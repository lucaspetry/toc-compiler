#include "SymbolTable.h"
#include "CodeBlock.h"
#include "Scope.h"

SymbolTable::SymbolTable() {
}

SymbolTable::~SymbolTable() {
}

SymbolTable& SymbolTable::operator=(const SymbolTable& table) {
    this->currentScope = table.currentScope;
    return *this;
}

void SymbolTable::newScope() {
    this->currentScope = new Scope(this->currentScope);
    this->currentScope->clear();
}

void SymbolTable::returnScope() {
    Scope* parent = this->currentScope->getParent();

    if(parent != NULL && parent->structure != NULL)
        parent->structure->setBody(this->currentScope->code);

    this->currentScope = parent;
}

void SymbolTable::pushLineScope(TreeNode* line) {
    if(this->currentScope->code == NULL) {
        this->currentScope->code = new CodeBlock(this->currentScope->indentation);
        this->currentScope->code->setSymbolTable(*this);
    }

    this->currentScope->code->insertLineBack(line);
}

CodeBlock* SymbolTable::getCurrentCodeBlock() {
    return this->currentScope->code;
}

TreeNode* SymbolTable::getParentStructure() {
    if(this->currentScope->parent != NULL)
        return this->currentScope->parent->structure;

    return NULL;
}

void SymbolTable::setCurrentStructure(TreeNode* node) {
    if(this->currentScope != NULL)
        this->currentScope->structure = node;
}

TreeNode* SymbolTable::getLastStatement() {
    return this->currentScope->lastStatement;
}

void SymbolTable::setLastStatement(TreeNode* node) {
    if(this->currentScope != NULL)
        this->currentScope->lastStatement = node;
}

int SymbolTable::getCurrentIndentation() {
    return this->currentScope->indentation;
}

void SymbolTable::clear() {
    currentScope->clear();
}

bool SymbolTable::existsSymbol(std::string id, bool checkParentScope) const {
    if(currentScope->existsSymbol(id)){
        return true;
    }
    if(checkParentScope) {
        Scope* scopeIt = this->currentScope;
        while(scopeIt->getParent() != NULL) {
            scopeIt = scopeIt->getParent();

            if(scopeIt->existsSymbol(id))
                return true;
        }
    }

    return false;
}

Symbol SymbolTable::getSymbol(std::string id, bool checkParentScope) const {
    if(this->currentScope->existsSymbol(id)){
        return this->currentScope->getSymbol(id);
}
    if(checkParentScope) {
        Scope* scopeIt = this->currentScope;
        while(scopeIt->getParent() != NULL) {
            scopeIt = scopeIt->getParent();
            if(scopeIt->existsSymbol(id))
                return scopeIt->getSymbol(id);
        }
    }

    // Dark zone: you shouldn't reach this zone!
    return Symbol(Data::UNKNOWN, Symbol::VARIABLE, false);
}

bool SymbolTable::isSymbolInitialized(std::string id, bool checkParentScope) const {
    if(this->existsSymbol(id))
        return this->getSymbol(id).isInitialized();

    if(checkParentScope) {
        Scope* scopeIt = this->currentScope;
        while(scopeIt->getParent() != NULL) {
            scopeIt = scopeIt->getParent();

            if(scopeIt->existsSymbol(id))
                return scopeIt->getSymbol(id).isInitialized();
        }
    }

    // Dark zone: you shouldn't reach this zone!
    return false;
}

void SymbolTable::addSymbol(std::string id, Symbol newSymbol) {
    currentScope->addSymbol(id, newSymbol);
}

void SymbolTable::setInitializedSymbol(std::string id, TreeNode* data) {
    if(this->existsSymbol(id))
        this->currentScope->setInitializedSymbol(id, data);
    else {
        Scope* scopeIt = this->currentScope;
        while(scopeIt->getParent() != NULL) {
            scopeIt = scopeIt->getParent();

            if(scopeIt->existsSymbol(id)) {
                scopeIt->setInitializedSymbol(id, data);
                break;
            }
        }
    }
}

void SymbolTable::setEncapsulation(std::string id, int encapsulation){
  if(this->existsSymbol(id))
      this->currentScope->setEncapsulation(id, encapsulation);
  else {
      Scope* scopeIt = this->currentScope;
      while(scopeIt->getParent() != NULL) {
          scopeIt = scopeIt->getParent();

          if(scopeIt->existsSymbol(id)) {
              scopeIt->setEncapsulation(id, encapsulation);
              break;
          }
      }
  }
}
void SymbolTable::setSymbolData(const std::string id, TreeNode* data) {
    currentScope->setSymbolData(id, data);
}

void SymbolTable::setUnknownTypes(Data::Type type) {
    currentScope->setUnknownTypes(type);
}

MemoryMap SymbolTable::getAllocations() const {
    MemoryMap map;
    Scope* scope = this->currentScope;

    while(scope != NULL) {
        MemoryMap scopeMap = scope->getMemoryMap();
        MemoryMap::iterator itMap;

        for(itMap = scopeMap.begin(); itMap != scopeMap.end(); ++itMap) {
            std::string varId = itMap->first;
            llvm::Value* value = itMap->second;

            // Se valor ainda não existe, adiciona
            if (map.find(varId) == map.end()) {
                map[varId] = value;
            }
        }

        scope = scope->getParent();
    }

    return map;
}

llvm::Value* SymbolTable::getVariableAllocation(std::string id) {
    if(this->existsSymbol(id))
        return this->currentScope->getVariableAllocation(id);
    else {
        Scope* scopeIt = this->currentScope;
        while(scopeIt->getParent() != NULL) {
            scopeIt = scopeIt->getParent();

            if(scopeIt->existsSymbol(id))
                return scopeIt->getVariableAllocation(id);
        }
    }

    // Dark zone: you shouldn't reach this zone!
    return NULL;
}

void SymbolTable::updateVariableAllocation(std::string id, llvm::Value* value) {
    if(this->existsSymbol(id))
        this->currentScope->updateVariableAllocation(id, value);
    else {
        Scope* scopeIt = this->currentScope;
        while(scopeIt->getParent() != NULL) {
            scopeIt = scopeIt->getParent();

            if(scopeIt->existsSymbol(id)) {
                this->currentScope->updateVariableAllocation(id, value);
                break;
            }
        }
    }
}
