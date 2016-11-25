#ifndef CONDITIONAL_H_
#define CONDITIONAL_H_

#include <string>
#include "TreeNode.h"
#include "CodeBlock.h"

/**
 * Condicional
 */
class Conditional : public TreeNode {

    public:
        Conditional(TreeNode* conditional, CodeBlock* body);
        Conditional(TreeNode* conditional, CodeBlock* bodyIf, CodeBlock* bodyElse);
        virtual ~Conditional();
        TreeNode::ClassType classType() const;
        std::string printInOrder() const;
        llvm::Value* generateCode();

    private:
      TreeNode* condition;
      CodeBlock* bodyIf;
      CodeBlock* bodyElse;

};

#endif
