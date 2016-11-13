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
    #include "Integer.h"
    #include "Float.h"
    #include "Boolean.h"

    SemanticAnalyzer SEMANTIC;
    TocAnalyzer TOC;
    SyntaxTree* SYNTAX_TREE;

    extern int yylex();
    extern void yyerror(const char* s, ...);
%}

%define parse.trace

%code requires {
    class TreeNode;
    class SyntaxTree;
}

/*
 * yylval == %union
 * Diferentes meios de armazenar os dados.
 */
%union {
    TreeNode* node;
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
%token T_TOC T_VOID


/*
 * Símbolos não-terminais da gramática e seus respectivos tipos.
 * Os tipos correspondem às variáveis usadas na união.
 */
%type <syntaxTree> program
%type <node> global main_scope line declaration multiple_declaration multiple_attribution expression attribuition
%type <integer> indent sp type

/*
 * Precedência de operadores.
 * Os primeiros listados têm menor precedência do que os últimos.
 * (left, right, nonassoc)
 */

/*
 * Símbolo inicial da gramática.
 */
%start start

%%

start:
    program { /** TOC.analyzeProgram() */ }
    ;

// Programa
program:
    global {SYNTAX_TREE = new SyntaxTree(); $$ = SYNTAX_TREE; if($1 != NULL) $$->insertLine($1); }
    | global T_NL program { $$ = $3; if($1 != NULL) $3->insertLine($1); }
    | error T_NL { yyerrok; $$ = NULL; }
    ;

// Linha
global:
    T_COMMENT { $$ = new Comment($1); }
    | T_VOID sp T_TOC T_OPAR T_CPAR sp T_NL main_scope {  $$ = new TocFunction((CodeBlock*) $8);   }
    ;

main_scope:
    indent line  {$$ = new CodeBlock($1); if($2 != NULL) ((CodeBlock*)$$)->insertLine($2);  }
    | indent line T_NL main_scope { $$ = $4; if($2 != NULL) ((CodeBlock*)$4)->insertLine($2);}
    ;

line:
    { $$ = NULL; }
    | declaration {$$ = $1; }
    | attribuition {$$ = $1; }
    | T_COMMENT {$$ = new Comment($1); }
    ;

// Declaração de variáveis
declaration:
    type sp T_ID { $$ = SEMANTIC.declareVariable($3, (Data::Type)$1); TOC.analyzeVariable($3); }
    | type sp T_ID multiple_declaration { $$ = new BinaryOperation(SEMANTIC.declareVariable($3, (Data::Type)$1), BinaryOperation::COMMA, $4);
                                          TOC.analyzeVariable($3); }
    | type sp T_ID sp T_ASSIGN sp expression { $$ = new BinaryOperation(SEMANTIC.declareAssignVariable($3, (Data::Type)$1), BinaryOperation::ASSIGN, $7);
                                              TOC.analyzeAssign($2,$4); TOC.analyzeVariable($3); }
    // array
    | type sp T_ID T_OBRACKET T_NUM T_CBRACKET { $$ = SEMANTIC.declareVariable($3, (Data::Type)$1, $5);
                                                TOC.analyzeVariable($3); }
    | type sp T_ID T_OBRACKET T_NUM T_CBRACKET multiple_declaration {$$ = new BinaryOperation(SEMANTIC.declareVariable($3, (Data::Type)$1, $5), BinaryOperation::COMMA, $7);
                                                                      TOC.analyzeVariable($3); }
    | type sp T_ID T_OBRACKET T_NUM T_CBRACKET sp T_ASSIGN sp T_OBRACE multiple_attribution T_CBRACE { $$ = new BinaryOperation(SEMANTIC.declareAssignVariable($3,(Data::Type)$1, $5),
                                                                                                        BinaryOperation::ASSIGN, $11); TOC.analyzeVariable($3); }
    ;

//Multiplas declarações
multiple_declaration:
    T_COMMA sp T_ID  { $$ = SEMANTIC.declareVariable($3 , Data::UNKNOWN);
                      TOC.analyzeCommas($2); TOC.analyzeVariable($3); }
    | T_COMMA sp T_ID multiple_declaration  { $$ = new BinaryOperation(SEMANTIC.declareVariable($3, Data::UNKNOWN), BinaryOperation::COMMA, $4);
                                              TOC.analyzeCommas($2); TOC.analyzeVariable($3);}
    // array
    | T_COMMA sp T_ID T_OBRACKET T_NUM T_CBRACKET { $$ = SEMANTIC.declareVariable($3, Data::UNKNOWN, $5);
                                                    TOC.analyzeCommas($2); TOC.analyzeVariable($3); }
    | T_COMMA sp T_ID T_OBRACKET T_NUM T_CBRACKET multiple_declaration { $$ = new BinaryOperation(SEMANTIC.declareVariable($3, Data::UNKNOWN, $5),
                                                                          BinaryOperation::COMMA, $7); TOC.analyzeCommas($2); TOC.analyzeVariable($3); }
    ;

// Multiplas atribuições para o array
multiple_attribution:
    expression {$$ = $1; }
    | expression T_COMMA sp multiple_attribution {$$ = new BinaryOperation($1, BinaryOperation::MULT_ATT, $4); }
    ;

// Expressão
expression:
    T_TRUE {$$ = new Boolean(true); }| T_FALSE {$$ = new Boolean(false); }
    | T_NUM {$$ = new Integer($1); } | T_DEC {$$ = new Float($1); } | T_TEXT {$$ = NULL; }
    | T_ID T_OBRACKET expression T_CBRACKET { $$ = SEMANTIC.useVariable($1, $3); }
    | T_ID {SEMANTIC.useVariable($1); $$ = NULL;}
    | {$$ = NULL; }
    ;

// Atribuição
attribuition:
    // array
    T_ID T_OBRACKET T_NUM T_CBRACKET sp T_ASSIGN sp expression {$$ = new BinaryOperation(SEMANTIC.assignVariable($1, new Integer($3)), BinaryOperation::ASSIGN, $8); }
    // other
    | T_ID sp T_ASSIGN sp expression { $$ = new BinaryOperation(SEMANTIC.assignVariable($1), BinaryOperation::ASSIGN, $5);
                                            TOC.analyzeAssign($2,$4); }
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
    {  int a = 0; $$ = a; }
    | T_SP T_SP indent { $$ = ($3 + 1);}
    ;

%%
