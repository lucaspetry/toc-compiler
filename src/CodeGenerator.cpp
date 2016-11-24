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
#include "UnaryOperation.h"

CodeGenerator::CodeGenerator() {

}

CodeGenerator::~CodeGenerator() {

}

void CodeGenerator::setProgramTitle(std::string title) {
    this->programTitle = title;
}

void CodeGenerator::generateExecuteCode(SyntaxTree* const syntaxTree) const {
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

    // Imprime o código gerado
#ifdef LLVM_DUMP
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
}

void SyntaxTree::generateCode() {
    for (TreeNode* line: lines) {
        line->generateCode();
    }
}

llvm::Value* BinaryOperation::generateCode() {
    if (this->operation == BinaryOperation::ASSIGN) {
      std::cout << "1" << std::endl;
        Variable* lvar = dynamic_cast<Variable *>(left); // TODO pode ser VariableDeclaration
        std::cout << "2" << std::endl;
        llvm::Value* newValue = IR::Builder->CreateAdd(right->generateCode(), IR::Zero, lvar->getId().c_str());
        std::cout << "3" << std::endl;
        this->symbolTable.updateVariableAllocation(lvar->getId(), newValue);
          std::cout << "4" << std::endl;

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

llvm::Value* UnaryOperation::generateCode(){
    return NULL; //TODO
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
    return NULL; //TODO;
}

llvm::Value* Integer::generateCode() {
    return llvm::ConstantInt::get(IR::Context, llvm::APInt(64, value));
}

llvm::Value* PrintFunction::generateCode() {
    IR::Module->getOrInsertFunction("printf",
                                   llvm::FunctionType::get(llvm::IntegerType::getInt32Ty(IR::Context), llvm::PointerType::get(llvm::Type::getInt8Ty(IR::Context), 0), true));
    llvm::Function *printFunction = IR::Module->getFunction("printf");
    std::vector<llvm::Value*> args;
    args.push_back(this->body->getLine(0)->generateCode());
    // OURO ABAIXO
    // IR::Builder->CreateGlobalString(llvm::StringRef(strPrint), llvm::Twine("str"), 3 /* ADDRESS_SPACE_SHARED */)
    return IR::Builder->CreateCall(printFunction, args, "printfCall");
}

llvm::Value* String::generateCode() {
    llvm::GlobalVariable* globalString = new llvm::GlobalVariable(
        /*Module=*/     *IR::Module,
        /*Type=*/       llvm::ArrayType::get(llvm::IntegerType::get(IR::Context, 32), this->value.size()),
        /*isConstant=*/ false,
        /*Linkage=*/    llvm::GlobalValue::PrivateLinkage,
        /*Initializer=*/0,
        /*Name=*/       ".str");
    globalString->setAlignment(1);

    llvm::Constant *arrayString = llvm::ConstantDataArray::getString(IR::Context, this->value.c_str(), true);
    globalString->setInitializer(arrayString);

    return globalString;
}

llvm::Value* TocFunction::generateCode() {
    IR::TocFunction = llvm::BasicBlock::Create(IR::Context, "toc", IR::MainFunction);
    IR::Builder->SetInsertPoint(IR::TocFunction);

    this->body->generateCode();

    IR::Builder->SetInsertPoint(IR::TocFunction);
    IR::Builder->CreateRetVoid();

    return IR::TocFunction;
}

llvm::Value* TypeCasting::generateCode(){
  switch(this->left){
      case Data::INT:
          if (next->dataType() == Data::FLT)
            return new llvm::FPToSIInst(next->generateCode(), llvm::IntegerType::getInt32Ty(IR::Context), "conv");
        break;
      case Data::FLT:
          if (next->dataType() == Data::INT)
            return new llvm::SIToFPInst(next->generateCode(), llvm::Type::getFloatTy(IR::Context), "conv");
        break;
      case Data::STR:
        break;
      case Data::BOO:
        break;
      default: return NULL;
  }
  return NULL;//TODO
}

llvm::Value* Variable::generateCode() {
    return this->symbolTable.getVariableAllocation(id);
}

llvm::Value* VariableDeclaration::generateCode() {
    return next->generateCode();
}

llvm::Value* Array::generateCode(){
  // http://stackoverflow.com/questions/35228471/how-to-create-llvm-array-type-using-allocainst
  // llvm::Type* I;
  // switch (this->type) {
  //     I = llvm::IntegerType::getInt32Ty(IR::Context); // cria um inteiro de qualquer forma
  //     break;
  // }
  // int num = ((Integer*)this->size)->getValue();
  // llvm::ArrayType* arrayType = llvm::ArrayType::get(I, 0);
  //
  // llvm::AllocaInst* arr_alloc = new llvm::AllocaInst(arrayType, "name");
  //
  // return arr_alloc;
}
