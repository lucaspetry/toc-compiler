#include "TocFunction.h"

TocFunction::TocFunction(CodeBlock* body) : Function("toc", NULL, body, NULL) {
}

TocFunction::~TocFunction() {
}

TreeNode::ClassType TocFunction::classType() const {
    return TreeNode::TOC_FUNCTION;
}

llvm::Value* TocFunction::generateCode() {
    llvm::BasicBlock *mainBB = llvm::BasicBlock::Create(IR::Context, "toc", IR::MainFunction);
    IR::Builder.SetInsertPoint(mainBB);

    return mainBB;
}
