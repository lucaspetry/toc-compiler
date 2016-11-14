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

void SemanticAnalyzer::analyzeCasting(BinaryOperation* binaryOp){
  TreeNode* left = binaryOp->left;
  BinaryOperation::Type op = binaryOp->operation;
  TreeNode* right = binaryOp->right;

  if (left->dataType() != right->dataType() && op == BinaryOperation::ASSIGN){
    if(right->dataType() == Data::STR){
      std::string text = "";
      if(left->dataType() == Data::BOO){
        text = ((String*)right)->getValue();
        text.erase(0, 1);
        text.erase(text.size() - 1);
        if (text == "false" || text == "true"){
          binaryOp->right = new TypeCasting(left->dataType(),right);
          right = binaryOp->right;
        } else {
          ERROR_LOGGER->log(ErrorLogger::SEMANTIC, "String value is not false or true.");
        }
      } else if (left->dataType() == Data::FLT || left->dataType() == Data::INT){
          text = ((String*)right)->getValue();
          text.erase(0, 1);
          text.erase(text.size() - 1);
          if (std::all_of(text.begin(), text.end(), ::isdigit)) {
            binaryOp->right = new TypeCasting(left->dataType(),right);
            right = binaryOp->right;
          } else {
            ERROR_LOGGER->log(ErrorLogger::SEMANTIC, "String value is a number.");
        }
      }
    } else{
        binaryOp->right = new TypeCasting(left->dataType(),right);
        right = binaryOp->right;
    }
  }
}


TreeNode* SemanticAnalyzer::declareVariable(std::string id, Data::Type dataType, int size) {
  if(this->symbolTable.existsSymbol(id, false))
      ERROR_LOGGER->log(ErrorLogger::SEMANTIC, "Re-declaration of variable " + id);
  else {
      // sempre que a declaração uma variavel tipada, busca pelas não tipadas na tabela para atualização
      if(dataType != Data::UNKNOWN)
        setType(dataType);
      // sempre que size é maior do que zero, trata-se de uma declaração de array
      if(size > 0){
        this->symbolTable.addSymbol(id, Symbol(dataType, Symbol::VARIABLE, false, new Integer(size))); // Adds variable to symbol table and save array size
        return new Array(id, dataType, new Integer(size));
      }else{
        this->symbolTable.addSymbol(id, Symbol(dataType, Symbol::VARIABLE, false)); // Adds variable to symbol table
        // nova declaração de variável
        VariableDeclaration *variable = new VariableDeclaration(dataType , new Variable(id, dataType));
        variable->setSymbolTable(this->symbolTable);
        return variable;
      }
    }
  // não se deve chegar nesse ponto
  return NULL;
}

TreeNode* SemanticAnalyzer::assignVariable(std::string id, TreeNode* index) {
  if(!this->symbolTable.existsSymbol(id, true)) {
      ERROR_LOGGER->log(ErrorLogger::SEMANTIC, "Undeclared variable " + id);
      return new Variable(id, Data::UNKNOWN); //Creates variable node anyway
  } else if (index != NULL){
      // quando index != null, index pode ser qualquer TreeNode, trata-se de uma atribuição de array
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
    // sempre que size é maior do que zero, trata-se de uma declaração de array
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
  // uso de uma variável do tipo array, verifica se a posição é possivel
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
// for(std::map<std::string, Symbol>::iterator it = this->symbolTable.entryList.begin(); it != this->symbolTable.entryList.end(); ++it) {
//     if (it->second.getDataType() == Data::UNKNOWN)
// }
//         this->symbolTable.addSymbol(it->first, Symbol(tipo, Symbol::VARIABLE, false));
}
