%{
    #include "SemanticAnalyzer.h"
    #include "TocAnalyzer.h"
    #include "SyntaxTree.h"
    #include "Array.h"
    #include "Comment.h"
    #include "Function.h"
    #include "TocFunction.h"
    #include "Variable.h"
    #include "VariableDeclaration.h"
    #include "BinaryOperation.h"
    #include "String.h"
    #include "PrintFunction.h"
    #include "Integer.h"
    #include "Float.h"
    #include "Boolean.h"
    #include "UnaryOperation.h"

    SemanticAnalyzer SEMANTIC;
    TocAnalyzer TOC;
    SyntaxTree* SYNTAX_TREE;

    extern int yylex();
    extern void yyerror(const char* s, ...);
%}

%define parse.trace

%code requires {
    class TreeNode;
    class CodeBlock;
    class SyntaxTree;
}

/*
 * yylval == %union
 * Diferentes meios de armazenar os dados.
 */
%union {
    TreeNode* node;
    CodeBlock* codeBlock;
    SyntaxTree* syntaxTree;
    char *string;
    int integer;
    float decimal;
}

/*
 * Símbolos terminais (tokens) para a gramática.
 */

%token <integer> T_BOO T_FLT T_INT T_STR T_NUM
%token <decimal> T_DEC
%token <string> T_COMMENT T_ID T_TEXT
%token T_OPAR T_CPAR T_OBRACKET T_CBRACKET T_OBRACE T_CBRACE T_ASSIGN T_COMMA
%token T_TRUE T_FALSE
%token T_TAB T_SP T_NL
%token T_TOC T_VOID T_PRINT

/*
 * Símbolos não-terminais da gramática e seus respectivos tipos.
 * Os tipos correspondem às variáveis usadas na união.
 */
%type <syntaxTree> program
%type <node> global line declaration expression attribuition multiple_attribution
%type <codeBlock> main_scope multiple_declaration
%type <integer> indent sp type op_binary

/*
 * Precedência de operadores.
 * Os primeiros listados têm menor precedência do que os últimos.
 * (left, right, nonassoc)
 */


 %left T_NOT T_AND T_OR
 %left T_GREATER T_GREATER_E T_LOWER T_LOWER_E T_EQUAL T_DIFF

 %left T_PLUS T_MINUS
 %left T_TIMES T_DIVIDE
 %left T_MOD

 %nonassoc U_MINUS error

/*
 * Símbolo inicial da gramática.
 */
%start start

%%

// Início do parsing
start:
    program { /** TOC.analyzeProgram() */ }
    ;

// Programa
program:
    global {SYNTAX_TREE = new SyntaxTree(); $$ = SYNTAX_TREE; if($1 != NULL) $$->insertLine($1); }
    | global T_NL program { $$ = $3; if($1 != NULL) $3->insertLine($1); }
    | error T_NL { yyerrok; $$ = NULL; }
    ;

// Escopo global
global:
    T_COMMENT { $$ = new Comment($1); }
    | T_VOID sp T_TOC T_OPAR T_CPAR sp T_NL main_scope { $$ = new TocFunction($8); }
    ;

// Escopo principal (função toc())
main_scope:
    indent line { $$ = new CodeBlock(1); if($2 != NULL) $$->insertLine($2); }
    | indent line T_NL main_scope { $$ = $4; if($2 != NULL) $$->insertLine($2); }
    ;

// Linha de código
line:
    { $$ = NULL; }
    | declaration {$$ = $1; }
    | attribuition {$$ = $1; }
    | T_COMMENT {$$ = new Comment($1); }
    | T_PRINT sp expression { TOC.analyzeSpaces(1, $2); $$ = new PrintFunction($3); }
    ;

// Declaração de variáveis
declaration:
    type sp T_ID { $$ = SEMANTIC.declareVariable($3, (Data::Type)$1);
                    TOC.analyzeVariable($3);
                    TOC.analyzeSpaces(1, $2);}
    | type sp T_ID multiple_declaration { $$ = new BinaryOperation(SEMANTIC.declareVariable($3, (Data::Type)$1), BinaryOperation::COMMA, $4);
                                            TOC.analyzeVariable($3); }
    | type sp T_ID sp T_ASSIGN sp expression { $$ = new BinaryOperation(SEMANTIC.declareAssignVariable($3, (Data::Type)$1), BinaryOperation::ASSIGN, $7);
                                                SEMANTIC.analyzeCasting((BinaryOperation*) $$);
                                                TOC.analyzeSpaces(1, $2);
                                                TOC.analyzeVariable($3); }
    // array
    | type sp T_ID T_OBRACKET T_NUM T_CBRACKET { $$ = SEMANTIC.declareVariable($3, (Data::Type)$1, $5);
                                                  TOC.analyzeVariable($3); }
    | type sp T_ID T_OBRACKET T_NUM T_CBRACKET multiple_declaration {$$ = new BinaryOperation(SEMANTIC.declareVariable($3, (Data::Type)$1, $5), BinaryOperation::COMMA, $7);
                                                                      TOC.analyzeVariable($3); }
    | type sp T_ID T_OBRACKET T_NUM T_CBRACKET sp T_ASSIGN sp T_OBRACE multiple_attribution T_CBRACE { $$ = new BinaryOperation(SEMANTIC.declareAssignVariable($3,(Data::Type)$1, $5), BinaryOperation::ASSIGN, $11);
                                                                                                        TOC.analyzeVariable($3); }
    ;

// Multiplas declarações
multiple_declaration:
    T_COMMA sp T_ID { $$ = new CodeBlock(0);
                      $$->insertLine(SEMANTIC.declareVariable($3, Data::UNKNOWN));
                      TOC.analyzeSpaces(1, $2); TOC.analyzeVariable($3); }
    | T_COMMA sp T_ID multiple_declaration {$$ = $4;
                                            $$->insertLine(SEMANTIC.declareVariable($3, Data::UNKNOWN));
                                            TOC.analyzeSpaces(1, $2); TOC.analyzeVariable($3); }
   // array
    | T_COMMA sp T_ID T_OBRACKET T_NUM T_CBRACKET { $$ = new CodeBlock(0);
                                                    $$->insertLine(SEMANTIC.declareVariable($3, Data::UNKNOWN, $5));
                                                    TOC.analyzeSpaces(1, $2); TOC.analyzeVariable($3); }
    | T_COMMA sp T_ID T_OBRACKET T_NUM T_CBRACKET multiple_declaration { $$ = $7;
                                                                        $$->insertLine(SEMANTIC.declareVariable($3, Data::UNKNOWN, $5));
                                                                        TOC.analyzeSpaces(1, $2); TOC.analyzeVariable($3); }
    ;

// Atribuição
attribuition:
    T_ID sp T_ASSIGN sp expression { $$ = new BinaryOperation(SEMANTIC.assignVariable($1), BinaryOperation::ASSIGN, $5);
                                     SEMANTIC.analyzeCasting((BinaryOperation*) $$);
                                     TOC.analyzeSpaces(2, $2, $4);}
    // array
    | T_ID T_OBRACKET T_NUM T_CBRACKET sp T_ASSIGN sp expression {$$ = new BinaryOperation(SEMANTIC.assignVariable($1, new Integer($3)), BinaryOperation::ASSIGN, $8); }
    ;

// Multiplas atribuições para o array
multiple_attribution:
    expression {$$ = $1; }
    | expression T_COMMA sp multiple_attribution {$$ = new BinaryOperation($1, BinaryOperation::MULT_ATT, $4); }
    ;

// Expressão
expression:
    T_TRUE {$$ = new Boolean(true); }| T_FALSE {$$ = new Boolean(false); }
    | T_NUM {$$ = new Integer($1); } | T_DEC {$$ = new Float($1); } | T_TEXT {$$ = new String($1); }
    | T_ID T_OBRACKET expression T_CBRACKET { $$ = SEMANTIC.useVariable($1, $3); }
    | T_ID {$$ = SEMANTIC.useVariable($1); }
    | T_MINUS expression %prec U_MINUS { $$ = new UnaryOperation(UnaryOperation::MINUS, $2); }
    | T_NOT sp expression { $$ = new UnaryOperation(UnaryOperation::NOT, $3); }
    | T_OPAR expression T_CPAR { $$ = $2; }
    | expression sp op_binary sp expression {$$ = new BinaryOperation($1, (BinaryOperation::Type)$3, $5); }
    ;

//Operaçoes binárias
op_binary:
    T_PLUS { $$ = BinaryOperation::PLUS ;}
    | T_MINUS { $$ = BinaryOperation::MINUS; }
    | T_TIMES { $$ = BinaryOperation::TIMES; }
    | T_DIVIDE { $$ = BinaryOperation::DIVIDE; }
    | T_GREATER { $$ = BinaryOperation::GREATER; }
    | T_GREATER_E { $$ = BinaryOperation::GREATER_E; }
    | T_LOWER { $$ = BinaryOperation::LOWER; }
    | T_LOWER_E { $$ = BinaryOperation::LOWER_E; }
    | T_EQUAL { $$ = BinaryOperation::EQUAL; }
    | T_DIFF { $$ = BinaryOperation::DIFF; }
    | T_AND { $$ = BinaryOperation::AND; }
    | T_OR { $$ = BinaryOperation::OR; }
    ;

// Tipos de dados
type:
    T_BOO {$$ = Data::BOO;}
    | T_FLT {$$ = Data::FLT;}
    | T_INT {$$ = Data::INT;}
    | T_STR {$$ = Data::STR;}
    | T_VOID {$$ = Data::VOID;}
    ;

// Espaços
sp:
    { $$ = 0; }
    | T_SP sp { $$ = $2 + 1; }
    ;

// Indentação (2 espaços)
indent:
    { $$ = 0; }
    | T_SP T_SP indent { $$ = $3 + 1; }
    ;

%%
