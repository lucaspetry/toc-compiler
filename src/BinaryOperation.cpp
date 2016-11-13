#include "BinaryOperation.h"

BinaryOperation::BinaryOperation(TreeNode* left, BinaryOperation::Type operation, TreeNode* right) : TreeNode(Data::UNKNOWN) {
    this->left = left;
    this->operation = operation;
    this->right = right;
}

BinaryOperation::~BinaryOperation() {
}

TreeNode::ClassType BinaryOperation::classType() const {
    return TreeNode::BINARY_OPERATION;
}

std::string BinaryOperation::printInOrder() const {
    std::string output = left->printInOrder();
    output += " ";

    output += operationToString(operation) + " ";
return output + right->printInOrder();
}

std::string BinaryOperation::operationToString(BinaryOperation::Type operation) const {
    switch(operation) {
        case BinaryOperation::ASSIGN:
            return "=";
        default:
            return "unknown";
    }
}

/**
 * llvm::Value* BinaryOperation::generateCode() no CodeGenerator.cpp
 */