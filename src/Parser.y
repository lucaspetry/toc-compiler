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

    SemanticAnalyzer SEMANTIC;  // Analisador semântico
    TocAnalyzer TOC;            // Analisador TOC
    SyntaxTree* SYNTAX_TREE;    // Árvore sintática

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
%type <node> line declaration expression attribuition multiple_attribution expression_two
%type <codeBlock> lines multiple_declaration
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
%nonassoc LINE
%nonassoc T_NL T_SP

/*
 * Símbolo inicial da gramática.
 */
%start start

%%

// Início do parsing
start:
    program { SEMANTIC.analyzeProgram();
              TOC.analyzeProgram(); }
    ;

// Programa
program:
    lines { SYNTAX_TREE = new SyntaxTree(SEMANTIC.getCurrentBody()); }
    ;

lines:
    indent line %prec LINE { if($2 != NULL) SEMANTIC.pushLineScope($2); }
    | lines T_NL indent line { if($4 != NULL) SEMANTIC.pushLineScope($4); }
    | error T_NL { yyerrok; $$ = NULL; }
    ;

// Linha de código
line:
    { $$ = NULL; }
    | declaration {$$ = $1; }
    | attribuition {$$ = $1; }
    | T_COMMENT { $$ = new Comment($1); TOC.analyzeComment((Comment*) $$); }
    | T_PRINT sp expression { TOC.analyzeSpaces(1, $2); $$ = new PrintFunction($3); }
    | T_VOID sp T_TOC T_OPAR T_CPAR sp { $$ = SEMANTIC.declareFunction("toc", NULL, NULL, NULL); }
    ;

// Declaração de variáveis
declaration:
    type sp T_ID { $$ = SEMANTIC.declareVariable($3, (Data::Type)$1);
                    TOC.analyzeVariable($3);
                    TOC.analyzeSpaces(1, $2);}
    | type sp T_ID multiple_declaration { $$ = $4; $4->insertLineFront(SEMANTIC.declareVariable($3, (Data::Type)$1));
                                          SEMANTIC.setUnknownTypes((Data::Type) $1, $4);
                                          TOC.analyzeVariable($3); }
    | type sp T_ID sp T_ASSIGN sp expression { $$ = new BinaryOperation(SEMANTIC.declareAssignVariable($3, (Data::Type)$1, $7), BinaryOperation::ASSIGN, $7);
                                                 $$->setSymbolTable(SEMANTIC.symbolTable);
                                                SEMANTIC.analyzeCasting((BinaryOperation*) $$);
                                                TOC.analyzeSpaces(1, $2);
                                                TOC.analyzeVariable($3); }
    // array
    | type sp T_ID T_OBRACKET T_NUM T_CBRACKET { $$ = SEMANTIC.declareVariable($3, (Data::Type)$1, $5);
                                                  TOC.analyzeVariable($3); }
    | type sp T_ID T_OBRACKET T_NUM T_CBRACKET multiple_declaration { $$ = $7; $7->insertLineFront(SEMANTIC.declareVariable($3, (Data::Type)$1, $5));
                                                                      SEMANTIC.setUnknownTypes((Data::Type) $1, $7);
                                                                      TOC.analyzeVariable($3); }
    | type sp T_ID T_OBRACKET T_NUM T_CBRACKET sp T_ASSIGN sp T_OBRACE multiple_attribution T_CBRACE { $$ = new BinaryOperation(SEMANTIC.declareAssignVariable($3,(Data::Type)$1, $11, $5), BinaryOperation::ASSIGN, $11);
                                                 $$->setSymbolTable(SEMANTIC.symbolTable);
                                                                                                        TOC.analyzeVariable($3); }
    ;

// Multiplas declarações
multiple_declaration:
    T_COMMA sp T_ID { $$ = new CodeBlock(SEMANTIC.getCurrentIndentation());
                      $$->insertLineFront(SEMANTIC.declareVariable($3, Data::UNKNOWN));
                      TOC.analyzeSpaces(1, $2); TOC.analyzeVariable($3); }
    | T_COMMA sp T_ID multiple_declaration {$$ = $4;
                                            $$->insertLineFront(SEMANTIC.declareVariable($3, Data::UNKNOWN));
                                            TOC.analyzeSpaces(1, $2); TOC.analyzeVariable($3); }
   // array
    | T_COMMA sp T_ID T_OBRACKET T_NUM T_CBRACKET { $$ = new CodeBlock(SEMANTIC.getCurrentIndentation());
                                                    $$->insertLineFront(SEMANTIC.declareVariable($3, Data::UNKNOWN, $5));
                                                    TOC.analyzeSpaces(1, $2); TOC.analyzeVariable($3); }
    | T_COMMA sp T_ID T_OBRACKET T_NUM T_CBRACKET multiple_declaration { $$ = $7;
                                                                        $$->insertLineFront(SEMANTIC.declareVariable($3, Data::UNKNOWN, $5));
                                                                        TOC.analyzeSpaces(1, $2); TOC.analyzeVariable($3); }
    ;

// Atribuição
attribuition:
    T_ID sp T_ASSIGN sp expression { $$ = new BinaryOperation(SEMANTIC.assignVariable($1, $5), BinaryOperation::ASSIGN, $5);
                                                 $$->setSymbolTable(SEMANTIC.symbolTable);
                                     SEMANTIC.analyzeCasting((BinaryOperation*) $$);
                                     TOC.analyzeSpaces(2, $2, $4);}
    // array
    | T_ID T_OBRACKET T_NUM T_CBRACKET sp T_ASSIGN sp expression {$$ = new BinaryOperation(SEMANTIC.assignVariable($1, $8, new Integer($3)), BinaryOperation::ASSIGN, $8);
                                                 $$->setSymbolTable(SEMANTIC.symbolTable); }
    ;

// Multiplas atribuições para o array
multiple_attribution:
    expression {$$ = $1; }
    | expression T_COMMA sp multiple_attribution {$$ = new BinaryOperation($1, BinaryOperation::MULT_ATT, $4);
                                                 $$->setSymbolTable(SEMANTIC.symbolTable); }
    ;

// Expressão
expression:
    expression_two {$$ = $1; }
    | expression sp op_binary sp expression_two {$$ = new BinaryOperation($1, (BinaryOperation::Type)$3, $5);
                                                 $$->setSymbolTable(SEMANTIC.symbolTable); }
    ;

expression_two:
  T_TRUE {$$ = new Boolean(true); }| T_FALSE {$$ = new Boolean(false); }
  | T_NUM {$$ = new Integer($1); } | T_DEC {$$ = new Float($1); } | T_TEXT {$$ = new String($1); }
  | T_ID T_OBRACKET expression T_CBRACKET { $$ = SEMANTIC.useVariable($1, $3); }
  | T_ID {$$ = SEMANTIC.useVariable($1); }
  | T_MINUS expression %prec U_MINUS LINE { $$ = new UnaryOperation(UnaryOperation::MINUS, $2); }
  | T_NOT sp expression %prec U_MINUS T_SP LINE { $$ = new UnaryOperation(UnaryOperation::NOT, $3); }
  | T_OPAR expression T_CPAR { $$ = $2; }
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

indent: // TODO Bug: Ainda será possível pular de 2 para 6 espaços, por exemplo
    sp { SEMANTIC.setScope((float)$1/2); }
    ;

// Espaços
sp:
    { $$ = 0; }
    | T_SP sp { $$ = $2 + 1; }
    ;

%%
