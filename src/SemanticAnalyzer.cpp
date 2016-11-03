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
  if(symbolExists(id, Symbol::VARIABLE, false))
        yyerror("semantic error: re-declaration of variable %s\n", id.c_str());
    else {
        symbolTable.addSymbol(id, Symbol(dataType, Symbol::VARIABLE, false)); // Adds variable to symbol table
    }

    if (size > 0) {
       return NULL; //TODO
       //return new Array(id, dataType, size);
    } else
        return NULL; //TODO
        //return new Variable(id, dataType); //Creates variable node anyway

}

TreeNode* SemanticAnalyzer::assignVariable(std::string id, Data::Type assignedType, TreeNode* index) {
  if(!symbolExists(id, Symbol::VARIABLE, true)) {
      yyerror("semantic error: undeclared variable %s\n", id.c_str());
      return NULL; //TODO
      //return new Variable(id, Data::UNKNOWN); //Creates variable node anyway
  } else if (index != NULL){
        setInitializedSymbol(id, Symbol::VARIABLE);
        return NULL; //TODO
        //return new Array(id, getSymbolType(id, Symbol::VARIABLE), index);
  }  else {
      setInitializedSymbol(id, Symbol::VARIABLE);
      return NULL; //TODO
      //return new Variable(id, getSymbolType(id, Symbol::VARIABLE));
  }
}

TreeNode* SemanticAnalyzer::declareAssignVariable(std::string id, Data::Type dataType, Data::Type assignedType) {
  if(symbolExists(id, Symbol::VARIABLE, false))
          yyerror("semantic error: re-declaration of variable %s\n", id.c_str());
      else
         symbolTable.addSymbol(id, Symbol(dataType, Symbol::VARIABLE, false)); // Adds variable to symbol table

      setInitializedSymbol(id, Symbol::VARIABLE);
      return NULL; //TODO
      //return new Variable(id, dataType);
}

TreeNode* SemanticAnalyzer::useVariable(std::string id, TreeNode* index) {
  if(!symbolExists(id, Symbol::VARIABLE, true)) {
      yyerror("semantic error: undeclared variable %s\n", id.c_str());
      return NULL; //TODO
      //return new Variable(id, Data::UNKNOWN); //Creates variable node anyway
  } else if (index != NULL){
      return NULL; //TODO
      //return new Array(id, getSymbolType(id, Symbol::VARIABLE), index);
  } else if(!isSymbolInitialized(id, Symbol::VARIABLE, true)) {
      yyerror("semantic error: uninitialized variable %s\n", id.c_str());
  }
  return NULL; //TODO
  //return new Variable(id, getSymbolType(id, Symbol::VARIABLE));
}

// TreeNode* SemanticAnalyzer::declareFunction(std::string functionId, Vector* params, Vector* body, TreeNode* returnValue) {
//   return NULL;
//
// }

// TreeNode* SemanticAnalyzer::callFunction(std::string functionId, Vector* params) {
//   return NULL;
//
// }

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