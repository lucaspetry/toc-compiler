#include "CodeGenerator.h"
#include <iostream>

#include "SyntaxTree.h"
#include "Array.h"
#include "BinaryOperation.h"
#include "Boolean.h"
#include "Comment.h"
#include "Float.h"
#include "Function.h"
#include "Integer.h"
#include "PrintFunction.h"
#include "String.h"
#include "Symbol.h"
#include "TocFunction.h"
#include "TypeCasting.h"
#include "Variable.h"
#include "VariableDeclaration.h"
#include "UnaryOperation.h"

CodeGenerator::CodeGenerator() {
    this->showDump = false;
}

CodeGenerator::~CodeGenerator() {

}

void CodeGenerator::setProgramTitle(std::string title) {
    this->programTitle = title;
}

void CodeGenerator::setDump(bool showDump) {
    this->showDump = showDump;
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
    if(this->showDump) {
        std::cout << "###########  LLVM Intermediate Representation  ###########\n\n";
        IR::Module->dump();
        std::cout << "\n";
        std::cout << "##################  LLVM Code Execution  #################\n\n";
    }

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

std::string Array::toLLVMString() {
    return "";
}

llvm::Value* BinaryOperation::generateCode() {
    if (this->operation == BinaryOperation::ASSIGN) {
        Variable* lvar = dynamic_cast<Variable*>(left);

        if(left->classType() == TreeNode::VARIABLE_DECLARATION)
            lvar = dynamic_cast<Variable*>((dynamic_cast<VariableDeclaration*>(left))->getNext());

        // TODO array?
        llvm::Value* newValue;

        switch(this->dataType()) {
            case Data::INT:
                newValue = IR::Builder->CreateAdd(right->generateCode(), IR::Zero, lvar->getId().c_str());
                break;
            case Data::FLT:
                newValue = IR::Builder->CreateFAdd(right->generateCode(), IR::ZeroFP, lvar->getId().c_str());
                break;
            default:
                newValue = IR::Builder->CreateFAdd(right->generateCode(), IR::ZeroFP, lvar->getId().c_str());
                break;
        }
        this->symbolTable.updateVariableAllocation(lvar->getId(), newValue);

        return newValue;
    } else {
        switch(this->operation) {
            case BinaryOperation::DIVIDE:
                return IR::Builder->CreateFDiv(left->generateCode(), right->generateCode(), "divtmp");
            case BinaryOperation::MINUS:
                return IR::Builder->CreateSub(left->generateCode(), right->generateCode(), "subtmp");
            case BinaryOperation::PLUS:
                switch(this->dataType()) {
                    case Data::INT:
                        return IR::Builder->CreateAdd(left->generateCode(), right->generateCode(), "addtmp");
                    case Data::FLT:
                        return IR::Builder->CreateFAdd(left->generateCode(), right->generateCode(), "addtmp");
                    default:
                        return IR::Builder->CreateFAdd(left->generateCode(), right->generateCode(), "addtmp");
                }
            case BinaryOperation::TIMES:
                return IR::Builder->CreateMul(left->generateCode(), right->generateCode(), "multmp");
            default:
                return NULL;
        }
    }
}

std::string BinaryOperation::toLLVMString() {
    return "";
}

llvm::Value* UnaryOperation::generateCode(){
    return NULL; //TODO
}

std::string UnaryOperation::toLLVMString() {
    return "";
}

llvm::Value* Boolean::generateCode() {
    // TODO não sei se isso está ok
    int equivalent = value ? 1 : 0;
    return llvm::ConstantInt::get(IR::Context, llvm::APInt(32, equivalent));
}

std::string Boolean::toLLVMString() {
    return this->value ? "true" : "false";
}

llvm::Value* CodeBlock::generateCode() {
    for (TreeNode* line: lines) {
        line->generateCode();
    }

    return NULL;
}

std::string CodeBlock::toLLVMString() {
    return "";
}

llvm::Value* Comment::generateCode() {
    return NULL; // Doesn't generate any code.
}

std::string Comment::toLLVMString() {
    return "";
}

llvm::Value* Float::generateCode() {
    return llvm::ConstantFP::get(IR::Context, llvm::APFloat(this->value));
}

std::string Float::toLLVMString() {
    return std::to_string(this->value);
}

llvm::Value* Function::generateCode() {
    return NULL; //TODO;
}

std::string Function::toLLVMString() {
    return "";
}

llvm::Value* Integer::generateCode() {
    return llvm::ConstantInt::get(IR::Context, llvm::APInt(32, value));
}

std::string Integer::toLLVMString() {
    return std::to_string(this->value);
}

llvm::Value* PrintFunction::generateCode() {
    IR::Module->getOrInsertFunction("printf",
                                   llvm::FunctionType::get(llvm::IntegerType::getInt32Ty(IR::Context), llvm::PointerType::get(llvm::Type::getInt8Ty(IR::Context), 0), true));
    llvm::Function *printFunction = IR::Module->getFunction("printf");
    std::vector<llvm::Value*> args;
    //llvm::Value* argStr = IR::Builder->CreateGlobalString(
    //    llvm::StringRef(this->body->getLine(0)->toLLVMString()), llvm::Twine("str"), 3 /* ADDRESS_SPACE_SHARED */);
    args.push_back(this->body->getLine(0)->generateCode());
    return IR::Builder->CreateCall(printFunction, args, "printfCall");
}

std::string PrintFunction::toLLVMString() {
    return "";
}

llvm::Value* String::generateCode() {
    llvm::GlobalVariable* globalString = new llvm::GlobalVariable(
        /*Module=*/     *IR::Module,
        /*Type=*/       llvm::ArrayType::get(llvm::IntegerType::get(IR::Context, 32), this->valuePrint.size()),
        /*isConstant=*/ false,
        /*Linkage=*/    llvm::GlobalValue::PrivateLinkage,
        /*Initializer=*/0,
        /*Name=*/       "str");
    globalString->setAlignment(1);

    llvm::Constant *arrayString = llvm::ConstantDataArray::getString(IR::Context, this->valuePrint.c_str(), true);
    globalString->setInitializer(arrayString);

    return globalString;
}

std::string String::toLLVMString() {
    return this->valuePrint;
}

llvm::Value* TocFunction::generateCode() {
    IR::TocFunction = llvm::BasicBlock::Create(IR::Context, "toc", IR::MainFunction);
    IR::Builder->SetInsertPoint(IR::TocFunction);

    this->body->generateCode();

    IR::Builder->SetInsertPoint(IR::TocFunction);
    IR::Builder->CreateRetVoid();

    return IR::TocFunction;
}

std::string TocFunction::toLLVMString() {
    return "";
}

llvm::Value* TypeCasting::generateCode() {
    llvm::Value* code = next->generateCode();
    llvm::Type* typeCast;
    llvm::Twine intCast = llvm::Twine("intCast");
    llvm::Twine fltCast = llvm::Twine("fltCast");
    llvm::Twine strCast = llvm::Twine("strCast");
    llvm::ConstantInt* intValue;
    llvm::ConstantFP* floatValue;

    switch(this->type) { // Tipo de destino
        case Data::BOO:
        case Data::INT:
            typeCast = llvm::Type::getInt32Ty(IR::Context);

            switch(next->dataType()) {
                case Data::FLT:
                    return IR::Builder->CreateFPToSI(code, typeCast, intCast);
                case Data::STR:
                    return code; // TODO
                default:
                    return code; // INT, BOO, VOID
            }
        case Data::FLT:
            typeCast = llvm::Type::getPrimitiveType(IR::Context, llvm::Type::FloatTyID);

            switch(next->dataType()) {
                case Data::BOO:
                case Data::INT:
                    return IR::Builder->CreateSIToFP(code, typeCast, fltCast);
                case Data::STR:
                    return code; // TODO
                default:
                    return code; // FLOAT, VOID
            }
        case Data::STR:
            typeCast = llvm::Type::getPrimitiveType(IR::Context, llvm::Type::ArrayTyID);

            switch(next->dataType()) {
                case Data::BOO:
                case Data::INT:
                    intValue = llvm::dyn_cast<llvm::ConstantInt>(code);
                    return IR::Builder->CreateGlobalString(
                        llvm::StringRef(std::to_string(intValue->getSExtValue())), strCast, 3 /* ADDRESS_SPACE_SHARED */);
                case Data::FLT:
                    floatValue = llvm::dyn_cast<llvm::ConstantFP>(code);
                    return IR::Builder->CreateGlobalString(
                        llvm::StringRef(std::to_string(floatValue->getValueAPF().convertToFloat())), strCast, 3 /* ADDRESS_SPACE_SHARED */);
                default:
                    return code; // STR, VOID
            }
        default:
            return code;
    }
}

std::string TypeCasting::toLLVMString() {
    switch(next->classType()) {
        case TreeNode::BOOLEAN:
        case TreeNode::FLOAT:
        case TreeNode::INTEGER:
        case TreeNode::STRING:
            return next->toLLVMString();
        default:
            return "";
    }
}

llvm::Value* Variable::generateCode() {
    return this->symbolTable.getVariableAllocation(id);
}

std::string Variable::toLLVMString() {
    TreeNode* data = this->symbolTable.getSymbol(this->id, true).getData();
    return data->toLLVMString();
}

llvm::Value* VariableDeclaration::generateCode() {
    return next->generateCode();
}

std::string VariableDeclaration::toLLVMString() {
    return "";
}
