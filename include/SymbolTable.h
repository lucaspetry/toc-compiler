#ifndef SYMBOLTABLE_H_
#define SYMBOLTABLE_H_

#include "LLVM.h"
#include <string>

class Symbol;
class Scope;
class TreeNode;

class SymbolTable {

    friend class SemanticAnalyzer;

    public:
      SymbolTable();
      virtual ~SymbolTable();
      SymbolTable& operator=(const SymbolTable& table);

      void newScope();
      void returnScope();

      void clear();
      bool existsSymbol(std::string id, bool checkParentScope = false) const;
      Symbol getSymbol(std::string id, bool checkParentScope = false) const;
      bool isSymbolInitialized(std::string id, bool checkParentScope = false) const;

      void addSymbol(const std::string id, Symbol newSymbol);
      void setInitializedSymbol(const std::string id);
      void setSymbolData(const std::string id, TreeNode* data);

      llvm::Value* getVariableAllocation(std::string id);
      void updateVariableAllocation(std::string id, llvm::Value* value);

    private:
      Scope* currentScope;

};

#endif
