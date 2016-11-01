%{
    #include "SemanticAnalyzer.h"
    #include "SyntaxTree.h"
    #include "Comment.h"
    #include "Function.h"

    SemanticAnalyzer SEMANTIC_ANALYZER;
    SyntaxTree* SYNTAX_TREE;

    extern int yylex();
    extern void yyerror(const char* s, ...);
%}

%define parse.trace

%code requires {
    class TreeNode;
    class SyntaxTree;
}

/* yylval == %union
 * union informs the different ways we can store data
 */
%union {
    TreeNode* node;
    SyntaxTree* syntaxTree;
    char *string;
    int integer;
}

/* token defines our terminal symbols (tokens).
 */
%token <integer> T_VOID T_BOO T_FLT T_INT T_STR
%token T_TAB T_SP T_NL
%token T_TOC
%token T_NUM T_DEC T_TRUE T_FALSE
%token <string> T_COMMENT T_ID T_TEXT
%token T_OPAR T_CPAR T_ASSIGN T_COMMA


/* type defines the type of our nonterminal symbols.
 * Types should match the names used in the union.
 * Example: %type<node> expr
 */
%type <syntaxTree> lines program
%type <node> global
%type <integer> indent sp type

/* Operator precedence for mathematical operators
 * The latest it is listed, the highest the precedence
 * left, right, nonassoc
 */

/*relational operators*/

/*unary operator*/

/* Starting rule
 */
%start program

%%

// Programa
program:
    lines { SYNTAX_TREE = $1; }
    ;

// Linhas
lines:
    global { $$ = new SyntaxTree(); if($1 != NULL) $$->insertLine($1); }
    | global T_NL lines { $$ = $3; if($1 != NULL) $3->insertLine($1); }
    | error T_NL { yyerrok; $$ = NULL; }
    ;

// Linha
global:
    | T_COMMENT { $$ = new Comment($1); }
    | indent T_COMMENT { $$ = new Comment($2); }
    | T_VOID T_SP T_TOC T_OPAR T_CPAR { $$ = new Function("toc", NULL, NULL); }
    ;

declaration:
    type sp T_ID
    | type sp T_ID sp T_ASSIGN sp expression
    ;

expression:
    T_NUM
    | T_DEC
    ;

type:
    T_BOO
    | T_FLT
    | T_INT
    | T_STR
    | T_VOID
    ;

sp:
    { $$ = 0; }
    | T_SP sp { $$ = $2 + 1; }
    ;

indent:
    { $$ = 0; }
    | T_SP T_SP indent { $$ = $3 + 1; }
    ;
%%
