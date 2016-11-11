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
    if(this->symbolTable.existsSymbol(id, false))
        ERROR_LOGGER->log(ErrorLogger::SEMANTIC, "Re-declaration of variable " + id);
    else {
        this->symbolTable.addSymbol(id, Symbol(dataType, Symbol::VARIABLE, false)); // Adds variable to symbol table
    }

    if (size > 0) {
        return NULL; //TODO
        //return new Array(id, dataType, size);
    } else
        // return NULL; //TODO Precisa setar a tabela de símbolos
        return new Variable(id, dataType); //Creates variable node anyway
}

TreeNode* SemanticAnalyzer::assignVariable(std::string id, TreeNode* index) {
    if(!this->symbolTable.existsSymbol(id, true)) {
        ERROR_LOGGER->log(ErrorLogger::SEMANTIC, "Undeclared variable " + id);
        // return NULL; //TODO Precisa setar a tabela de símbolos
        return new Variable(id, Data::UNKNOWN); //Creates variable node anyway
    } else if (index != NULL){
        this->symbolTable.setInitializedSymbol(id);
        return NULL; //TODO Precisa setar a tabela de símbolos
        //return new Array(id, getSymbolType(id, Symbol::VARIABLE), index);
    }  else {
        this->symbolTable.setInitializedSymbol(id);
        // return NULL; //TODO Precisa setar a tabela de símbolos
        return new Variable(id, this->symbolTable.getSymbol(id).getDataType());
    }
}

TreeNode* SemanticAnalyzer::declareAssignVariable(std::string id, Data::Type dataType) {
    if(this->symbolTable.existsSymbol(id, false))
        ERROR_LOGGER->log(ErrorLogger::SEMANTIC, "Re-declaration of variable " + id);
    else
        this->symbolTable.addSymbol(id, Symbol(dataType, Symbol::VARIABLE, false)); // Adds variable to symbol table

    this->symbolTable.setInitializedSymbol(id);
    // return NULL; //TODO Precisa setar a tabela de símbolos
    return new Variable(id, dataType);
}

TreeNode* SemanticAnalyzer::useVariable(std::string id, TreeNode* index) {
    if(!this->symbolTable.existsSymbol(id, true)) {
        ERROR_LOGGER->log(ErrorLogger::SEMANTIC, "Undeclared variable " + id);
        // return NULL; //TODO Precisa setar a tabela de símbolos
        return new Variable(id, Data::UNKNOWN); //Creates variable node anyway
    } else if (index != NULL){
        return NULL; //TODO Precisa setar a tabela de símbolos
        //return new Array(id, getSymbolType(id, Symbol::VARIABLE), index);
    } else if(!this->symbolTable.isSymbolInitialized(id, true)) {
        ERROR_LOGGER->log(ErrorLogger::SEMANTIC, "Uninitialized variable " + id);
    }
    // return NULL; //TODO Precisa setar a tabela de símbolos
    return new Variable(id, this->symbolTable.getSymbol(id).getDataType());
}

void SemanticAnalyzer::setType(Data::Type tipo){
    // for(std::map<std::string, Symbol>::iterator it = this->symbolTable.entryList.begin(); it != this->symbolTable.entryList.end(); ++it) {
    //     if (it->second.getDataType() == Data::UNKNOWN)
    //         this->symbolTable.addSymbol(it->first, Symbol(tipo, Symbol::VARIABLE, false));
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
