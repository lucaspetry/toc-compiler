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

%token <integer> T_BOO T_FLT T_INT T_STR T_NUM T_VOID
%token <decimal> T_DEC
%token <string> T_COMMENT T_ID T_TEXT
%token T_OPAR T_CPAR T_OBRACKET T_CBRACKET T_OBRACE T_CBRACE T_ASSIGN T_COMMA T_SCOLON
%token T_TRUE T_FALSE
%token T_IF T_ELSE
%token T_TAB T_SP T_NL
%token T_TOC T_PRINT T_RETURN
%token T_FOR T_IN
%token T_OBJ T_PRV T_PUB

/*
 * Símbolos não-terminais da gramática e seus respectivos tipos.
 * Os tipos correspondem às variáveis usadas na união.
 */
%type <syntaxTree> program
%type <node> line declaration attribuition multiple_attribution expr expr_right function object_attributes object_functions
%type <codeBlock> lines multiple_declaration function_params
%type <integer> indent sp type_var  op_binary encapsulation function_type

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

// linhas de codigo
lines:
    indent line %prec LINE { if($2 != NULL) SEMANTIC.pushLineScope($2); }
    | lines T_NL indent line { if($4 != NULL) SEMANTIC.pushLineScope($4); }
    | error T_NL { yyerrok; $$ = NULL; }
    ;

// Linha de código
line:
    { $$ = NULL; }
    // Declaração e atribuição
    | declaration {$$ = $1; }
    | attribuition {$$ = $1; }
    // Diversos
    | T_COMMENT { $$ = new Comment($1); TOC.analyzeComment((Comment*) $$); }
    | T_PRINT sp expr { TOC.analyzeSpaces(1, $2); $$ = SEMANTIC.declarePrint($3); }
    // Condicional
    | T_IF T_OPAR expr T_CPAR sp {$$ = SEMANTIC.declareCondition($3, NULL); }
    | T_ELSE { $$ = NULL; SEMANTIC.declareElseCondition(NULL); }
    // Laços
    | T_FOR T_OPAR declaration T_SCOLON sp expr T_SCOLON sp attribuition T_CPAR {$$ = SEMANTIC.declareLoop($3, $6, $9);
                                                                                            TOC.analyzeSpaces(2, $5, $8);}
    | T_FOR T_OPAR T_ID sp T_IN sp T_ID T_CPAR {$$ = SEMANTIC.declareLoop(SEMANTIC.declareAssignVariable($3, Data::UNKNOWN, NULL),
                                                                              NULL, SEMANTIC.useVariable($7, new Integer(1)));
                                                                              SEMANTIC.analyzeLoop($7); }
    // Funções
    | T_VOID sp T_TOC T_OPAR T_CPAR sp { $$ = SEMANTIC.declareFunction("toc", NULL, NULL, Data::VOID); }
    | function

    //Orientacao objetos
    | T_OBJ sp T_ID T_OPAR function_params T_CPAR sp {$$ = SEMANTIC.declareObject($3,$5,NULL); }
    | T_OBJ sp T_ID T_OPAR T_CPAR sp { $$ = SEMANTIC.declareObject($3,NULL,NULL); }
    | object_attributes {$$ = $1;  }
    | object_functions {$$ = $1; }
    ;

// Metodos para objetos (encapsulamento)
object_functions:
    encapsulation sp type_var sp T_ID T_OPAR function_params T_CPAR sp {$$ = SEMANTIC.declareMethod($5, $7, NULL, (Data::Type)$3, $1); }
    | encapsulation sp type_var sp T_ID T_OPAR T_CPAR sp {$$ = SEMANTIC.declareMethod($5, NULL, NULL, (Data::Type)$3, $1); }

    ;

// Atributos para obejtos (encapsulamento)
object_attributes:
    encapsulation sp type_var sp T_ID { $$ = SEMANTIC.declareAttribute($5, (Data::Type)$3, $1);
                                              TOC.analyzeVariable($5);
                                              TOC.analyzeSpaces(2, $2, $4);}
    | encapsulation sp type_var sp T_ID sp T_ASSIGN sp expr { $$ = SEMANTIC.declareBinaryOperation(SEMANTIC.declareAssignAttribute($5, (Data::Type)$3, $1, $9), BinaryOperation::ASSIGN, $9);
                                                      $$->setSymbolTable(SEMANTIC.symbolTable);
                                                      SEMANTIC.analyzeCasting((BinaryOperation*) $$);
                                                      TOC.analyzeSpaces(2, $2, $4);
                                                      TOC.analyzeVariable($5); }
    | encapsulation sp type_var sp T_ID T_OBRACKET T_NUM T_CBRACKET { $$ = SEMANTIC.declareAttribute($5, (Data::Type)$3, $1, $7);
                                                                            TOC.analyzeVariable($5); }
    | encapsulation sp type_var sp T_ID T_OBRACKET T_NUM T_CBRACKET sp T_ASSIGN sp T_OBRACE multiple_attribution T_CBRACE {
                                      $$ = SEMANTIC.declareBinaryOperation(SEMANTIC.declareAssignAttribute($5,(Data::Type)$3, $1, $13, $7), BinaryOperation::ASSIGN, $13);
                                                                $$->setSymbolTable(SEMANTIC.symbolTable);
                                                                TOC.analyzeVariable($5); }
    ;

// Parâmetros de função
function_params:
    type_var sp T_ID { $$ = new CodeBlock(SEMANTIC.getCurrentIndentation()); $$->insertLineFront(SEMANTIC.declareVariable($3, (Data::Type)$1)); }
    | type_var sp T_ID T_COMMA sp function_params { $$ = $6; $$->insertLineFront(SEMANTIC.declareVariable($3, (Data::Type)$1)); }
    ;

// Funções
function:
     type_var sp T_ID T_OPAR function_params T_CPAR sp { $$ = SEMANTIC.declareFunction($3, $5, NULL, (Data::Type)$1); }
    | type_var sp T_ID T_OPAR T_CPAR sp { $$ = SEMANTIC.declareFunction($3, NULL, NULL, (Data::Type) $1); }
    | T_RETURN sp expr sp { $$ = SEMANTIC.declareFunctionReturn($3); }
    ;

// Declaração de variáveis
declaration:
    //variaveis
    type_var sp T_ID { $$ = SEMANTIC.declareVariable($3, (Data::Type)$1);
                    TOC.analyzeVariable($3);
                    TOC.analyzeSpaces(1, $2);}
    | type_var sp T_ID multiple_declaration { $$ = $4; $4->insertLineFront(SEMANTIC.declareVariable($3, (Data::Type)$1));
                                          SEMANTIC.setUnknownTypes((Data::Type) $1, $4);
                                          TOC.analyzeVariable($3); }
    | type_var sp T_ID sp T_ASSIGN sp expr { $$ = SEMANTIC.declareBinaryOperation(SEMANTIC.declareAssignVariable($3, (Data::Type)$1, $7), BinaryOperation::ASSIGN, $7);
                                                 $$->setSymbolTable(SEMANTIC.symbolTable);
                                                SEMANTIC.analyzeCasting((BinaryOperation*) $$);
                                                TOC.analyzeSpaces(3, $2, $4,$6);
                                                TOC.analyzeVariable($3); }
    // array
    | type_var sp T_ID T_OBRACKET T_NUM T_CBRACKET { $$ = SEMANTIC.declareVariable($3, (Data::Type)$1, $5);
                                                  TOC.analyzeVariable($3); }
    | type_var sp T_ID T_OBRACKET T_NUM T_CBRACKET multiple_declaration { $$ = $7; $7->insertLineFront(SEMANTIC.declareVariable($3, (Data::Type)$1, $5));
                                                                      SEMANTIC.setUnknownTypes((Data::Type) $1, $7);
                                                                      TOC.analyzeVariable($3); }
    | type_var sp T_ID T_OBRACKET T_NUM T_CBRACKET sp T_ASSIGN sp T_OBRACE multiple_attribution T_CBRACE { $$ = SEMANTIC.declareBinaryOperation(SEMANTIC.declareAssignVariable($3,(Data::Type)$1, $11, $5), BinaryOperation::ASSIGN, $11);
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
    T_ID sp T_ASSIGN sp expr { $$ = SEMANTIC.declareBinaryOperation(SEMANTIC.assignVariable($1, $5), BinaryOperation::ASSIGN, $5);
                                                 $$->setSymbolTable(SEMANTIC.symbolTable);
                                     SEMANTIC.analyzeCasting((BinaryOperation*) $$);
                                     TOC.analyzeSpaces(2, $2, $4);}
    // array
    | T_ID T_OBRACKET T_NUM T_CBRACKET sp T_ASSIGN sp expr {$$ = SEMANTIC.declareBinaryOperation(SEMANTIC.assignVariable($1, $8, new Integer($3)), BinaryOperation::ASSIGN, $8);
                                                 $$->setSymbolTable(SEMANTIC.symbolTable); }
    ;

// Multiplas atribuições para o array
multiple_attribution:
    expr {$$ = $1; }
    | expr T_COMMA sp multiple_attribution {$$ = SEMANTIC.declareBinaryOperation($1, BinaryOperation::MULT_ATT, $4);
                                                 $$->setSymbolTable(SEMANTIC.symbolTable); }
    ;

// Expressão
expr:
    expr_right {$$ = $1; }
    | expr sp op_binary sp expr_right {$$ = SEMANTIC.declareBinaryOperation($1, (BinaryOperation::Type)$3, $5);
                                                 $$->setSymbolTable(SEMANTIC.symbolTable); SEMANTIC.analyzeCasting((BinaryOperation*) $$) ;}
    ;

// Direita da expressão
expr_right:
  T_TRUE {$$ = new Boolean(true); }| T_FALSE {$$ = new Boolean(false); }
  | T_NUM {$$ = new Integer($1); } | T_DEC {$$ = new Float($1); } | T_TEXT {$$ = new String($1); }
  | T_ID T_OBRACKET expr T_CBRACKET { $$ = SEMANTIC.useVariable($1, $3); }
  | T_ID {$$ = SEMANTIC.useVariable($1); }
  | T_MINUS sp expr %prec U_MINUS T_SP LINE { $$ = new UnaryOperation(UnaryOperation::MINUS, $3); }
  | T_NOT sp expr %prec U_MINUS T_SP LINE { $$ = new UnaryOperation(UnaryOperation::NOT, $3); }
  | T_OPAR expr T_CPAR { $$ = $2; }
  ;

// Operadores binários
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

// Encapsulamento
encapsulation:
    T_PUB {$$ = 0;}
    | T_PRV {$$ = 1;}
    ;

// Tipos de dados
type_var:
    T_BOO {$$ = Data::BOO;}
    | T_FLT {$$ = Data::FLT;}
    | T_INT {$$ = Data::INT;}
    | T_STR {$$ = Data::STR;}
    ;

// Tipos de funções
function_type:
    T_BOO {$$ = Data::BOO;}
    | T_FLT {$$ = Data::FLT;}
    | T_INT {$$ = Data::INT;}
    | T_STR {$$ = Data::STR;}
    | T_VOID {$$ = Data::VOID;}
    ;

// Indentação
indent:
    sp { if(yychar != T_NL) SEMANTIC.setScope((float)$1/2); }
    ;

// Espaços
sp:
    { $$ = 0; }
    | T_SP sp { $$ = $2 + 1; }
    ;

%%
