#ifndef CODEGENERATOR_H_
#define CODEGENERATOR_H_

#include "SyntaxTree.h"
#include "LLVM.h"
#include <iostream>
#include <string>

/**
 * Gerador de código intermediário (LLVM)
 */
class CodeGenerator {

    public:
        /**
         * Construir um gerador de código intermediário 
         */
        CodeGenerator();
    
        /**
         * Destruir o gerador de código intermediário 
         */
        virtual ~CodeGenerator();
    
        /**
         * Definir o título do programa
         * @param title título
         */
        void setProgramTitle(std::string title);
    
        /**
         * Definir se o dump é exibido
         * @param showDump true se o dump deve ser mostrado
         */
        void setDump(bool showDump);
    
        /**
         * Gerar o código intermediário e executar-lo
         * @param syntaxTree árvore sintática para a qual será gerado o programa
         */
        void generateExecuteCode(SyntaxTree* const syntaxTree) const;

    private:
        std::string programTitle;
        bool showDump;

};

#endif
