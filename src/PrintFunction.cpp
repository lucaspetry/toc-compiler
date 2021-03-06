#include "PrintFunction.h"

PrintFunction::PrintFunction(TreeNode* param) : Function("print", NULL, NULL, NULL) {
    CodeBlock* body = new CodeBlock(0);
    body->insertLineFront(param);
    this->body = body;
}

PrintFunction::~PrintFunction() {
}

TreeNode::ClassType PrintFunction::classType() const {
    return TreeNode::PRINT_FUNCTION;
}

std::string PrintFunction::printInOrder() const {
    return "print " + this->body->printInOrder();
}
