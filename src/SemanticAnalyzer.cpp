#include "SemanticAnalyzer.h"

SemanticAnalyzer::SemanticAnalyzer() {
}

SemanticAnalyzer::~SemanticAnalyzer() {
}

void SemanticAnalyzer::newScope() {
    this->symbolTable.newScope();
}

void SemanticAnalyzer::returnScope() {
    this->symbolTable.returnScope();
}

TreeNode* SemanticAnalyzer::declareVariable(std::string id, Data::Type dataType, int size) {
    if(symbolTable.existsSymbol(id, false))
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
    if(!symbolTable.existsSymbol(id, true)) {
        ERROR_LOGGER->log(ErrorLogger::SEMANTIC, "Undeclared variable " + id);
        // return NULL; //TODO
        return new Variable(id, Data::UNKNOWN); //Creates variable node anyway
    } else if (index != NULL){
        symbolTable.setInitializedSymbol(id);
        return NULL; //TODO
        //return new Array(id, getSymbolType(id, Symbol::VARIABLE), index);
    }  else {
        symbolTable.setInitializedSymbol(id);
        // return NULL; //TODO
        return new Variable(id, symbolTable.getSymbol(id).getDataType());
    }
}

TreeNode* SemanticAnalyzer::declareAssignVariable(std::string id, Data::Type dataType) {
    if(symbolTable.existsSymbol(id, false))
        ERROR_LOGGER->log(ErrorLogger::SEMANTIC, "Re-declaration of variable " + id);
    else
        symbolTable.addSymbol(id, Symbol(dataType, Symbol::VARIABLE, false)); // Adds variable to symbol table

    symbolTable.setInitializedSymbol(id);
    // return NULL; //TODO
    return new Variable(id, dataType);
}

TreeNode* SemanticAnalyzer::useVariable(std::string id, TreeNode* index) {
    if(!symbolTable.existsSymbol(id, true)) {
        ERROR_LOGGER->log(ErrorLogger::SEMANTIC, "Undeclared variable " + id);
        // return NULL; //TODO
        return new Variable(id, Data::UNKNOWN); //Creates variable node anyway
    } else if (index != NULL){
        return NULL; //TODO
        //return new Array(id, getSymbolType(id, Symbol::VARIABLE), index);
    } else if(!symbolTable.isSymbolInitialized(id, true)) {
        ERROR_LOGGER->log(ErrorLogger::SEMANTIC, "Uninitialized variable " + id);
    }
    // return NULL; //TODO
    return new Variable(id, symbolTable.getSymbol(id).getDataType());
}

void SemanticAnalyzer::setType(Data::Type tipo){
    // for(std::map<std::string, Symbol>::iterator it = symbolTable.entryList.begin(); it != symbolTable.entryList.end(); ++it) {
    //     if (it->second.getDataType() == Data::UNKNOWN)
    //         symbolTable.addSymbol(it->first, Symbol(tipo, Symbol::VARIABLE, false));
    // }
}
// TreeNode* SemanticAnalyzer::declareFunction(std::string functionId, Vector* params, Vector* body, TreeNode* returnValue) {
//   return NULL;
//
// }

// TreeNode* SemanticAnalyzer::callFunction(std::string functionId, Vector* params) {
//   return NULL;
//
// }
