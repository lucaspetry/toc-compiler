#ifndef TOCFUNCTION_H_
#define TOCFUNCTION_H_

#include "Function.h"

class TocFunction : public Function {

    public:
        TocFunction(CodeBlock* body);
        virtual ~TocFunction();
        TreeNode::ClassType classType() const;
        llvm::Value* generateCode(llvm::IRBuilder<>* builder);

};

#endif
