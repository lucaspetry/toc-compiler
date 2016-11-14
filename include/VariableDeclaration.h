#ifndef VARIABLEDECLARATION_H_
#define VARIABLEDECLARATION_H_

#include "TreeNode.h"

/**
  Class VariableDeclaration
**/

class VariableDeclaration : public TreeNode {

    public:
        VariableDeclaration(Data::Type type, TreeNode* next);
        virtual ~VariableDeclaration();
        TreeNode::ClassType classType() const;
        std::string printInOrder() const;
        llvm::Value* generateCode();

    private:
        TreeNode* next;

};

#endif
