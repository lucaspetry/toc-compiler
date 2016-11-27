#include "UnaryOperation.h"

UnaryOperation::UnaryOperation(UnaryOperation::Type operation, TreeNode* right) : TreeNode(Data::UNKNOWN) {
    this->operation = operation;
    this->right = right;
}

UnaryOperation::~UnaryOperation() {
}

TreeNode::ClassType UnaryOperation::classType() const {
    return TreeNode::UNARY_OPERATION;
}

std::string UnaryOperation::printInOrder() const {
    std::string output = "";
    output += operationToString(operation) + " ";
    return output + right->printInOrder();
}

void UnaryOperation::setBody(CodeBlock* codeBlock) {
}

std::string UnaryOperation::operationToString(UnaryOperation::Type operation) const{
    switch(operation) {
        case MINUS:
            return "-u";
        case NOT:
            return "not";
        default:
            return "unknown";
    }
}
