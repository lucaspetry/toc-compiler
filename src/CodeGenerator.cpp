#include "CodeGenerator.h"

CodeGenerator::CodeGenerator() {
    
}

CodeGenerator::~CodeGenerator() {
    
}

void CodeGenerator::setProgramTitle(std::string title) {
    this->programTitle = title;
}

void CodeGenerator::generateExecutableCode(SyntaxTree* const syntaxTree) const {
    llvm::LLVMContext &context = llvm::getGlobalContext();
    llvm::Module *module;
    llvm::IRBuilder<> builder(context);

    std::unique_ptr<llvm::Module> owner = llvm::make_unique<llvm::Module>(this->programTitle, context);
    module = owner.get();

    // Função do programa
    llvm::Type* intType = llvm::Type::getInt64Ty(context);
    llvm::FunctionType* typeOfMain = llvm::FunctionType::get(intType, false);
    llvm::Function* mainFunction = llvm::Function::Create(typeOfMain, llvm::Function::ExternalLinkage, "main", module);

    // Bloco básico principal
    llvm::BasicBlock *mainBB = llvm::BasicBlock::Create(context, "main", mainFunction);
    builder.SetInsertPoint(mainBB);
    
    // Gera o código do programa
    syntaxTree->generateCode(&builder);

    // Verifica a função principal
    llvm::verifyFunction(*mainFunction);

    // Imprime o código gerado
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