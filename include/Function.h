#ifndef FUNCTION_H_
#define FUNCTION_H_

#include "TreeNode.h"
#include "CodeBlock.h"
#include <string>

/**
 * Função
 */
class Function : public TreeNode {

    public:
        Function(std::string id, CodeBlock* params, CodeBlock* body, TreeNode* ret);
        virtual ~Function();
        TreeNode::ClassType classType() const;
        std::string printInOrder() const;
        std::string getId() const;
        void setReturn(TreeNode* t);
        void setBody(CodeBlock* codeBlock);
        void setEncapsulation(int value);
        llvm::Value* generateCode();

    protected:
        std::string id;
        CodeBlock* params;
        CodeBlock* body;
        TreeNode* ret;
        int encapsulation;

};

#endif
