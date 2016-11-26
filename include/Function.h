#ifndef FUNCTION_H_
#define FUNCTION_H_

#include <string>
#include "TreeNode.h"
#include "CodeBlock.h"

/**
 * Função
 */
class Function : public TreeNode {

    public:
        Function(std::string id, CodeBlock* params, CodeBlock* body, TreeNode* ret);
        virtual ~Function();
        TreeNode::ClassType classType() const;
        std::string printInOrder() const;
        llvm::Value* generateCode();
        void setBody(CodeBlock* codeBlock);

    protected:
      std::string id;
      CodeBlock* params;
      CodeBlock* body;
      TreeNode* ret;

};

#endif
