%{
    #include "SemanticAnalyzer.h"
    #include "SyntaxTree.h"
    #include "TreeNode.h"

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
    char *comment;
}

/* token defines our terminal symbols (tokens).
 */
%token T_VOID
%token T_TAB T_INDENT T_SPACE T_NL
%token T_TOC
%token <comment> T_COMMENT
%token T_OPAR T_CPAR


/* type defines the type of our nonterminal symbols.
 * Types should match the names used in the union.
 * Example: %type<node> expr
 */
%type <syntaxTree> lines program
%type <node> line

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
    line { $$ = new SyntaxTree(); if($1 != NULL) $$->insertLine($1);  }
    | line T_NL lines { $$ = $3; if($1 != NULL) $3->insertLine($1);  }
    | error T_NL { yyerrok; $$ = NULL; }
    ;

// Linha
line:
    T_COMMENT {std::cout << $1 << std::endl;}
    | T_VOID T_SPACE T_TOC T_OPAR T_CPAR {std::cout << "SSDF" << std::endl;}
    ;
%%
