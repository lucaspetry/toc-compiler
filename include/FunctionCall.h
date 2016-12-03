#ifndef FUNCTIONCALL_H_
#define FUNCTIONCALL_H_

#include "TreeNode.h"
#include "CodeBlock.h"
#include <string>

/**
 * Função
 */
class FunctionCall : public TreeNode {

    public:
        FunctionCall(std::string id, CodeBlock* params);
        virtual ~FunctionCall();
        TreeNode::ClassType classType() const;
        std::string printInOrder() const;
        std::string getId() const;
        void setBody(CodeBlock* codeBlock);
        llvm::Value* generateCode();

    protected:
        std::string id;
        CodeBlock* params;

};

#endif
