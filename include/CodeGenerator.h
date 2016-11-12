#ifndef CODEGENERATOR_H_
#define CODEGENERATOR_H_

#include "SyntaxTree.h"
#include "LLVM.h"
#include <iostream>
#include <string>

class CodeGenerator {

    public:
        CodeGenerator();
        virtual ~CodeGenerator();
        void setProgramTitle(std::string title);
        void generateExecutableCode(SyntaxTree* const syntaxTree) const;

    private:
        std::string programTitle;

};

#endif
