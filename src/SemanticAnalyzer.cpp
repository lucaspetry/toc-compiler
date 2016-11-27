#include "SemanticAnalyzer.h"
#include "Symbol.h"

SemanticAnalyzer::SemanticAnalyzer() {
    this->currentStructure = NULL;
    this->symbolTable.newScope();
}

SemanticAnalyzer::~SemanticAnalyzer() {
}

void SemanticAnalyzer::newScope() {
    this->analyzeScopeCreation();
    this->symbolTable.setCurrentStructure(this->currentStructure);
    this->currentStructure = NULL;
    this->symbolTable.newScope();
}

void SemanticAnalyzer::returnScope() {
    this->symbolTable.returnScope();
}

void SemanticAnalyzer::setScope(float indentation) {
    int indINT = (int) indentation;

    if(indINT != indentation) {
        ERROR_LOGGER->log(ErrorLogger::SYNTAX, "INDENTATION 2 SPACES ERROR"); // TODO
        return;
    }

    if(indINT - this->getCurrentIndentation() > 1)
        ERROR_LOGGER->log(ErrorLogger::SEMANTIC, "INDENTATION ERROR"); // TODO
    else if(indINT > this->getCurrentIndentation()) {
        this->newScope();
    } else {
        int ind = this->getCurrentIndentation();
        while(indINT < ind) {
            this->returnScope();
            ind--;
        }
    }
}

void SemanticAnalyzer::pushLineScope(TreeNode* line) {
    this->symbolTable.pushLineScope(line);
}

CodeBlock* SemanticAnalyzer::getCurrentBody() {
    return this->symbolTable.getCurrentCodeBlock();
}

int SemanticAnalyzer::getCurrentIndentation() {
    return this->symbolTable.getCurrentIndentation();
}

void SemanticAnalyzer::setUnknownTypes(Data::Type type, CodeBlock* codeBlock){
    this->symbolTable.setUnknownTypes(type);

    for(int i = 0; i < codeBlock->numberOfLines(); i++)
        codeBlock->getLine(i)->setType(type);
}

void SemanticAnalyzer::analyzeProgram() {
    // Verifica a existência da função toc()
    Symbol tocFunction = this->symbolTable.getSymbol("toc");

    if(tocFunction.getType() != Symbol::FUNCTION
       || tocFunction.getDataType() != Data::VOID)
        ERROR_LOGGER->log(ErrorLogger::SEMANTIC, "Main function toc() not found.");
}

void SemanticAnalyzer::analyzeScopeCreation() {
    if(this->currentStructure == NULL)
        ERROR_LOGGER->log(ErrorLogger::SEMANTIC, "INDENTATION ERROR"); // TODO
}

void SemanticAnalyzer::analyzeCasting(BinaryOperation* binaryOp){
  TreeNode* left = binaryOp->left;
  TreeNode* right = binaryOp->right;
  std::string text = "";

  if (left->dataType() != right->dataType()){
    if(right->dataType() == Data::STR){

      switch (left->dataType()) {
        case Data::BOO:
          if (((String*)right)->isBoolean()){
            binaryOp->right = new TypeCasting(left->dataType(), right);
            right = binaryOp->right;
          } else {
            ERROR_LOGGER->log(ErrorLogger::SEMANTIC, "String value is not false or true.");
          }
          break;
        case Data::FLT:
        case Data::INT:
          if (((String*)right)->isNumber()) {
            binaryOp->right = new TypeCasting(left->dataType(), right);
            right = binaryOp->right;
          } else {
            ERROR_LOGGER->log(ErrorLogger::SEMANTIC, "String value is a number.");
          }
          break;
        default:
          break;
      }

    }else{
        binaryOp->right = new TypeCasting(left->dataType(),right);
        right = binaryOp->right;
    }
  }
}

void SemanticAnalyzer::analyzeRelationalOperationCasting(BinaryOperation* binaryop) {

}

bool SemanticAnalyzer::checkIdentifier(std::string id) const {
    if(this->symbolTable.existsSymbol(id, false)) {
        ERROR_LOGGER->log(ErrorLogger::SEMANTIC, "Identifier " + id + " already used for declaration.");
        return false;
    }

    return true;
}

TreeNode* SemanticAnalyzer::declareVariable(std::string id, Data::Type dataType, int size) {
    if(this->checkIdentifier(id)) {
        // sempre que size é maior do que zero, trata-se de uma declaração de array
        if(size > 0) {
            this->symbolTable.addSymbol(id, Symbol(dataType, Symbol::VARIABLE, false, new Integer(size))); // Adds variable to symbol table and save array size
            return new Array(id, dataType, new Integer(size));
        } else {
            this->symbolTable.addSymbol(id, Symbol(dataType, Symbol::VARIABLE, false)); // Adds variable to symbol table
            // nova declaração de variável

            Variable* v = new Variable(id, dataType);
            VariableDeclaration* vD = new VariableDeclaration(dataType, v);
            v->setSymbolTable(this->symbolTable);
            vD->setSymbolTable(this->symbolTable);
            return vD;
        }
    }

    return NULL;
}

TreeNode* SemanticAnalyzer::declareFunction(std::string id, CodeBlock* params, CodeBlock* body, TreeNode* ret) {
    if(this->checkIdentifier(id)) {
        // Se é a função toc, cria a mesma
        if(!id.compare("toc")) {
            TocFunction* tocFunction = new TocFunction(body);
            this->symbolTable.addSymbol(id, Symbol(Data::VOID, Symbol::FUNCTION, true, tocFunction));
            this->currentStructure = tocFunction;
            return tocFunction;
        }

        // Outra função qualquer
        // TODO
    }

    return NULL;
}

TreeNode* SemanticAnalyzer::assignVariable(std::string id, TreeNode* value, TreeNode* index) {
  if(!this->symbolTable.existsSymbol(id, true)) {
      ERROR_LOGGER->log(ErrorLogger::SEMANTIC, "Undeclared variable " + id + ".");
      return new Variable(id, Data::UNKNOWN); //Creates variable node anyway
  } else if (index != NULL){
      // quando index != null, index pode ser qualquer TreeNode, trata-se de uma atribuição de array
      this->symbolTable.setInitializedSymbol(id);
      return new Array(id, this->symbolTable.getSymbol(id).getDataType(), index, new std::vector<TreeNode*>);
  }  else {
      this->symbolTable.setInitializedSymbol(id, value);
      Variable* v = new Variable(id, this->symbolTable.getSymbol(id).getDataType());
      v->setSymbolTable(this->symbolTable);
      return v;
  }
}

TreeNode* SemanticAnalyzer::declareAssignVariable(std::string id, Data::Type dataType, TreeNode* value, int size) {
    if(this->checkIdentifier(id)) {
        this->symbolTable.addSymbol(id, Symbol(dataType, Symbol::VARIABLE, false)); // Adds variable to symbol table
        // sempre que size é maior do que zero, trata-se de uma declaração de array
        if(size > 0){
            this->symbolTable.setInitializedSymbol(id);
            return new Array(id, dataType, new Integer(size));
        }
        this->symbolTable.setInitializedSymbol(id, value);
        Variable* v = new Variable(id, dataType);
        VariableDeclaration* vD = new VariableDeclaration(dataType, v);
        v->setSymbolTable(this->symbolTable);
        vD->setSymbolTable(this->symbolTable);
        return vD;
    }

  return NULL;
}

TreeNode* SemanticAnalyzer::useVariable(std::string id, TreeNode* index) {
  if(!this->symbolTable.existsSymbol(id, true)) {
      ERROR_LOGGER->log(ErrorLogger::SEMANTIC, "Undeclared variable " + id + ".");
      return new Variable(id, Data::UNKNOWN); //Creates variable node anyway
  } else if(!this->symbolTable.isSymbolInitialized(id, true)) {
      ERROR_LOGGER->log(ErrorLogger::SEMANTIC, "Variable " + id + " used but not initialized.");
  }
  // uso de uma variável do tipo array, verifica se a posição é possivel
  if (index != NULL){
    Symbol s = this->symbolTable.getSymbol(id, true);
    Integer *i = ((Integer*) s.getData());
    Integer *local = ((Integer*) index);
    if(local->getValue() > i->getValue() || local->getValue() < 0)
      ERROR_LOGGER->log(ErrorLogger::SEMANTIC, "Index out of bounds " + id + ".");
    return new Array(id, Data::UNKNOWN, index);
  }

  Variable* v = new Variable(id, this->symbolTable.getSymbol(id).getDataType());
  v->setSymbolTable(this->symbolTable);
  return v;
}
