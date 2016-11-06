#include "CodeGenerator.h"

CodeGenerator::CodeGenerator() {
    
}

CodeGenerator::~CodeGenerator() {
    
}

void CodeGenerator::setProgramTitle(std::string title) {
    this->programTitle = title;
}

void CodeGenerator::generateExecutableCode() const {
    llvm::LLVMContext &context = llvm::getGlobalContext();
    llvm::Module *module;
    llvm::IRBuilder<> builder(context);

    std::unique_ptr<llvm::Module> owner = llvm::make_unique<llvm::Module>(this->programTitle, context);
    module = owner.get();

    // Função do programa
    llvm::Type* intType = llvm::Type::getInt64Ty(context);
    llvm::FunctionType* typeOfMain = llvm::FunctionType::get(intType, false);
    llvm::Function* mainFunction = llvm::Function::Create(typeOfMain, llvm::Function::ExternalLinkage, "main", module);

    // Blobo básico principal
    llvm::BasicBlock *mainBB = llvm::BasicBlock::Create(context, "main", mainFunction);
    builder.SetInsertPoint(mainBB);

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
    llvm::AllocaInst* A = builder.CreateAlloca(intType, NULL, "A");
    llvm::AllocaInst* B = builder.CreateAlloca(intType, NULL, "B");

    /*** lets compute
     * 0. A = 0;
     * 1. x = A;
     * 2. y = 0;
     * 3. x = y + 10 - (-1) + x;
     * 4. x = x + 1 + 10 + 10 + 10
     * 5. A = x;
     * 6. return x;
     ***/
    builder.CreateStore(Zero, A); //0
    llvm::Value* x = builder.CreateLoad(A, "x"); //1
    auto y = builder.CreateAdd(Zero, Zero, "y"); //2 (one way to set to zero ;)
    auto tmp = builder.CreateAdd(y, Ten, "tmp"); //3.1
    tmp = builder.CreateSub(tmp, NegativeOne, "tmp"); //3.2
    x = builder.CreateAdd(tmp, x, "x"); //3.3
    x = builder.CreateAdd(x, One, "x"); //4
    x = builder.CreateAdd(x, Ten, "x"); //4
    x = builder.CreateAdd(x, Ten, "x"); //4
    x = builder.CreateAdd(x, Ten, "x"); //4
    builder.CreateStore(x, A); //5
    builder.CreateRet(x); //6
    
    //Checks if everything is okay with our function
    llvm::verifyFunction(*mainFunction);

    // Lets print the intermediary representation generated
    module->dump();
    //mainFunction->dump();
//
//    /*** Now lets compute it with a just in time (JIT) compiler ***/
//    llvm::ExecutionEngine* OurExecutionEngine;
//    std::string Error;
//    LLVMInitializeNativeAsmPrinter();
//    LLVMInitializeNativeAsmParser();
//    LLVMInitializeNativeAsmPrinter(); //target = generates code for my processor
//    OurExecutionEngine = llvm::EngineBuilder(std::move(owner)).setErrorStr(&Error).setMCPU(llvm::sys::getHostCPUName()).create();
//    
//    if (!OurExecutionEngine) {
//        fprintf(stderr, "Could not create OurExecutionEngine: %s\n", Error.c_str());
//        exit(1);
//    }
//
//    // JIT our main. It returns a function pointer.
//    void *mainPointer = OurExecutionEngine->getPointerToFunction(mainFunction);
//    std::cout << "1\n";
//    // Translate the pointer and run our main to get its results
//    int (*result)() = (int (*)())(intptr_t)mainPointer;
//    std::cout << "Result of our main = " << result() << std::endl;
}