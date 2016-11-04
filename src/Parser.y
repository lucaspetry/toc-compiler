%{
    #include "SemanticAnalyzer.h"
    #include "TocAnalyzer.h"
    #include "SyntaxTree.h"
    #include "Array.h"
    #include "Comment.h"
    #include "Function.h"

    // to test
    #include <iostream>

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
%token <integer> T_VOID T_BOO T_FLT T_INT T_STR T_NUM // coloquei T_NUM aqui afinal precisamos do valor inteir dele. T_INT deveria estar aqui ?
%token T_TAB T_SP T_NL
%token T_TOC
%token T_DEC T_TRUE T_FALSE
%token <string> T_COMMENT T_ID T_TEXT
%token T_OPAR T_CPAR T_OBRACKET T_CBRACKET T_OBRACE T_CBRACE T_ASSIGN T_COMMA


/*
 * Símbolos não-terminais da gramática e seus respectivos tipos.
 * Os tipos correspondem às variáveis usadas na união.
 */
%type <syntaxTree> program
%type <node> global main_scope line declaration multiple_declaration multiple_attribution
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
    | {$$ = NULL;} // coloquei aqui pois não passa linha em branco, não sei se é o melhor local
    ;

// Linha
global:
    T_COMMENT { $$ = new Comment($1); }
    | T_VOID sp T_TOC T_OPAR T_CPAR sp T_NL main_scope { $$ = new Function("toc", NULL, NULL); }
    ;

main_scope:
    | indent line { $$ = $2; }
    | indent line T_NL main_scope { $$ = $4; }
    ;

line:
    declaration {$$ = $1; }
    | T_COMMENT {$$ = NULL; }
    ;

// Declaração de variáveis
declaration:
    type sp T_ID { $$ = NULL; }
    | type sp T_ID sp T_ASSIGN sp expression { $$ = NULL; }
    // aqui é possível declarar 1 (uma) ou n variáveis do tipo arranjo
    | type sp T_ID T_OBRACKET T_NUM T_CBRACKET multiple_declaration {
      if($7 == NULL) $$ = SEMANTIC_ANALYZER.declareVariable($3, (Data::Type)$1, 5); // id, type, size
    }
    // aqui é possível declarar e atribuir 1 (um) ou n valores ao arranjo
    | type sp T_ID T_OBRACKET T_NUM T_CBRACKET sp T_ASSIGN sp T_OBRACE multiple_attribution T_CBRACE {
      $$ = SEMANTIC_ANALYZER.declareVariable($3, (Data::Type)$1, $5);  // id, type, size
    }
    ;

//Multiplas declarações
multiple_declaration:
    {$$ = NULL; }
    | T_COMMA sp T_ID sp T_OBRACKET T_NUM T_CBRACKET {$$ = NULL; }
    | T_COMMA sp T_ID T_OBRACKET T_NUM T_CBRACKET multiple_declaration {$$ = NULL; }
    ;

// Multiplas atribuições para o array
multiple_attribution:
    expression {$$ = NULL; } // podemos atribuir os 4 tipos {str, int, boo, flt}
    | expression T_COMMA sp multiple_attribution {$$ = NULL; }

// Expressão
expression:
    T_TRUE | T_FALSE
    | T_NUM | T_DEC
    |
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
