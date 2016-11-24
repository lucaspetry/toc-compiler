#include "Scope.h"

Scope::Scope(Scope* parent) {
  this->parent = parent;
}

Scope& Scope::operator=(const Scope& scope) {
    this->entryList = scope.entryList;
    this->allocations = scope.allocations;
    this->parent = scope.parent;
    return *this;
}

Scope::~Scope() {
}

Scope* Scope::getParent() {
    return this->parent;
}

void Scope::setParent(Scope* parent) {
    this->parent = parent;
}

void Scope::clear() {
    entryList.clear();
    allocations.clear();
}

bool Scope::existsSymbol(std::string id) const {
    return entryList.find(id) != entryList.end();
}

Symbol Scope::getSymbol(std::string id) const {
    return entryList.at(id);
}

bool Scope::isSymbolInitialized(std::string id) const {
    return entryList.at(id).initialized;
}

void Scope::addSymbol(std::string id, Symbol newSymbol) {
    entryList[id] = newSymbol;

    if(newSymbol.getType() == Symbol::VARIABLE)
        allocations[id] = IR::Zero;
}

void Scope::setInitializedSymbol(std::string id) {
    entryList[id].initialized = true;
}

void Scope::setSymbolData(const std::string id, TreeNode* data) {
    if(entryList[id].data) {
        delete entryList[id].data; // Dangerous!
        entryList[id].data = 0;
    }

    entryList[id].data = data;
}

void Scope::setUnknownTypes(Data::Type type) {
    std::map<std::string, Symbol> newEntryList;
    std::map<std::string, Symbol>::iterator it;
        
    for(it = entryList.begin(); it != entryList.end(); ++it) {
        Symbol s = it->second;
        
        if (s.getDataType() == Data::UNKNOWN) {
            s.dataType = type;
        }
        
        newEntryList[it->first] = s;
    }
    
    this->entryList = newEntryList;
}

llvm::Value* Scope::getVariableAllocation(std::string id) {
    return allocations[id];
}

void Scope::updateVariableAllocation(std::string id, llvm::Value* value) {
    allocations[id] = value;
}
