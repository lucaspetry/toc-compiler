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
    llvm::LLVMContext &context = llvm::getGlobalContext();
    llvm::Type* intType = llvm::Type::getInt64Ty(context);
    
    /**
     *    APENAS UM TESTE
     */
    
    /*** Constants are all unified ***/
    /* http://llvm.org/docs/doxygen/html/classllvm_1_1ConstantInt.html
     * static ConstantInt *	get (LLVMContext &context, const APInt &V)
     * Return a ConstantInt with the specified value and an implied Type.
     * APInt = Arbitrary Precision Integer */
    llvm::ConstantInt* Ten = llvm::ConstantInt::get(context, llvm::APInt(64,10));
    auto One = llvm::ConstantInt::get(context, llvm::APInt(64, 1));
    auto Zero = llvm::ConstantInt::get(context, llvm::APInt(64, 0));

    /* static ConstantInt *	get (IntegerType *Ty, uint64_t V, bool isSigned=false)
     * Return a ConstantInt with the specified integer value for the specified type. */
    llvm::Constant* NegativeOne = llvm::ConstantInt::get( intType, -1, true);

    /*** A and B are variables in memory, so we can read and write from them ***/

    /* http://llvm.org/docs/doxygen/html/classllvm_1_1IRBuilder.html
     * AllocaInst * 	CreateAlloca (Type *Ty, Value *ArraySize=nullptr, const Twine &Name="") */
    llvm::AllocaInst* A = builder->CreateAlloca(intType, NULL, "A");

    /*** lets compute
     * 0. A = 0;
     * 1. x = A;
     * 2. y = 0;
     * 3. x = y + 10 - (-1) + x;
     * 4. x = x + 1 + 10 + 10 + 10
     * 5. A = x;
     * 6. return x;
     ***/
    builder->CreateStore(Zero, A); //0
    llvm::Value* x = builder->CreateLoad(A, "x"); //1
    auto y = builder->CreateAdd(Zero, Zero, "y"); //2 (one way to set to zero ;)
    auto tmp = builder->CreateAdd(y, Ten, "tmp"); //3.1
    tmp = builder->CreateSub(tmp, NegativeOne, "tmp"); //3.2
    x = builder->CreateAdd(tmp, x, "x"); //3.3
    x = builder->CreateAdd(x, One, "x"); //4
    x = builder->CreateAdd(x, Ten, "x"); //4
    x = builder->CreateAdd(x, Ten, "x"); //4
    x = builder->CreateAdd(x, Ten, "x"); //4
    builder->CreateStore(x, A); //5
    builder->CreateRet(x); //6
    
    
    for (TreeNode* line: lines) {
        line->generateCode(builder);
    }
}

void SyntaxTree::insertLine(TreeNode* line) {
    this->lines.insert(lines.begin(), line);
}
