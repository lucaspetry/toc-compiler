#ifndef Loop_H_
#define Loop_H_

#include <string>
#include "TreeNode.h"

/**
 * Loop
 */
class Loop : public TreeNode {

    public:
        Loop(TreeNode* init, TreeNode* test, TreeNode* attribuition, TreeNode* body);
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
      TreeNode* body;

};
#endif
