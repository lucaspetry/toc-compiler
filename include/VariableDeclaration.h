#ifndef VARIABLEDECLARATION_H_
#define VARIABLEDECLARATION_H_

#include "TreeNode.h"

class VariableDeclaration : public TreeNode {

    public:
        VariableDeclaration(Data::Type type, TreeNode* next);
        virtual ~VariableDeclaration();
        TreeNode::ClassType classType() const;
        std::string printInOrder() const;
        virtual void generateCode() const;

    private:
        TreeNode* next;

};

#endif
