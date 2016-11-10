#ifndef BINARYOPERATION_H_
#define BINARYOPERATION_H_

#include "TreeNode.h"
#include "Variable.h"

class BinaryOperation : public TreeNode {

    public:
        enum Type {
            COMMA,
            ASSIGN,
            UNKNOWN
        };

        BinaryOperation(TreeNode* left, Type operation, TreeNode* right);
        virtual ~BinaryOperation();
        TreeNode::ClassType classType() const;
        std::string printInOrder() const;
        std::string operationToString(Type operation) const;
        void generateCode(llvm::IRBuilder<>* builder);
    
    private:
        Type operation;
        TreeNode* left;
        TreeNode* right;

};

#endif
