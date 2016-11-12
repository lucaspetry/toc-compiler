#include "PrintFunction.h"

PrintFunction::PrintFunction(TreeNode* param) : Function("print", NULL, NULL, NULL) {
    CodeBlock* body = new CodeBlock(0);
    body->insertLine(param);
    this->body = body;
}

PrintFunction::~PrintFunction() {
}

TreeNode::ClassType PrintFunction::classType() const {
    return TreeNode::PRINT_FUNCTION;
}

std::string PrintFunction::printInOrder() const {
    // Print especial
    return "";
}

/**
 * llvm::Value* PrintFunction::generateCode() no CodeGenerator.cpp
 */