#include "CodeGenerator.h"
#include "ErrorLogger.h"
#include "SyntaxTree.h"

ErrorLogger* ERROR_LOGGER;

extern SyntaxTree* SYNTAX_TREE;
extern int yydebug;
extern int yyparse();

int main(int argc, char **argv) {
    // yydebug = 1;

    // Cria o logger de erros
    ERROR_LOGGER = new ErrorLogger();
    
    // Parsing da entrada
    yyparse();
    
#ifdef LLVM // Gera o código intermediário
    
    CodeGenerator codeGen;
    codeGen.setProgramTitle("TOC Program");
    codeGen.generateExecutableCode(SYNTAX_TREE);
    
#else // Ou imprime a árvore sintática
    
    SYNTAX_TREE->print();
    
#endif
    
    return 0;
}
