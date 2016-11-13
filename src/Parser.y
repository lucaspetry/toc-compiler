%{
    #include "SemanticAnalyzer.h"
    #include "TocAnalyzer.h"
    #include "SyntaxTree.h"
    #include "Comment.h"
    #include "Function.h"
    #include "TocFunction.h"
    #include "Variable.h"
    #include "VariableDeclaration.h"
    #include "BinaryOperation.h"
    #include "Integer.h"
    #include "Float.h"
    #include "Boolean.h"

    SemanticAnalyzer SEMANTIC_ANALYZER;
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
%token <integer> T_NUM T_STR T_BOO T_FLT T_INT
%token <decimal> T_DEC
%token T_TAB T_SP T_NL
%token T_FALSE T_TRUE
%token T_TOC T_VOID
%token <string> T_COMMENT T_ID T_TEXT
%token T_OPAR T_CPAR T_ASSIGN T_COMMA


/*
 * Símbolos não-terminais da gramática e seus respectivos tipos.
 * Os tipos correspondem às variáveis usadas na união.
 */
%type <syntaxTree> program
%type <node> global line declaration expression attribuition
%type <codeBlock> main_scope multiple_declaration
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
    | attribuition
    | declaration {$$ = $1; }
    | T_COMMENT {$$ = new Comment($1); }
    ;

// Declaração de variáveis
declaration:
    type sp T_ID { TOC.analyzeSpaces(1, $2);
                   TOC.analyzeVariable($3);
                   Variable* v = (Variable*)SEMANTIC_ANALYZER.declareVariable($3, (Data::Type)$1);
                   $$ = new VariableDeclaration((Data::Type)$1 ,v); }
    | type sp T_ID multiple_declaration { TOC.analyzeSpaces(1, $2); TOC.analyzeVariable($3);
                                          SEMANTIC_ANALYZER.setType((Data::Type)$1);
                                          $$ = $4;
                                          $4->insertLine(SEMANTIC_ANALYZER.declareVariable($3, (Data::Type)$1)); }
    | type sp T_ID sp T_ASSIGN sp expression { TOC.analyzeSpaces(3, $2, $4, $6);
                                               TOC.analyzeVariable($3);
                                               $$ = new BinaryOperation(SEMANTIC_ANALYZER.declareAssignVariable($3, (Data::Type)$1),
                                                                            BinaryOperation::ASSIGN, $7); }
    ;

// Multiplas declarações
multiple_declaration:
    T_COMMA sp T_ID  { TOC.analyzeSpaces(1, $2); TOC.analyzeVariable($3);
                       $$ = new CodeBlock(0);
                       $$->insertLine(SEMANTIC_ANALYZER.declareVariable($3, Data::UNKNOWN)); }
    | T_COMMA sp T_ID multiple_declaration  { TOC.analyzeSpaces(1, $2); TOC.analyzeVariable($3);
                                              $$ = $4;
                                              $$->insertLine(SEMANTIC_ANALYZER.declareVariable($3, Data::UNKNOWN));}
    ;
// Atribuição
attribuition:
    T_ID sp T_ASSIGN sp expression { TOC.analyzeSpaces(2, $2, $4);
                                     $$ = new BinaryOperation(SEMANTIC_ANALYZER.assignVariable($1), BinaryOperation::ASSIGN, $5);}
// Expressão
expression:
    T_TRUE {$$ = new Boolean(true);}
    | T_FALSE {$$ = new Boolean(false);}
    | T_NUM {$$ = new Integer($1);}
    | T_DEC {$$ = new Float($1);}
    | T_ID {SEMANTIC_ANALYZER.useVariable($1); $$ = NULL;}
    ;

// Tipos de dados
type:
    T_BOO { $$ = Data::BOO;}
    | T_FLT {$$ = Data::FLT;}
    | T_INT { $$ = Data::INT;}
    | T_STR { $$ = Data::STR;}
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
    | T_SP T_SP indent { $$ = $3 + 1;}
    ;

%%
