#ifndef LLVM_H_
#define LLVM_H_

/**
 * Arquivos de geração de código intermediário (LLVM)
 */
#include "llvm/IR/DerivedTypes.h"                   // for types
#include "llvm/IR/IRBuilder.h"                      // for Builder
#include "llvm/IR/LLVMContext.h"                    // for Context
#include "llvm/IR/Module.h"                         // for Module
#include "llvm/IR/Verifier.h"                       // for Verify function
#include "llvm/ExecutionEngine/ExecutionEngine.h"   // for JIT
#include "llvm/ExecutionEngine/GenericValue.h"      // for GenericValue
#include "llvm/ExecutionEngine/Interpreter.h"
#include "llvm/ExecutionEngine/MCJIT.h"

/**
 * Variáveis de geração de código intermediário (LLVM)
 */
namespace IR {
    static llvm::Function* MainFunction = 0; // Criada no CodeGenerator.
    static llvm::Function* CurrentFunction; // Criado no CodeGenerator.
    static llvm::BasicBlock* TocFunction; // Criado no CodeGenerator.
    static llvm::LLVMContext& Context = llvm::getGlobalContext();
    static llvm::Module *Module = 0; // Criado no CodeGenerator.
    static llvm::IRBuilder<>* Builder = new llvm::IRBuilder<>(Context);
    static llvm::Constant* Zero = llvm::ConstantInt::get(Context, llvm::APInt(32, 0));
    static llvm::Constant* ZeroFP = llvm::ConstantFP::get(Context, llvm::APFloat(0.0));
    static llvm::Constant* False = llvm::ConstantInt::get(IR::Context, llvm::APInt(32, 0));
}

#endif
