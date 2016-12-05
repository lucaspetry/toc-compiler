#include "CodeGenerator.h"
#include <iostream>

#include "SyntaxTree.h"
#include "Array.h"
#include "BinaryOperation.h"
#include "Boolean.h"
#include "Comment.h"
#include "Data.h"
#include "Float.h"
#include "Function.h"
#include "FunctionCall.h"
#include "Integer.h"
#include "PrintFunction.h"
#include "String.h"
#include "Symbol.h"
#include "TocFunction.h"
#include "TypeCasting.h"
#include "Variable.h"
#include "VariableDeclaration.h"
#include "UnaryOperation.h"
#include "Loop.h"
#include "Conditional.h"
#include "Object.h"

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
    IR::CurrentFunction = IR::MainFunction;

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

llvm::Type* Data::toLLVMType(Data::Type type) {
    switch(type) {
        case Data::BOO:
        case Data::INT:
            return llvm::Type::getInt32Ty(IR::Context);
        case Data::FLT:
            return llvm::Type::getPrimitiveType(IR::Context, llvm::Type::FloatTyID);
        case Data::STR:
            return llvm::Type::getVoidTy(IR::Context);
    }
}

void SyntaxTree::generateCode() {
    for (TreeNode* line: lines) {
        line->generateCode();
    }
}

llvm::Value* BinaryOperation::generateCode() {
    if (this->operation == BinaryOperation::ASSIGN) {
        Variable* lvar = dynamic_cast<Variable*>(left);

        if(left->classType() == TreeNode::VARIABLE_DECLARATION)
            lvar = dynamic_cast<Variable*>((dynamic_cast<VariableDeclaration*>(left))->getNext());

        // TODO array?
        llvm::Value* newValue;

        switch(this->dataType()) {
            case Data::BOO:
            case Data::INT:
                newValue = IR::Builder->CreateAdd(right->generateCode(), IR::Zero, lvar->getId().c_str());
                break;
            case Data::FLT:
                newValue = IR::Builder->CreateFAdd(right->generateCode(), IR::ZeroFP, lvar->getId().c_str());
                break;
            case Data::STR:
                newValue = right->generateCode();
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
                    case Data::BOO:
                    case Data::INT:
                        return IR::Builder->CreateAdd(left->generateCode(), right->generateCode(), "addtmp");
                    case Data::FLT:
                        return IR::Builder->CreateFAdd(left->generateCode(), right->generateCode(), "addtmp");
                    case Data::STR:
                        if(left->classType() == TreeNode::STRING && right->classType() == TreeNode::STRING) {
                            String* str1 = (String*) left;
                            String* str2 = (String*) right;
                            std::string newString = str1->getValue() + str2->getValue();

                            llvm::GlobalVariable* globalString = new llvm::GlobalVariable(
                                /*Module=*/     *IR::Module,
                                /*Type=*/       llvm::ArrayType::get(llvm::IntegerType::get(IR::Context, 32), newString.size()),
                                /*isConstant=*/ false,
                                /*Linkage=*/    llvm::GlobalValue::PrivateLinkage,
                                /*Initializer=*/0,
                                /*Name=*/       "str");
                            globalString->setAlignment(1);

                            llvm::Constant *arrayString = llvm::ConstantDataArray::getString(IR::Context, newString.c_str(), true);
                            globalString->setInitializer(arrayString);

                            return globalString;
                        }
                        break;
                        return IR::Builder->CreateFAdd(left->generateCode(), right->generateCode(), "addtmp");
                    default:
                        return IR::Builder->CreateFAdd(left->generateCode(), right->generateCode(), "addtmp");
                }
            case BinaryOperation::TIMES:
                return IR::Builder->CreateMul(left->generateCode(), right->generateCode(), "multmp");
            case BinaryOperation::GREATER:
                return IR::Builder->CreateICmpSGT(left->generateCode(), right->generateCode(), "greater");
            case BinaryOperation::GREATER_E:
                return IR::Builder->CreateICmpSGE(left->generateCode(), right->generateCode(), "greaterequal");
            case BinaryOperation::LOWER:
                return IR::Builder->CreateICmpSLT(left->generateCode(), right->generateCode(), "lower");
            case BinaryOperation::LOWER_E:
                return IR::Builder->CreateICmpSLE(left->generateCode(), right->generateCode(), "lowerequal");
            case BinaryOperation::EQUAL:
                return IR::Builder->CreateICmpEQ(left->generateCode(), right->generateCode(), "equal");
            case BinaryOperation::DIFF:
                return IR::Builder->CreateICmpNE(left->generateCode(), right->generateCode(), "notequal");
            case BinaryOperation::AND:
                return IR::Builder->CreateAnd(left->generateCode(), right->generateCode(), "and");
            case BinaryOperation::OR:
                return IR::Builder->CreateOr(left->generateCode(), right->generateCode(), "or");
            default:
                return NULL;
        }
    }
}

llvm::Value* UnaryOperation::generateCode() {
    return NULL; //TODO
}

llvm::Value* Boolean::generateCode() {
    int equivalent = value ? 1 : 0;
    return llvm::ConstantInt::get(IR::Context, llvm::APInt(32, equivalent));
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
    return llvm::ConstantFP::get(IR::Context, llvm::APFloat(this->value));
}

llvm::Value* Function::generateCode() {
    std::vector<llvm::Type*> params;

    if(this->params != NULL)
        for(int i = 0; i < this->params->numberOfLines(); i++) {
            params.push_back(Data::toLLVMType(this->params->getLine(i)->dataType()));
        }

    llvm::FunctionType* funType = llvm::FunctionType::get(Data::toLLVMType(this->dataType()), params, false);
    IR::Module->getOrInsertFunction(this->id, funType);
    IR::CurrentFunction = IR::Module->getFunction(this->id);


    llvm::Function::arg_iterator paramsIt = IR::CurrentFunction->arg_begin();
    int i = 0;

    for(; paramsIt != IR::CurrentFunction->arg_end(); ++paramsIt) {
        Variable* var = (Variable*) ((VariableDeclaration*)this->params->getLine(i))->getNext();
        paramsIt->setName(var->getId());
        this->params->symbolTable.updateVariableAllocation(var->getId(), &*paramsIt);
        i++;
    }

    llvm::BasicBlock* startFunction = llvm::BasicBlock::Create(IR::Context, "start", IR::CurrentFunction);
    IR::Builder->SetInsertPoint(startFunction);

    body->generateCode();

    if(this->ret != NULL) {
        IR::Builder->CreateRet(this->ret->generateCode());
    } else {
        IR::Builder->CreateRetVoid();
    }

    llvm::verifyFunction(*IR::CurrentFunction);

    return IR::CurrentFunction;
}

llvm::Value* FunctionCall::generateCode() {
    std::vector<llvm::Value*> args;

    if(this->params != NULL)
        for(int i = 0; i < this->params->numberOfLines(); i++)
            args.push_back(this->params->getLine(i)->generateCode());

    return IR::Builder->CreateCall(IR::Module->getOrInsertFunction(this->id,
                Data::toLLVMType(this->dataType())), args, this->id + "Call");
}

llvm::Value* Integer::generateCode() {
    return llvm::ConstantInt::get(IR::Context, llvm::APInt(32, value));
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

llvm::Value* TocFunction::generateCode() {
    IR::TocFunction = llvm::BasicBlock::Create(IR::Context, "toc", IR::MainFunction);
    IR::Builder->SetInsertPoint(IR::TocFunction);

    this->body->generateCode();

    //IR::Builder->SetInsertPoint(IR::TocFunction);
    IR::Builder->CreateRetVoid();

    return IR::TocFunction;
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
                    intValue = llvm::dyn_cast<llvm::ConstantInt>(code);
                    if(intValue->isZero()) {
                        return IR::Builder->CreateGlobalString(llvm::StringRef("false"), strCast, 3 /* ADDRESS_SPACE_SHARED */);
                    } else {
                        return IR::Builder->CreateGlobalString(llvm::StringRef("true"), strCast, 3 /* ADDRESS_SPACE_SHARED */);
                    }
                case Data::INT:
                    intValue = llvm::dyn_cast<llvm::ConstantInt>(code);

                    if(intValue == NULL)
                        return code;
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

llvm::Value* Variable::generateCode() {
    if(IR::PHILoop != NULL)
        return IR::PHILoop;
    return this->symbolTable.getVariableAllocation(id);
}

llvm::Value* Conditional::generateCode() {
    llvm::Value* condition = this->condition->generateCode();
    llvm::Value* conditionTrue = IR::Builder->CreateICmpNE(condition, IR::False, "comp");
    llvm::BasicBlock *thenBlock = llvm::BasicBlock::Create(IR::Context, llvm::Twine("then"), IR::CurrentFunction);
    llvm::BasicBlock *mergeBlock = llvm::BasicBlock::Create(IR::Context, llvm::Twine("merge"), IR::CurrentFunction);
    llvm::BasicBlock *elseBlock = mergeBlock;

    llvm::BasicBlock *currentBlock = IR::Builder->GetInsertBlock();

    // Gera o else, se existe else
    if(this->elseCode != NULL) {
        elseBlock = llvm::BasicBlock::Create(IR::Context, llvm::Twine("else"), IR::CurrentFunction);
        IR::Builder->SetInsertPoint(elseBlock);
        this->elseCode->generateCode();
        IR::Builder->CreateBr(mergeBlock);
    }

    // Cria a condição de branch
    IR::Builder->SetInsertPoint(currentBlock);
    IR::Builder->CreateCondBr(conditionTrue, thenBlock, elseBlock);

    // Gera o then
    IR::Builder->SetInsertPoint(thenBlock);
    this->thenCode->generateCode();
    IR::Builder->CreateBr(mergeBlock);

    IR::Builder->SetInsertPoint(mergeBlock);

    // PHI
    if(this->elseCode != NULL) {
        MemoryMap mapThen = this->thenCode->symbolTable.getAllocations();
        MemoryMap mapElse = this->elseCode->symbolTable.getAllocations();

        MemoryMap::iterator itMap;

        for(itMap = mapThen.begin(); itMap != mapThen.end(); ++itMap) {
            std::string varId = itMap->first;
            llvm::Value* value = itMap->second;

            // Se valor existe no then e else, cria PHI
            if (mapElse.find(varId) != mapElse.end()) {
                llvm::PHINode *phi = IR::Builder->CreatePHI(value->getType(), 2, varId + "Phi");
                phi->addIncoming(value, thenBlock);
                phi->addIncoming(mapElse[varId], elseBlock);
                this->thenCode->symbolTable.updateVariableAllocation(varId, phi);
            }
        }
    }

    return condition;
}

llvm::Value* VariableDeclaration::generateCode() {
    return next->generateCode();
}

llvm::Value* Object::generateCode() {
    return NULL;//TODO
}

llvm::Value* Array::generateCode() {
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
  return NULL;
}

llvm::Value* Loop::generateCode() {
    llvm::Value* start = this->init->generateCode();
    llvm::BasicBlock *PreheaderBB = IR::Builder->GetInsertBlock();
    llvm::BasicBlock *LoopBB =llvm::BasicBlock::Create(IR::Context, llvm::Twine("loop"), IR::CurrentFunction);
    llvm::BasicBlock *condLoop =llvm::BasicBlock::Create(IR::Context, llvm::Twine("condLoop"), IR::CurrentFunction);
    IR::Builder->CreateBr(condLoop);

    // Código do laço
    IR::Builder->SetInsertPoint(LoopBB);
    this->body->generateCode();
    IR::Builder->CreateBr(condLoop);
    llvm::BasicBlock *LoopEndBB = IR::Builder->GetInsertBlock();

    // Condição do laço
    IR::Builder->SetInsertPoint(condLoop);

    llvm::PHINode *phi = IR::Builder->CreatePHI(start->getType(), 2, "Phi");
    phi->addIncoming(start, PreheaderBB);

    IR::PHILoop = phi;
    llvm::Value* att = this->attribuition->generateCode();

    llvm::Value* condition = this->test->generateCode();
    llvm::Value* conditionTrue = IR::Builder->CreateICmpNE(condition, IR::False, "comp");
    IR::PHILoop = NULL;

    llvm::BasicBlock *AfterBB = llvm::BasicBlock::Create(IR::Context, "afterloop", IR::CurrentFunction);

    IR::Builder->CreateCondBr(conditionTrue, LoopBB, AfterBB);

    IR::Builder->SetInsertPoint(AfterBB);
    phi->addIncoming(att, LoopEndBB);

    return condition;
}
