#include "CodeGenerator.h"
#include <iostream>

CodeGenerator::CodeGenerator() {

}

CodeGenerator::~CodeGenerator() {

}

void CodeGenerator::setProgramTitle(std::string title) {
    this->programTitle = title;
}

void CodeGenerator::generateExecutableCode(SyntaxTree* const syntaxTree) const {
    std::unique_ptr<llvm::Module> owner = llvm::make_unique<llvm::Module>(this->programTitle, IR::Context);
    IR::Module = owner.get();

    // Função do programa
    llvm::Type* intType = llvm::Type::getInt64Ty(IR::Context);
    llvm::FunctionType* typeOfMain = llvm::FunctionType::get(intType, false);
    IR::MainFunction = llvm::Function::Create(typeOfMain, llvm::Function::ExternalLinkage, "main", IR::Module);

    // Gera o código do programa
    syntaxTree->generateCode();

    // Verifica a função principal
    llvm::verifyFunction(*IR::MainFunction);

#ifdef LLVM_DUMP
    // Imprime o código gerado
    std::cout << "###########  LLVM Intermediate Representation  ###########\n\n";
    IR::Module->dump();
    std::cout << "\n";
    std::cout << "##################  LLVM Code Execution  #################\n\n";
#endif

    // Executa o código intermediário com o LLVM
    std::string Error;
    LLVMInitializeNativeAsmPrinter();
    LLVMInitializeNativeAsmParser();
    LLVMInitializeNativeAsmPrinter(); //target = generates code for my processor
    llvm::ExecutionEngine* executionEngine =
                            llvm::EngineBuilder(std::move(owner))
                                            .setErrorStr(&Error)
                                            .setMCPU(llvm::sys::getHostCPUName())
                                            .create();

    if (!executionEngine) {
        fprintf(stderr, "Could not create executionEngine: %s\n", Error.c_str());
        exit(1);
    }

    // Executa a função principal e imprime o resultado
    std::vector<llvm::GenericValue> noargs;
    llvm::GenericValue gv = executionEngine->runFunction(IR::MainFunction, noargs);
    int result = gv.IntVal.getSExtValue();
    std::cout << "Result: " << result << std::endl;

}
