#include "TocFunction.h"

TocFunction::TocFunction(CodeBlock* body) : Function("toc", NULL, body, NULL) {
}

TocFunction::~TocFunction() {
}

TreeNode::ClassType TocFunction::classType() const {
    return TreeNode::TOC_FUNCTION;
}

llvm::Value* TocFunction::generateCode(llvm::IRBuilder<>* builder) {
    llvm::BasicBlock *mainBB = llvm::BasicBlock::Create(llvm::getGlobalContext(), "toc", IR::MainFunction);
    builder->SetInsertPoint(mainBB);
    
    return NULL;//TODO;
}
