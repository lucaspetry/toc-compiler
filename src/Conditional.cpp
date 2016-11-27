#include "Conditional.h"
#include <iostream>


Conditional::Conditional(TreeNode* condition, CodeBlock* body, bool elsing) : TreeNode(Data::UNKNOWN) {
    this->condition = condition;
    this->body = body;
    this->elsing = elsing;
}

Conditional::~Conditional() {
}

TreeNode::ClassType Conditional::classType() const {
    if(this->elsing)
      return TreeNode::CONDITIONAL_ELSE;
    else
      return TreeNode::CONDITIONAL_IF;
}

std::string Conditional::printInOrder() const {
    std::string output = "";
    if(this->elsing == false) {
    output += "if "+ condition->printInOrder() + "\n";
    if(this->body != NULL)
        output += this->body->printInOrder();
    } else {
        output+= "else \n" ;
        if(this->body != NULL)
          output += this->body->printInOrder();
    }
    return output;

}

void Conditional::setBody(CodeBlock* codeBlock) {
    this->body = codeBlock;
}
