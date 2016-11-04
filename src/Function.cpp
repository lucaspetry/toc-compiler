#include "Function.h"

Function::Function(std::string id, CodeBlock* params, CodeBlock* body) : TreeNode(Data::UNKNOWN) {
    this->params = params;
    this->body = body;
}

Function::~Function() {

}

TreeNode::ClassType Function::classType() const {
    return TreeNode::FUNCTION;
}

std::string Function::printInOrder() const {
    std::string output;
    output += this->id;
    return output;
}
