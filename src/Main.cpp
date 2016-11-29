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

    CodeGenerator codeGen;

#ifdef LLVM_DUMP
    codeGen.setDump(true);
#endif

#ifdef LLVM // Gera o código intermediário
    if(!ERROR_LOGGER->hasErrors()) {
        codeGen.setProgramTitle("TOC Program");    
        codeGen.generateExecuteCode(SYNTAX_TREE);
    }
#else // Ou imprime a árvore sintática

    SYNTAX_TREE->print();

#endif

    return 0;
}
