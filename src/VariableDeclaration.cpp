#include "VariableDeclaration.h"

VariableDeclaration::VariableDeclaration(Data::Type type, TreeNode* next) : TreeNode(type) {
    this->next = next;
    this->type = type;
    this->encapsulation = 2;
}

VariableDeclaration::~VariableDeclaration() {
}

TreeNode::ClassType VariableDeclaration::classType() const {
    return TreeNode::VARIABLE_DECLARATION;
}

std::string VariableDeclaration::printInOrder() const {
    std::string output = "";
    switch (encapsulation) {
      case 0: output+= "pub ";
      break;
      case 1: output+= "prv ";
      break;
      default: break;
    }
    output+= Data::toString(this->type) + " ";
    output += next->printInOrder();
    return output;
}

TreeNode* VariableDeclaration::getNext() {
    return this->next;
}

void VariableDeclaration::setBody(CodeBlock* codeBlock) {
}

void VariableDeclaration::setEncapsulation(int n){
  this->encapsulation = n;
}
