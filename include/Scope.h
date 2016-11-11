#ifndef SCOPE_H_
#define SCOPE_H_

#include "LLVM.h"
#include "Symbol.h"
#include "TreeNode.h"
#include <map>
#include <string>
#include <vector>

typedef std::map<std::string, llvm::Value*> MemoryMap;

/**
 * Tabela de símbolos gerada na análise sintática.
 */
class Scope {

    friend class SymbolTable;

    public:
        Scope(Scope* parent = 0);
        Scope& operator=(const Scope& scope);
        virtual ~Scope();

        Scope* getParent();
        void setParent(Scope* parent);
        void clear();
        bool existsSymbol(std::string id) const;
        Symbol getSymbol(std::string id) const;
        bool isSymbolInitialized(std::string id) const;

        void addSymbol(const std::string id, Symbol newSymbol);
        void setInitializedSymbol(const std::string id);
        void setSymbolData(const std::string id, TreeNode* data);

        llvm::Value* getVariableAllocation(std::string id);
        void updateVariableAllocation(std::string id, llvm::Value* value);


    private:
        Scope* parent;
        std::map<std::string, Symbol> entryList;
        MemoryMap allocations;

};

#endif
