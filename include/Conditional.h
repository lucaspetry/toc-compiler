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
        Conditional(TreeNode* condition, CodeBlock* thenCode, CodeBlock* elseCode);
        virtual ~Conditional();
        TreeNode::ClassType classType() const;
        std::string printInOrder() const;
        bool hasElse() const;
        void setElse(bool settingElse);
        void setBody(CodeBlock* codeBlock);
        llvm::Value* generateCode();

    private:
      TreeNode* condition;
      CodeBlock* thenCode;
      CodeBlock* elseCode;
      bool settingElse;

};

#endif
