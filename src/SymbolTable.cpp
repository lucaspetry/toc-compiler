#include "SymbolTable.h"

SymbolTable::SymbolTable() {
}

SymbolTable& SymbolTable::operator=(const SymbolTable& table) {
    this->entryList = table.entryList;
    return *this;
}

SymbolTable::~SymbolTable() {
}

void SymbolTable::clear() {
    entryList.clear();
}

bool SymbolTable::existsSymbol(std::string id, Symbol::IdentifierType type) const {
    return entryList.find(id) != entryList.end();
}

Symbol SymbolTable::getSymbol(std::string id, Symbol::IdentifierType type) const {
    return entryList.at(id);
}

std::vector<std::string> SymbolTable::getUninitializedFunctions() {
    std::map<std::string, Symbol>::iterator iter;
    std::vector<std::string> functions;

    for(iter = entryList.begin(); iter != entryList.end(); iter++) {
        if(!entryList[iter->first].initialized)
            functions.push_back(iter->first);
    }

    return functions;
}

void SymbolTable::addSymbol(std::string id, Symbol newSymbol) {
    entryList[id] = newSymbol;
}

void SymbolTable::setInitializedSymbol(std::string id, Symbol::IdentifierType type) {
    entryList[id].initialized = true;
}

void SymbolTable::setSymbolData(const std::string id, Symbol::IdentifierType type, TreeNode* data) {
    if(entryList[id].data) {
        delete entryList[id].data;
        entryList[id].data = 0;
    }

    entryList[id].data = data;
}
