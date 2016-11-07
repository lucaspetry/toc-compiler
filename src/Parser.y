%{
    #include "SemanticAnalyzer.h"
    #include "TocAnalyzer.h"
    #include "SyntaxTree.h"
    #include "Comment.h"
    #include "Function.h"
    #include "Variable.h"
    #include "VariableDeclaration.h"

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
%type <node> global main_scope line declaration multiple_declaration expression
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
    global {SYNTAX_TREE = new SyntaxTree(); $$ = SYNTAX_TREE; if($1 != NULL) $$->insertLine($1); }
    | global T_NL program { $$ = $3; if($1 != NULL) $3->insertLine($1); }
    | error T_NL { yyerrok; $$ = NULL; }
    ;

// Linha
global:
    T_COMMENT { $$ = new Comment($1); }
    | T_VOID sp T_TOC T_OPAR T_CPAR sp T_NL main_scope { $$ = new Function("toc", Data::VOID, NULL, $8); }
    ;

main_scope:
    indent line  {$$ = new CodeBlock($1); if($2 != NULL) ((CodeBlock*)$$)->insertLine($2);}
    | indent line T_NL main_scope { $$ = $4; if($2 != NULL) ((CodeBlock*)$4)->insertLine($2);}
    ;

line:
    { $$ = NULL; }
    | declaration {$$ = $1; }
    | T_COMMENT {$$ = new Comment($1); }
    ;

// Declaração de variáveis
declaration:
    type sp T_ID { TOC_ANALYZER.analyzeVariable($3); Variable* v = (Variable*)SEMANTIC_ANALYZER.declareVariable($3, (Data::Type)$1); $$ = new VariableDeclaration((Data::Type)$1 ,v);}
    | type sp T_ID multiple_declaration { TOC_ANALYZER.analyzeVariable($3); SEMANTIC_ANALYZER.declareVariable($3, (Data::Type)$1);
                                                  $$ = NULL;}
    | T_ID sp T_ASSIGN sp expression { TOC_ANALYZER.analyzeAssign($2,$4);
                                                  $$ = NULL;}
    | type sp T_ID sp T_ASSIGN sp expression { TOC_ANALYZER.analyzeAssign($2,$4);
                                              TOC_ANALYZER.analyzeVariable($3);
                                              SEMANTIC_ANALYZER.declareVariable($3, (Data::Type)$1);
                                                $$ = NULL; }
    ;

//Multiplas declarações
multiple_declaration:
    T_COMMA sp T_ID  { TOC_ANALYZER.analyzeCommas($2); TOC_ANALYZER.analyzeVariable($3); $$ = NULL;}
    | T_COMMA sp T_ID multiple_declaration  { TOC_ANALYZER.analyzeCommas($2); TOC_ANALYZER.analyzeVariable($3); $$ = NULL;}
    ;

// Expressão
expression:
    T_TRUE {$$ = NULL;}
    | T_FALSE {$$ = NULL;}
    | T_NUM {$$ = NULL;}
    | T_DEC {$$ = NULL;}
    | T_ID {SEMANTIC_ANALYZER.useVariable($1); $$ = NULL;}
    ;

// Tipos de dados
type:
    T_BOO { $$ = Data::BOO;}
    | T_FLT {$$ = Data::FLT;}
    | T_INT{ $$ = Data::INT;}
    | T_STR{ $$ = Data::STR;}
    | T_VOID {$$ = Data::VOID;}
    ;

// Espaços
sp:
    { $$ = 0; }
    | T_SP sp { $$ = $2 + 1; }
    ;

// Indentação
indent:
    {  int a = 1; $$ = a; }
    | T_SP T_SP indent { $$ = ($3 + 1);}
    ;

%%
