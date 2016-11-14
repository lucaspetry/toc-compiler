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
    std::string output = "";
    if(this->type != Data::UNKNOWN){
      output += toString(this->type);
      output += " ";
    }
    output += next->printInOrder();
    return output;
}
