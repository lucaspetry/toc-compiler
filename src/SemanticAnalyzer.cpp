#include "SemanticAnalyzer.h"

SemanticAnalyzer::SemanticAnalyzer() {
}

SemanticAnalyzer::~SemanticAnalyzer() {
}

void SemanticAnalyzer::newScope() {
    scopes.push_back(this->symbolTable);
    this->symbolTable.clear();
}

void SemanticAnalyzer::returnScope() {
    this->symbolTable = scopes.back();
    scopes.pop_back();
}

TreeNode* SemanticAnalyzer::declareVariable(std::string id, Data::Type dataType, int size) {
    if(size > 0)
      return new Array(id, dataType, size); // id, type, size
    return NULL;
}

TreeNode* SemanticAnalyzer::assignVariable(std::string id, Data::Type assignedType, TreeNode* index) {
  return NULL;

}

TreeNode* SemanticAnalyzer::declareAssignVariable(std::string id, Data::Type dataType, Data::Type assignedType) {
  return NULL;

}

TreeNode* SemanticAnalyzer::useVariable(std::string id, TreeNode* index) {
  return NULL;

}

Symbol SemanticAnalyzer::getSymbol(std::string id, Symbol::IdentifierType type, bool checkParentScope) {
    if(symbolTable.existsSymbol(id, type))
        return symbolTable.getSymbol(id, type);

    for(int i = scopes.size() - 1; i >= 0; i--) {
        SymbolTable t = scopes[i];
        if(t.existsSymbol(id, type))
            return t.getSymbol(id, type);
    }

    // Dark zone: you shouldn't reach this zone!
    return Symbol(Data::UNKNOWN, Symbol::VARIABLE, false);
}

Data::Type SemanticAnalyzer::getSymbolType(std::string id, Symbol::IdentifierType type) const {
    if(symbolTable.existsSymbol(id, type))
        return symbolTable.getSymbolType(id, type);

    for(int i = scopes.size() - 1; i >= 0; i--) {
        SymbolTable t = scopes[i];
        if(t.existsSymbol(id, type))
            return t.getSymbolType(id, type);
    }

    // Dark zone: you shouldn't reach this zone!
    return Data::UNKNOWN;
}

bool SemanticAnalyzer::symbolExists(std::string id, Symbol::IdentifierType type, bool checkParentScope) {
    if(symbolTable.existsSymbol(id, type))
        return true;

    if(checkParentScope) {
        for(SymbolTable t : scopes)
            if(t.existsSymbol(id, type))
                return true;
        return false;
    }

    return false;
}

bool SemanticAnalyzer::isSymbolInitialized(std::string id, Symbol::IdentifierType type, bool checkParentScope) const {
    if(symbolTable.existsSymbol(id, type))
        return symbolTable.isSymbolInitialized(id, type);

    if(checkParentScope) {
        for(int i = scopes.size() - 1; i >= 0; i--) {
            SymbolTable t = scopes[i];
            if(t.existsSymbol(id, type))
                return t.isSymbolInitialized(id, type);
        }
    }

    // Dark zone: you shouldn't reach this zone!
    return false;
}

void SemanticAnalyzer::setInitializedSymbol(std::string id, Symbol::IdentifierType type) {
    if(symbolTable.existsSymbol(id, type))
        symbolTable.setInitializedSymbol(id, type);
    else
        for(int i = scopes.size() - 1; i >= 0; i--) {
            SymbolTable t = scopes[i];
            if(scopes[i].existsSymbol(id, type)) {
                scopes[i].setInitializedSymbol(id, type);
                break;
            }
        }
}
