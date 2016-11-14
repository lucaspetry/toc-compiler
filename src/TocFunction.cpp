#include "TocFunction.h"

TocFunction::TocFunction(CodeBlock* body) : Function("toc", NULL, body, NULL) {
    this->type = Data::VOID;
}

TocFunction::~TocFunction() {
}

TreeNode::ClassType TocFunction::classType() const {
    return TreeNode::TOC_FUNCTION;
}

/**
 * llvm::Value* TocFunction::generateCode() no CodeGenerator.cpp
 */