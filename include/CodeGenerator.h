#ifndef CODEGENERATOR_H_
#define CODEGENERATOR_H_

#include "llvm/IR/DerivedTypes.h"   //for types
#include "llvm/IR/IRBuilder.h"      //for Builder
#include "llvm/IR/LLVMContext.h"    //for Context
#include "llvm/IR/Module.h"         //for Module
#include "llvm/IR/Verifier.h"       //for Verify function
#include "llvm/ExecutionEngine/ExecutionEngine.h" //for JIT
#include "llvm/ExecutionEngine/GenericValue.h"    //for GenericValue
#include "llvm/ExecutionEngine/MCJIT.h"

#include <iostream>
#include <vector>

class CodeGenerator {

    public:
        CodeGenerator();
        virtual ~CodeGenerator();
        void generateExecutableCode();

};

#endif
