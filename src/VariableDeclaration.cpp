#include "VariableDeclaration.h"

VariableDeclaration::VariableDeclaration(Data::Type type, TreeNode* next) : TreeNode(type) {
    this->next = next;

}

VariableDeclaration::~VariableDeclaration() {
}

TreeNode::ClassType VariableDeclaration::classType() const {
    return TreeNode::VARIABLE_DECLARATION;
}

std::string VariableDeclaration::printInOrder() const {
    std::string output = toString(this->type);
    output+= next->printInOrder();
    return output;
}

/**
 * llvm::Value* VariableDeclaration::generateCode() no CodeGenerator.cpp
 */