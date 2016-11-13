#ifndef BINARYOPERATION_H_
#define BINARYOPERATION_H_

#include "TreeNode.h"
#include "Variable.h"

class BinaryOperation : public TreeNode {

  friend class SemanticAnalyzer;

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
        llvm::Value* generateCode();

    private:
        Type operation;
        TreeNode* left;
        TreeNode* right;

};

#endif
