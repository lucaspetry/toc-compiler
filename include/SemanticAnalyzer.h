#ifndef SEMANTICANALYZER_H_
#define SEMANTICANALYZER_H_

#include "ErrorLogger.h"
#include "SymbolTable.h"
#include "Array.h"
#include "Integer.h"
#include "Variable.h"
#include "VariableDeclaration.h"
#include "LLVM.h"
#include <string>
#include <vector>

extern ErrorLogger* ERROR_LOGGER;

class SemanticAnalyzer {

    public:
        SemanticAnalyzer();
        virtual ~SemanticAnalyzer();
        void newScope();
        void returnScope();
        void setType(Data::Type tipo);

        TreeNode* declareVariable(std::string varId, Data::Type dataType, int size = 0);
        TreeNode* assignVariable(std::string varId, TreeNode* index = NULL);
        TreeNode* declareAssignVariable(std::string id, Data::Type dataType, int size = 0);
        TreeNode* useVariable(std::string varId, TreeNode* index = NULL);


    private:
        SymbolTable symbolTable;
};

#endif
