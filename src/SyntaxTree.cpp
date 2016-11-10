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

void SyntaxTree::generateCode(llvm::IRBuilder<>* builder) {    
    for (TreeNode* line: lines) {
        line->generateCode(builder);
    }
    
//    builder->CreateStore(x, A); //5
//    builder->CreateRet(x); //6
}

void SyntaxTree::insertLine(TreeNode* line) {
    this->lines.insert(lines.begin(), line);
}
