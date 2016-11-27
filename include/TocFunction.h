#ifndef TOCFUNCTION_H_
#define TOCFUNCTION_H_

#include "Function.h"

/**
 * Função TOC (função principal do programa)
 */
class TocFunction : public Function {

    public:
        TocFunction(CodeBlock* body);
        virtual ~TocFunction();
        TreeNode::ClassType classType() const;
        llvm::Value* generateCode();
        std::string toLLVMString();

};

#endif
