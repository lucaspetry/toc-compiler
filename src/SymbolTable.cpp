#include "SymbolTable.h"

SymbolTable::SymbolTable() {
}

SymbolTable::~SymbolTable() {
}

void SymbolTable::newScope() {
    this->currentScope = new Scope(this->currentScope);
    this->currentScope->clear();
}

void SymbolTable::returnScope() {
    this->currentScope = this->currentScope->getParent();
}

void SymbolTable::clear() {
    currentScope->clear();
}

bool SymbolTable::existsSymbol(std::string id, bool checkParentScope) const {
    if(currentScope->existsSymbol(id))
        return true;

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
    if(this->currentScope->existsSymbol(id))
        return this->currentScope->getSymbol(id);

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

void SymbolTable::setInitializedSymbol(std::string id) {
    if(this->existsSymbol(id))
        this->currentScope->setInitializedSymbol(id);
    else {
        Scope* scopeIt = this->currentScope;
        while(scopeIt->getParent() != NULL) {
            scopeIt = scopeIt->getParent();
            if(scopeIt->existsSymbol(id)) {
                scopeIt->setInitializedSymbol(id);
                break;
            }
        }
    }
}

void SymbolTable::setSymbolData(const std::string id, TreeNode* data) {
    currentScope->setSymbolData(id, data);
}

llvm::Value* SymbolTable::getVariableAllocation(std::string id) {
    return NULL; //TODO
}

void SymbolTable::updateVariableAllocation(std::string id, llvm::Value* value) {
    // TODO
}
