#ifndef LLVM_H_
#define LLVM_H_

/**
 * Arquivos de geração de código intermediário (LLVM).
 */
#include "llvm/IR/DerivedTypes.h"                   // for types
#include "llvm/IR/IRBuilder.h"                      // for Builder
#include "llvm/IR/LLVMContext.h"                    // for Context
#include "llvm/IR/Module.h"                         // for Module
#include "llvm/IR/Verifier.h"                       // for Verify function
#include "llvm/ExecutionEngine/ExecutionEngine.h"   // for JIT
#include "llvm/ExecutionEngine/GenericValue.h"      // for GenericValue
#include "llvm/ExecutionEngine/MCJIT.h"

#endif