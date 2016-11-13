#include "SemanticAnalyzer.h"
#include "Symbol.h"

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
      if(dataType != Data::UNKNOWN)
        setType(dataType);

      if(size > 0){
        this->symbolTable.addSymbol(id, Symbol(dataType, Symbol::VARIABLE, false, new Integer(size))); // Adds variable to symbol table and save array size
        return new Array(id, dataType, new Integer(size));
      }else{
        this->symbolTable.addSymbol(id, Symbol(dataType, Symbol::VARIABLE, false)); // Adds variable to symbol table
        VariableDeclaration *variable = new VariableDeclaration(dataType , new Variable(id, dataType));
        variable->setSymbolTable(this->symbolTable);
        return variable;
      }
    }

  return NULL;
}

TreeNode* SemanticAnalyzer::assignVariable(std::string id, TreeNode* index) {
  if(!this->symbolTable.existsSymbol(id, true)) {
      ERROR_LOGGER->log(ErrorLogger::SEMANTIC, "Undeclared variable " + id);
      return new Variable(id, Data::UNKNOWN); //Creates variable node anyway
  } else if (index != NULL){
      this->symbolTable.setInitializedSymbol(id);
      return new Array(id, this->symbolTable.getSymbol(id).getDataType(), index, new std::vector<TreeNode*>);
  }  else {
      this->symbolTable.setInitializedSymbol(id);
      return new Variable(id, this->symbolTable.getSymbol(id).getDataType());
  }
}

TreeNode* SemanticAnalyzer::declareAssignVariable(std::string id, Data::Type dataType, int size) {
  if(this->symbolTable.existsSymbol(id, false))
    ERROR_LOGGER->log(ErrorLogger::SEMANTIC, "Re-declaration of variable " + id);
  else{
    this->symbolTable.addSymbol(id, Symbol(dataType, Symbol::VARIABLE, false)); // Adds variable to symbol table
    if(size > 0){
      this->symbolTable.setInitializedSymbol(id);
      return new Array(id, dataType, new Integer(size));
    }else{
      this->symbolTable.setInitializedSymbol(id);
      return new VariableDeclaration(dataType, new Variable(id, dataType));
    }
  }
  return NULL;
}

TreeNode* SemanticAnalyzer::useVariable(std::string id, TreeNode* index) {
  if(!this->symbolTable.existsSymbol(id, true)) {
      ERROR_LOGGER->log(ErrorLogger::SEMANTIC, "Undeclared variable " + id);
      return new Variable(id, Data::UNKNOWN); //Creates variable node anyway
  } else if(!this->symbolTable.isSymbolInitialized(id, true)) {
      ERROR_LOGGER->log(ErrorLogger::SEMANTIC, "Uninitialized variable " + id);
  }

  if (index != NULL){
    Symbol s = this->symbolTable.getSymbol(id, true);
    Integer *i = ((Integer*)s.getData());
    Integer *local = ((Integer*) index);
    if(local->getValue() > i->getValue() || local->getValue() < 0)
      ERROR_LOGGER->log(ErrorLogger::SEMANTIC, "Index out of bounds " + id);
    return new Array(id, Data::UNKNOWN, index);
  }

  return new Variable(id, this->symbolTable.getSymbol(id).getDataType());
}

void SemanticAnalyzer::setType(Data::Type type){
  // std::map<std::string, Symbol>::iterator iter;
  // for(iter = entryList.begin(); iter != entryList.end(); iter++){
  //   if (iter->second.getDataType() == Data::UNKNOWN){
  //     entryList[iter->first].setDataType(type);
  //   }
  // }
}
