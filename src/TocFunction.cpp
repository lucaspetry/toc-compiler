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
    // llvm::Type* intType = llvm::Type::getInt64Ty(IR::Context);
    // llvm::AllocaInst * A = IR::Builder.CreateAlloca(intType,NULL,"A");
    // IR::Builder.CreateStore(IR::Zero,A);
    this->body->generateCode();

    return mainBB;
}
