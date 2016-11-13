#include "CodeGenerator.h"
#include <iostream>

#include "SyntaxTree.h"
#include "BinaryOperation.h"
#include "Boolean.h"
#include "Comment.h"
#include "Float.h"
#include "Function.h"
#include "Integer.h"
#include "PrintFunction.h"
#include "TocFunction.h"
#include "Variable.h"
#include "VariableDeclaration.h"

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
    llvm::Type* voidType = llvm::Type::getVoidTy(IR::Context);
    llvm::FunctionType* typeOfMain = llvm::FunctionType::get(voidType, false);
    IR::Module->getOrInsertFunction("main", typeOfMain);
    IR::MainFunction = IR::Module->getFunction("main");

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
    executionEngine->runFunction(IR::MainFunction, noargs);
    std::cout << "\nExecution finished!" << std::endl;

}

void SyntaxTree::generateCode() {
    for (TreeNode* line: lines) {
        line->generateCode();
    }
}

llvm::Value* BinaryOperation::generateCode() {
    if (this->operation == BinaryOperation::ASSIGN) {
        Variable* lvar = dynamic_cast<Variable *>(left); // TODO pode ser VariableDeclaration
        return IR::Builder->CreateAdd(right->generateCode(), IR::Zero, lvar->getId().c_str());
        lvar->generateCode();
        //symbolTable.updateVariableAllocation(lvar->getId(), lvar->generateCode());
    } else {
        left->generateCode(); // TODO
        right->generateCode(); // TODO
        switch(this->operation){
//            case plus:
//                code = IR::Builder->CreateAdd(left->code, right->code, "addtmp");
//                break;
//            case times:
//                code = IR::Builder->CreateMul(left->code, right->code, "multmp");
//                break;
            default:
                return NULL; //Not the greatest error capture, but okay for the example
                break;
        }
    }

}

llvm::Value* Boolean::generateCode() {
    // TODO não sei se isso está ok
    bool equivalent = value ? 1 : 0;
    return llvm::ConstantInt::get(IR::Context, llvm::APInt(64, equivalent));
}

llvm::Value* Comment::generateCode() {
    return NULL; // Doesn't generate any code.
}

llvm::Value* Float::generateCode() {
    return llvm::ConstantFP::get(IR::Context, llvm::APFloat(value));
}

llvm::Value* Function::generateCode() {
    return NULL;//TODO;
}

llvm::Value* Integer::generateCode() {
    return llvm::ConstantInt::get(IR::Context, llvm::APInt(64, value));
}

llvm::Value* PrintFunction::generateCode() {
    return NULL;//TODO;
}

llvm::Value* TocFunction::generateCode() {
    IR::TocFunction = llvm::BasicBlock::Create(IR::Context, "toc", IR::MainFunction);
    IR::Builder->SetInsertPoint(IR::TocFunction);

    this->body->generateCode();

    IR::Builder->SetInsertPoint(IR::TocFunction);
    IR::Builder->CreateRetVoid();

    return IR::TocFunction;
}

llvm::Value* Variable::generateCode() {
    return this->symbolTable.getVariableAllocation(id);
}

llvm::Value* VariableDeclaration::generateCode() {
    return next->generateCode();
}

llvm::Value* Array::generateCode(){
  return NULL;
};
