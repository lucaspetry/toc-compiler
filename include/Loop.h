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
        llvm::Value* generateCode();

    private:
      TreeNode* init;
      TreeNode* test;
      TreeNode* attribuition;
      TreeNode* body;

};
#endif
