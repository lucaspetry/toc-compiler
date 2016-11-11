#ifndef SEMANTICANALYZER_H_
#define SEMANTICANALYZER_H_

#include "ErrorLogger.h"
#include "SymbolTable.h"
#include "Variable.h"
#include "LLVM.h"
#include <string>
#include <vector>

extern ErrorLogger* ERROR_LOGGER;

/**
 * Analisador semântico.
 */
class SemanticAnalyzer {

    public:
        SemanticAnalyzer();
        virtual ~SemanticAnalyzer();

        void newScope();
        void returnScope();

        void setType(Data::Type tipo);

        TreeNode* declareVariable(std::string varId, Data::Type dataType, int size = 0);
        TreeNode* assignVariable(std::string varId, TreeNode* index = NULL);
        TreeNode* declareAssignVariable(std::string id, Data::Type dataType);
        TreeNode* useVariable(std::string varId, TreeNode* index = NULL);
        //TreeNode* declareFunction(std::string functionId, Vector* params, Vector* body, TreeNode* returnValue);
        //TreeNode* callFunction(std::string functionId, Vector* params);

    private:
        SymbolTable symbolTable;

};

#endif
