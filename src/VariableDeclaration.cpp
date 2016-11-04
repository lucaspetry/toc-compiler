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
    return typeToString(this->type) + next->printInOrder();
}
void VariableDeclaration::generateCode() const {
  //TODO;
}
std::string VariableDeclaration::typeToString(Data::Type type) const {
    switch(type) {
        case Data::INT:
            return "int";
        case Data::BOO:
            return "bool";
        case Data::FLT:
            return "float";
        default:
            return "unknown";
    }
}
