#ifndef SEMANTICANALYZER_H_
#define SEMANTICANALYZER_H_

#include "ErrorLogger.h"
#include "SymbolTable.h"
#include "Variable.h"
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
        bool symbolExists(std::string id, bool checkParentScope);

    private:
        /**
         * Métodos para gerência de múltiplos escopos.
         */
        Symbol getSymbol(std::string id, bool checkParentScope);
        Data::Type getSymbolType(std::string id) const;
        bool isSymbolInitialized(std::string id, bool checkParentScope) const;
        void setInitializedSymbol(std::string id);

        SymbolTable symbolTable;
        std::vector<SymbolTable> scopes;

};

#endif
