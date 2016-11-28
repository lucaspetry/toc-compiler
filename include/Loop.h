#ifndef Loop_H_
#define Loop_H_

#include <string>
#include "TreeNode.h"
#include "CodeBlock.h"
#include "Variable.h"
#include "VariableDeclaration.h"
#include "Array.h"

/**
 * Loop
 */
class Loop : public TreeNode {

    public:
        Loop(TreeNode* init, TreeNode* test, TreeNode* attribuition);
        virtual ~Loop();
        TreeNode::ClassType classType() const;
        std::string printInOrder() const;
        void setBody(CodeBlock* codeBlock);
        llvm::Value* generateCode();
        std::string toLLVMString();

    private:
      TreeNode* init;
      TreeNode* test;
      TreeNode* attribuition;
      CodeBlock* body;
};
#endif
