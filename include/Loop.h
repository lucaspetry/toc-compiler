#ifndef LOOP_H_
#define LOOP_H_

#include "TreeNode.h"
#include "CodeBlock.h"
#include "Variable.h"
#include "VariableDeclaration.h"
#include "Array.h"
#include <string>

/**
 * Laço
 */
class Loop : public TreeNode {

    public:
        Loop(TreeNode* init, TreeNode* test, TreeNode* attribuition);
        virtual ~Loop();
        TreeNode::ClassType classType() const;
        std::string printInOrder() const;
        void setBody(CodeBlock* codeBlock);
        llvm::Value* generateCode();

    private:
      TreeNode* init;
      TreeNode* test;
      TreeNode* attribuition;
      CodeBlock* body;
};
#endif
