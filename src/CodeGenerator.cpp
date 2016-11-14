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
#include "String.h"
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
    
//    llvm::Function* printFunction = llvm::Function::Create(llvm::FunctionType::get(voidType, false), llvm::Function::ExternalLinkage, "putchard", IR::Module);
//    executionEngine->addGlobalMapping(printFunction, &putchard);

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
        llvm::Value* newValue = IR::Builder->CreateAdd(right->generateCode(), IR::Zero, lvar->getId().c_str());
        this->symbolTable.updateVariableAllocation(lvar->getId(), newValue);
        return newValue;
    } else {
        switch(this->operation) {
            case BinaryOperation::DIVIDE:
                return IR::Builder->CreateFDiv(left->generateCode(), right->generateCode(), "divtmp");
            case BinaryOperation::MINUS:
                return IR::Builder->CreateSub(left->generateCode(), right->generateCode(), "subtmp");
            case BinaryOperation::PLUS:
                return IR::Builder->CreateAdd(left->generateCode(), right->generateCode(), "addtmp");
            case BinaryOperation::TIMES:
                return IR::Builder->CreateMul(left->generateCode(), right->generateCode(), "multmp");
            default:
                return NULL;
        }
    }

}

llvm::Value* Boolean::generateCode() {
    // TODO não sei se isso está ok
    bool equivalent = value ? 1 : 0;
    return llvm::ConstantInt::get(IR::Context, llvm::APInt(64, equivalent));
}

llvm::Value* CodeBlock::generateCode() {
    for (TreeNode* line: lines) {
        line->generateCode();
    }

    return NULL;
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
    IR::Module->getOrInsertFunction("printf",
                                   llvm::FunctionType::get(llvm::IntegerType::getInt32Ty(IR::Context), llvm::PointerType::get(llvm::Type::getInt8Ty(IR::Context), 0), true));
    llvm::Function *printFunction = IR::Module->getFunction("printf");
    std::vector<llvm::Value*> args;
    args.push_back(this->body->getLine(0)->generateCode());//llvm::ConstantDataArray::getString(IR::Context, llvm::StringRef("test"), true));
    return IR::Builder->CreateCall(printFunction, args, "printfCall");
}

llvm::Value* String::generateCode() {
    llvm::GlobalVariable* gvar_array__str = new llvm::GlobalVariable(/*Module=*/*IR::Module, 
    /*Type=*/llvm::ArrayType::get(llvm::IntegerType::get(IR::Context, 32), 5),
    /*isConstant=*/true,
    /*Linkage=*/llvm::GlobalValue::PrivateLinkage,
    /*Initializer=*/0, // has initializer, specified below
    /*Name=*/".str");
    gvar_array__str->setAlignment(1);

    // Constant Definitions
    llvm::Constant *const_array_4 = llvm::ConstantDataArray::getString(IR::Context, this->value.c_str(), true);
//    std::vector<llvm::Constant*> const_ptr_5_indices;
//    llvm::ConstantInt* const_int64_6 = llvm::ConstantInt::get(IR::Context, llvm::APInt(64, llvm::StringRef("0"), 10));
//    const_ptr_5_indices.push_back(const_int64_6);
//    const_ptr_5_indices.push_back(const_int64_6);
//    llvm::Constant* const_ptr_5 = llvm::ConstantExpr::getGetElementPtr(gvar_array__str, const_ptr_5_indices);

    // Global Variable Definitions
    gvar_array__str->setInitializer(const_array_4);
    
    return gvar_array__str;
}

llvm::Value* TocFunction::generateCode() {
    IR::TocFunction = llvm::BasicBlock::Create(IR::Context, "toc", IR::MainFunction);
    IR::Builder->SetInsertPoint(IR::TocFunction);
    
    this->body->generateCode();    
    
    std::cout << "test print" << std::endl;
//    llvm::Type* voidType = llvm::Type::getVoidTy(IR::Context);
//    IR::Module->getOrInsertFunction("putchard", llvm::FunctionType::get(voidType, false));
//    llvm::Function* printFunction = IR::Module->getFunction("putchard");
//    std::vector<llvm::Value*> arguments;
//    arguments.push_back(llvm::ConstantInt::get(IR::Context, llvm::APInt(64, 41)));
//    IR::Builder->CreateCall(printFunction, arguments, "callprint");
//    
//    std::cout << "test print2" << std::endl;
    
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