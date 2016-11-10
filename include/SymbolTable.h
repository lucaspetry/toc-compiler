#ifndef SYMBOLTABLE_H_
#define SYMBOLTABLE_H_

#include "LLVM.h"
#include "Symbol.h"
#include "TreeNode.h"
#include "ErrorLogger.h"
#include <map>
#include <string>
#include <vector>

typedef std::map<std::string, llvm::Value*> MemoryMap;

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
        bool existsSymbol(std::string id) const;
        Symbol getSymbol(std::string id) const;
        std::vector<std::string> getUninitializedFunctions();

        void addSymbol(const std::string id, Symbol newSymbol);
        void setInitializedSymbol(const std::string id);
        void setSymbolData(const std::string id, TreeNode* data);
        llvm::Value* useVariable(std::string id);
        void allocateVariable(std::string id,llvm::Value* = NULL);
        void updateVariable(std::string id, llvm::Value * value);


    private:
        std::map<std::string, Symbol> entryList;
        MemoryMap allocations;

};

#endif
