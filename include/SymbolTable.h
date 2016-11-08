#ifndef SYMBOLTABLE_H_
#define SYMBOLTABLE_H_

#include "Symbol.h"
#include "TreeNode.h"
#include <map>
#include <string>
#include <vector>

/**
 * Tabela de símbolos gerada na análise sintática.
 */
class SymbolTable {
    
    friend class SemanticAnalyzer;
    
    public:
        SymbolTable();
        SymbolTable& operator=(const SymbolTable& table);
        virtual ~SymbolTable();
        void clear();
        bool existsSymbol(std::string id, Symbol::IdentifierType type) const;
        Symbol getSymbol(std::string id, Symbol::IdentifierType type) const;
        std::vector<std::string> getUninitializedFunctions();
    
        void addSymbol(const std::string id, Symbol newSymbol);
        void setInitializedSymbol(const std::string id, Symbol::IdentifierType type);
        void setSymbolData(const std::string id, Symbol::IdentifierType type, TreeNode* data);
    
    private:
        std::map<std::string, Symbol> entryList;
    
};

#endif