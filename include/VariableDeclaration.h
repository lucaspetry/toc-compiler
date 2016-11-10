#ifndef VARIABLEDECLARATION_H_
#define VARIABLEDECLARATION_H_

#include "TreeNode.h"

class VariableDeclaration : public TreeNode {

    public:
        VariableDeclaration(Data::Type type, TreeNode* next);
        virtual ~VariableDeclaration();
        TreeNode::ClassType classType() const;
        std::string printInOrder() const;
        llvm::Value* generateCode(llvm::IRBuilder<>* builder);

    private:
        TreeNode* next;

};

#endif