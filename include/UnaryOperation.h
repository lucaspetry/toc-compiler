#ifndef UNARYOPERATION_H_
#define UNARYOPERATION_H_

#include "TreeNode.h"
#include "Variable.h"

/**
 * Operação unária 
 */
class UnaryOperation : public TreeNode {

    public:
        enum Type {
            MINUS,
            NOT
        };

        UnaryOperation(Type operation, TreeNode* right);
        virtual ~UnaryOperation();
        TreeNode::ClassType classType() const;
        std::string printInOrder() const;
        llvm::Value* generateCode();
        std::string operationToString(UnaryOperation::Type operation) const;

    private:
        Type operation;
        TreeNode* right;

};

#endif
