#ifndef BINARYOPERATION_H_
#define BINARYOPERATION_H_

#include "TreeNode.h"

class BinaryOperation : public TreeNode {

    public:
        enum Type {
            ASSIGN,
            COMMA
        };

        BinaryOperation(TreeNode* left, Type operation, TreeNode* right);
        virtual ~BinaryOperation();
        TreeNode::ClassType classType() const;
        std::string printInOrder() const;
        std::string operationToString(Type operation) const;

    private:
        Type operation;
        TreeNode* left;
        TreeNode* right;

};

#endif
