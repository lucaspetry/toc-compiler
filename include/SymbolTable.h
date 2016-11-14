#ifndef SYMBOLTABLE_H_
#define SYMBOLTABLE_H_

#include "LLVM.h"
#include <string>

class Symbol;
class Scope;
class TreeNode;

/**
  Class SymbolTable
**/

class SymbolTable {

    friend class SemanticAnalyzer;

    public:
      SymbolTable();
      virtual ~SymbolTable();

      SymbolTable& operator=(const SymbolTable& table);
      Symbol getSymbol(std::string id, bool checkParentScope = false) const;

      void newScope();
      void returnScope();
      void clear();

      bool existsSymbol(std::string id, bool checkParentScope = false) const;
      bool isSymbolInitialized(std::string id, bool checkParentScope = false) const;

      void addSymbol(const std::string id, Symbol newSymbol);
      void setInitializedSymbol(const std::string id);
      void setSymbolData(const std::string id, TreeNode* data);
      void updateVariableAllocation(std::string id, llvm::Value* value);

      llvm::Value* getVariableAllocation(std::string id);

    private:
      Scope* currentScope;

};

#endif
