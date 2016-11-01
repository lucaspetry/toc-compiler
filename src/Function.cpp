#include "Function.h"

Function::Function(std::string id, CodeBlock* params, CodeBlock* body) : TreeNode(Data::UNKNOWN) {

}

Function::~Function() {

}

TreeNode::ClassType Function::classType() const {
    return TreeNode::FUNCTION;
}

std::string Function::printInOrder() const {
    return ""; // TODO
}
