#ifndef SEMANTICANALYZER_H_
#define SEMANTICANALYZER_H_

#include "SymbolTable.h"
#include <string>
#include <vector>

class SemanticAnalyzer;

extern SemanticAnalyzer SEMANTIC_ANALYZER;
extern void yyerror(const char* s, ...);

/**
 * Analisador semântico.
 */
class SemanticAnalyzer {

    public:
        SemanticAnalyzer();
        virtual ~SemanticAnalyzer();

        void newScope();
        void returnScope();


        TreeNode* declareVariable(std::string varId, Data::Type dataType, int size = 0);
        TreeNode* assignVariable(std::string varId, Data::Type assignedType, TreeNode* index = NULL);
        TreeNode* declareAssignVariable(std::string id, Data::Type dataType, Data::Type assignedType);
        TreeNode* useVariable(std::string varId, TreeNode* index = NULL);

        //TreeNode* declareFunction(std::string functionId, Vector* params, Vector* body, TreeNode* returnValue);
        //TreeNode* callFunction(std::string functionId, Vector* params);
        bool symbolExists(std::string id, Symbol::IdentifierType type, bool checkParentScope);

    private:
        Symbol getSymbol(std::string id, Symbol::IdentifierType type, bool checkParentScope);
        Data::Type getSymbolType(std::string id, Symbol::IdentifierType type) const;
        bool isSymbolInitialized(std::string id, Symbol::IdentifierType type, bool checkParentScope) const;
        void setInitializedSymbol(std::string id, Symbol::IdentifierType type);

        SymbolTable symbolTable;
        std::vector<SymbolTable> scopes;

};

#endif