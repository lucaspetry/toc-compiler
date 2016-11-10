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
    if(symbolExists(id, false))
        ERROR_LOGGER->log(ErrorLogger::SEMANTIC, "Re-declaration of variable " + id);
    else {
        symbolTable.addSymbol(id, Symbol(dataType, Symbol::VARIABLE, false)); // Adds variable to symbol table
    }

    if (size > 0) {
        return NULL; //TODO
        //return new Array(id, dataType, size);
    } else
        // return NULL; //TODO
        return new Variable(id, dataType); //Creates variable node anyway
}

TreeNode* SemanticAnalyzer::assignVariable(std::string id, TreeNode* index) {
    if(!symbolExists(id, true)) {
        ERROR_LOGGER->log(ErrorLogger::SEMANTIC, "Undeclared variable " + id);
        // return NULL; //TODO
        return new Variable(id, Data::UNKNOWN); //Creates variable node anyway
    } else if (index != NULL){
        setInitializedSymbol(id);
        return NULL; //TODO
        //return new Array(id, getSymbolType(id, Symbol::VARIABLE), index);
    }  else {
        setInitializedSymbol(id);
        // return NULL; //TODO
        return new Variable(id, getSymbolType(id));
    }
}

TreeNode* SemanticAnalyzer::declareAssignVariable(std::string id, Data::Type dataType) {
    if(symbolExists(id, false))
        ERROR_LOGGER->log(ErrorLogger::SEMANTIC, "Re-declaration of variable " + id);
    else
        symbolTable.addSymbol(id, Symbol(dataType, Symbol::VARIABLE, false)); // Adds variable to symbol table

    setInitializedSymbol(id);
    // return NULL; //TODO
    return new Variable(id, dataType);
}

TreeNode* SemanticAnalyzer::useVariable(std::string id, TreeNode* index) {
    if(!symbolExists(id, true)) {
        ERROR_LOGGER->log(ErrorLogger::SEMANTIC, "Undeclared variable " + id);
        // return NULL; //TODO
        return new Variable(id, Data::UNKNOWN); //Creates variable node anyway
    } else if (index != NULL){
        return NULL; //TODO
        //return new Array(id, getSymbolType(id, Symbol::VARIABLE), index);
    } else if(!isSymbolInitialized(id, true)) {
        ERROR_LOGGER->log(ErrorLogger::SEMANTIC, "Uninitialized variable " + id);
    }
    // return NULL; //TODO
    return new Variable(id, getSymbolType(id));
}

void SemanticAnalyzer::setType(Data::Type tipo){
  for(std::map<std::string, Symbol>::iterator it = symbolTable.entryList.begin(); it != symbolTable.entryList.end(); ++it) {
      if (it->second.getDataType() == Data::UNKNOWN)
        symbolTable.addSymbol(it->first, Symbol(tipo, Symbol::VARIABLE, false));
}
}
// TreeNode* SemanticAnalyzer::declareFunction(std::string functionId, Vector* params, Vector* body, TreeNode* returnValue) {
//   return NULL;
//
// }

// TreeNode* SemanticAnalyzer::callFunction(std::string functionId, Vector* params) {
//   return NULL;
//
// }

Symbol SemanticAnalyzer::getSymbol(std::string id, bool checkParentScope) {
    if(symbolTable.existsSymbol(id))
        return symbolTable.getSymbol(id);

    for(int i = scopes.size() - 1; i >= 0; i--) {
        SymbolTable t = scopes[i];
        if(t.existsSymbol(id))
            return t.getSymbol(id);
    }

    // Dark zone: you shouldn't reach this zone!
    return Symbol(Data::UNKNOWN, Symbol::VARIABLE, false);
}

Data::Type SemanticAnalyzer::getSymbolType(std::string id) const {
    if(symbolTable.existsSymbol(id))
        return symbolTable.getSymbol(id).getDataType();

    for(int i = scopes.size() - 1; i >= 0; i--) {
        SymbolTable t = scopes[i];
        if(t.existsSymbol(id))
            return t.getSymbol(id).getDataType();
    }

    // Dark zone: you shouldn't reach this zone!
    return Data::UNKNOWN;
}

bool SemanticAnalyzer::symbolExists(std::string id, bool checkParentScope) {
    if(symbolTable.existsSymbol(id))
        return true;

    if(checkParentScope) {
        for(SymbolTable t : scopes)
            if(t.existsSymbol(id))
                return true;
        return false;
    }

    return false;
}

bool SemanticAnalyzer::isSymbolInitialized(std::string id, bool checkParentScope) const {
    if(symbolTable.existsSymbol(id))
        return symbolTable.getSymbol(id).isInitialized();

    if(checkParentScope) {
        for(int i = scopes.size() - 1; i >= 0; i--) {
            SymbolTable t = scopes[i];
            if(t.existsSymbol(id))
                return t.getSymbol(id).isInitialized();
        }
    }

    // Dark zone: you shouldn't reach this zone!
    return false;
}

void SemanticAnalyzer::setInitializedSymbol(std::string id) {
    if(symbolTable.existsSymbol(id))
        symbolTable.setInitializedSymbol(id);
    else
        for(int i = scopes.size() - 1; i >= 0; i--) {
            SymbolTable t = scopes[i];
            if(scopes[i].existsSymbol(id)) {
                scopes[i].setInitializedSymbol(id);
                break;
            }
        }
}
