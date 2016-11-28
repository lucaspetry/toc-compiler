#ifndef CONDITIONAL_H_
#define CONDITIONAL_H_

#include <string>
#include "TreeNode.h"
#include "CodeBlock.h"

/**
 * Condicional
 */
class Conditional : public TreeNode {

  friend class SemanticAnalyzer;
    public:
        Conditional(TreeNode* conditional, CodeBlock* body, bool elsing);
        virtual ~Conditional();
        TreeNode::ClassType classType() const;
        std::string printInOrder() const;
        void setBody(CodeBlock* codeBlock);
        llvm::Value* generateCode();

    private:
      TreeNode* condition;
      CodeBlock* body;
      bool elsing;

};

#endif
