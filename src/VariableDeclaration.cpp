#include "VariableDeclaration.h"

VariableDeclaration::VariableDeclaration(Data::Type type, TreeNode* next) : TreeNode(type) {
    this->next = next;
    this->type = type;
}

VariableDeclaration::~VariableDeclaration() {
}

TreeNode::ClassType VariableDeclaration::classType() const {
    return TreeNode::VARIABLE_DECLARATION;
}

std::string VariableDeclaration::printInOrder() const {
    std::string output = toString(this->type) + " ";
    output += next->printInOrder();
    return output;
}

TreeNode* VariableDeclaration::getNext() {
    return this->next;
}