#include "SyntaxTree.h"

SyntaxTree::SyntaxTree() {
}

SyntaxTree::~SyntaxTree() {
}

void SyntaxTree::print() {
    for (TreeNode* line: lines) {
        std::string toPrint = line->printInOrder();

        if(toPrint.back() == ' ') {
            toPrint = toPrint.substr(0, toPrint.length()-1);
        }

        std::cout << toPrint << std::endl;
    }
}

void SyntaxTree::generateCode(llvm::LLVMContext &Context) {
    for (TreeNode* line: lines) {
        line->generateCode();
    }
    // llvm::BasicBlock *mainBB = llvm::BasicBlock::Create(Context, "toc", IR::MainFunction);
    // IR::Builder.SetInsertPoint(mainBB);
    // llvm::Type* intType = llvm::Type::getInt64Ty(Context);
    // llvm::AllocaInst * A = IR::Builder.CreateAlloca(intType,NULL,"A");
    // IR::Builder.CreateStore(IR::Zero,A);
    // IR::Builder.CreateStore(IR::Zero,IR::Zero); //5
    // llvm::Value* x = IR::Builder.CreateLoad(A,"x");
    
    // IR::Builder.CreateStore(x,A);
    // IR::Builder.CreateRet(x);
}

void SyntaxTree::insertLine(TreeNode* line) {
    this->lines.insert(lines.begin(), line);
}
