%{
    #include "SemanticAnalyzer.h"
    #include "TocAnalyzer.h"
    #include "SyntaxTree.h"
    #include "Comment.h"
    #include "Function.h"

    SemanticAnalyzer SEMANTIC_ANALYZER;
    TocAnalyzer TOC_ANALYZER;
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
}

/*
 * Símbolos terminais (tokens) para a gramática.
 */
%token <integer> T_VOID T_BOO T_FLT T_INT T_STR
%token T_TAB T_SP T_NL
%token T_TOC
%token T_NUM T_DEC T_TRUE T_FALSE
%token <string> T_COMMENT T_ID T_TEXT
%token T_OPAR T_CPAR T_ASSIGN T_COMMA


/*
 * Símbolos não-terminais da gramática e seus respectivos tipos.
 * Os tipos correspondem às variáveis usadas na união.
 */
%type <syntaxTree> program
%type <node> global main_scope line declaration
%type <integer> indent sp type

/*
 * Precedência de operadores.
 * Os primeiros listados têm menor precedência do que os últimos.
 * (left, right, nonassoc)
 */

/* 
 * Símbolo inicial da gramática.
 */
%start program

%%

// Programa
program:
    global { SYNTAX_TREE = new SyntaxTree(); $$ = SYNTAX_TREE; if($1 != NULL) $$->insertLine($1); }
    | global T_NL program { $$ = $3; if($1 != NULL) $3->insertLine($1); }
    | error T_NL { yyerrok; $$ = NULL; }
    ;

// Linha
global:
    T_COMMENT { $$ = new Comment($1); }
    | T_VOID sp T_TOC T_OPAR T_CPAR sp T_NL main_scope { $$ = new Function("toc", NULL, NULL); }
    ;

main_scope:
    indent line { $$ = $2; }
    | indent line T_NL main_scope { $$ = $4; }
    ;
    
line:
    declaration
    | T_COMMENT
    ;

// Declaração de variáveis
declaration:
    type sp T_ID { $$ = NULL; }
    | type sp T_ID sp T_ASSIGN sp expression { $$ = NULL; }
    ;

// Expressão
expression:
    T_TRUE | T_FALSE
    | T_NUM | T_DEC
    ;

// Tipos de dados
type:
    T_BOO
    | T_FLT
    | T_INT
    | T_STR
    | T_VOID
    ;

// Espaços
sp:
    { $$ = 0; }
    | T_SP sp { $$ = $2 + 1; }
    ;

// Indentação
indent:
    { $$ = 0; }
    | T_SP T_SP indent { $$ = $3 + 1; }
    ;
    
%%
