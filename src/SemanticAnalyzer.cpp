#include "SemanticAnalyzer.h"
#include "Symbol.h"
#include "PrintFunction.h"

SemanticAnalyzer::SemanticAnalyzer() {
    this->currentStructure = NULL;
    this->lastStatement = NULL;
    this->symbolTable.newScope();
}

SemanticAnalyzer::~SemanticAnalyzer() {
}

void SemanticAnalyzer::analyzeRelationalOperationCasting(BinaryOperation* binaryop) {
}

void SemanticAnalyzer::newScope() {
    this->analyzeScopeCreation();
    this->symbolTable.setCurrentStructure(this->currentStructure);
    this->symbolTable.setLastStatement(this->lastStatement);
    this->currentStructure = NULL;
    this->symbolTable.newScope();
}

void SemanticAnalyzer::returnScope() {
    this->symbolTable.returnScope();
    this->lastStatement = this->symbolTable.getLastStatement();
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

void SemanticAnalyzer::setUnknownTypes(Data::Type type, CodeBlock* codeBlock) {
    this->symbolTable.setUnknownTypes(type);

    for(int i = 0; i < codeBlock->numberOfLines(); i++){
      codeBlock->getLine(i)->setType(type);
    }
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

void SemanticAnalyzer::analyzeCasting(BinaryOperation* binaryOp) {
  TreeNode* left = binaryOp->left;
  TreeNode* right = binaryOp->right;
  std::string text = "";

  if (left->dataType() != right->dataType()) {
    if(right->dataType() == Data::STR) {

      switch (left->dataType()) {
        case Data::BOO:
          if (((String*)right)->isBoolean() || this->symbolTable.getSymbol(((Variable*)right)->getId()).getData()->dataType()) {
            binaryOp->right = new TypeCasting(left->dataType(), right);
            right = binaryOp->right;
          } else {
            ERROR_LOGGER->log(ErrorLogger::SEMANTIC, "String value is not false or true.");
          }
          break;
        case Data::FLT:
        case Data::INT:
          if (((String*)right)->isNumber() || this->symbolTable.getSymbol(((Variable*)right)->getId()).getData()->dataType()) {
            binaryOp->right = new TypeCasting(left->dataType(), right);
            right = binaryOp->right;
          } else {
            ERROR_LOGGER->log(ErrorLogger::SEMANTIC, "String value is not a number.");
          }
          break;
        default:
          break;
      }

    }else{
        binaryOp->right = new TypeCasting(binaryOp->dataType(), right);
        right = binaryOp->right;
    }
  }
}

void SemanticAnalyzer::analyzeLoop(std::string id) {
  if(this->symbolTable.getSymbol(id, true).getData()->classType() != TreeNode::ARRAY)
    ERROR_LOGGER->log(ErrorLogger::SEMANTIC, "Expecting an array type " + id + ".");
}

void SemanticAnalyzer::analyzeArray(std::string id, int size, TreeNode* attribuition){
  BinaryOperation* node = (BinaryOperation*)attribuition;
  int c = 0;
  if(attribuition->classType() != TreeNode::BINARY_OPERATION && size > 1)
    ERROR_LOGGER->log(ErrorLogger::SEMANTIC, "Illegal array assignment.");
  else if(attribuition->classType() == TreeNode::BINARY_OPERATION){
    while(node->right->classType() == TreeNode::BINARY_OPERATION){
      c ++;
      if(node->right->classType() != TreeNode::BINARY_OPERATION)
        break;
      node = (BinaryOperation*)(node->right);
    }
    c = c + 2;
    if(c > size)
      ERROR_LOGGER->log(ErrorLogger::SEMANTIC, "Number of elements in assignment differs from array length.");
  }
}

void SemanticAnalyzer::analyzeAssignArray(std::string id, TreeNode* size){
  // Integer* i = (Integer*) size;
  // TreeNode* t = this->symbolTable.getSymbol(id, true).getData();
  // if (t->classType() == TreeNode::ARRAY)
  //   std::cout << "a" << std::endl;
  // // TreeNode* s = array->getSize();
  // // if(i->getValue() > s->getValue())

}

bool SemanticAnalyzer::checkIdentifier(std::string id) const {
    if(this->symbolTable.existsSymbol(id, false)) {
        ERROR_LOGGER->log(ErrorLogger::SEMANTIC, "Identifier " + id + " already used for declaration.");
        return false;
    }

    return true;
}

TreeNode* SemanticAnalyzer::cast(Data::Type type, TreeNode* node) const {
    if(type != node->dataType())
        return new TypeCasting(type, node);

    return node;
}

bool SemanticAnalyzer::checkStatement(TreeNode::ClassType tipo){
    if(this->symbolTable.getParentStructure() == NULL && tipo != TreeNode::TOC_FUNCTION && tipo != TreeNode::FUNCTION && tipo != TreeNode::OBJECT && tipo != TreeNode::VARIABLE_DECLARATION)
        return false;
    switch (tipo) {

      case TreeNode::LOOP:
      case TreeNode::CONDITIONAL: if(this->symbolTable.getParentStructure()->classType() == TreeNode::FUNCTION ||
                        this->symbolTable.getParentStructure()->classType() == TreeNode::TOC_FUNCTION ||
                        this->symbolTable.getParentStructure()->classType() == TreeNode::CONDITIONAL ||
                        this->symbolTable.getParentStructure()->classType() == TreeNode::LOOP)
                          return true;
                        return false;
      case TreeNode::TOC_FUNCTION: if(this->symbolTable.getParentStructure() == NULL)
                                        return true;
                                  return false;
      case TreeNode::FUNCTION: if(this->symbolTable.getParentStructure() == NULL || this->symbolTable.getParentStructure()->classType() == TreeNode::OBJECT)
                                      return true;
                                return false;
      case TreeNode::VARIABLE:
      case TreeNode::ARRAY:
      case TreeNode::VARIABLE_DECLARATION: if(this->lastStatement!= NULL && this->lastStatement->classType() == TreeNode::OBJECT)
                                              return false;
                                            return true;
      case TreeNode::OBJECT:  if(this->symbolTable.getParentStructure() == NULL)
                                    return true;
                              return false;
      // case TreeNode::BINARY_OPERATION: if(this->symbolTable.getParentStructure() != NULL)
      //                                     return false;
      //                                 return true;
      //                       }
    }
  }

TreeNode* SemanticAnalyzer::declareVariable(std::string id, Data::Type dataType, int size) {
    if(this->checkIdentifier(id)) {
        if(size > 0) {
            Array* array = new Array(id, dataType, new Integer(size));
            this->symbolTable.addSymbol(id, Symbol(dataType, Symbol::VARIABLE, false, array)); // Adds variable to symbol table and save array size
            return array;
        } else {
            this->symbolTable.addSymbol(id, Symbol(dataType, Symbol::VARIABLE, false)); // Adds variable to symbol table
            Variable* v = new Variable(id, dataType);
            VariableDeclaration* vD = new VariableDeclaration(dataType, v);
            v->setSymbolTable(this->symbolTable);
            vD->setSymbolTable(this->symbolTable);
            return vD;

    }
    // return a random variable if id is in use
    return new VariableDeclaration(dataType, new Variable(id, dataType));
}
}

TreeNode* SemanticAnalyzer::declareBinaryOperation(TreeNode* left, BinaryOperation::Type op, TreeNode* right) {
    // if(!checkStatement(TreeNode::BINARY_OPERATION))
    //   ERROR_LOGGER->log(ErrorLogger::SEMANTIC, "Illegal instruction.");
    BinaryOperation* binOP = new BinaryOperation(left,op,right);
    this->currentStructure = binOP;
    this->lastStatement = binOP;
    return binOP;
}

TreeNode* SemanticAnalyzer::declareObject(std::string id, CodeBlock* param, CodeBlock* body){
  if(!checkStatement(TreeNode::OBJECT))
    ERROR_LOGGER->log(ErrorLogger::SEMANTIC, "Illegal declaration of object in this scope.");

    if(this->checkIdentifier(id)) {
        Object* obj = new Object(id,param,NULL);
        this->symbolTable.addSymbol(id, Symbol(Data::OBJ, Symbol::OBJECT, true, obj));
        this->currentStructure = obj;
        this->lastStatement = obj;
        return obj;
    }
    return NULL;
}

TreeNode* SemanticAnalyzer::declareAttribute(std::string id, Data::Type type, int encapsulation, int size) {
  if(this->symbolTable.getParentStructure() == NULL || this->symbolTable.getParentStructure()->classType() != TreeNode::OBJECT)
      ERROR_LOGGER->log(ErrorLogger::SEMANTIC, "Encapsulation out of object scope.");

    Object* o = (Object*)this->symbolTable.getParentStructure();

    if(size > 0){
        Array* a = new Array(id, type, new Integer(size));
        a->setEncapsulation(encapsulation);
        this->symbolTable.addSymbol(id, Symbol(type, Symbol::VARIABLE, true, a));
        if(encapsulation == 1)
          this->symbolTable.getSymbol(id).setEncapsulation(true);
        this->lastStatement = a;
        o->setSymbolTable(this->symbolTable);
        return a;
    }else{
      VariableDeclaration* vd = new VariableDeclaration(type, new Variable(id, type));
      vd->setEncapsulation(encapsulation);
      this->symbolTable.addSymbol(id, Symbol(type, Symbol::VARIABLE, true, vd));
      if(encapsulation == 1)
        this->symbolTable.getSymbol(id).setEncapsulation(true);
      this->lastStatement = vd;
      o->setSymbolTable(this->symbolTable);
      return vd;
    }
  return NULL;
}

TreeNode* SemanticAnalyzer::declareAssignAttribute(std::string id, Data::Type type, int encapsulation, TreeNode* value, int size) {
  if(this->symbolTable.getParentStructure() == NULL || this->symbolTable.getParentStructure()->classType() != TreeNode::OBJECT)
      ERROR_LOGGER->log(ErrorLogger::SEMANTIC, "Encapsulation out of object scope.");

    Object* o = (Object*)this->symbolTable.getParentStructure();

    if(this->checkIdentifier(id)) {
        if(size > 0) {
            Array* array = new Array(id, type, new Integer(size));
            array->setEncapsulation(encapsulation);
            this->symbolTable.addSymbol(id, Symbol(type, Symbol::VARIABLE, false, array)); // Adds variable to symbol table and save array size
            this->symbolTable.setInitializedSymbol(id, array);
            if(encapsulation == 1)
              this->symbolTable.getSymbol(id).setEncapsulation(true);
            this->lastStatement = array;
            o->setSymbolTable(this->symbolTable);
            return array;
        }

        this->symbolTable.addSymbol(id, Symbol(type, Symbol::VARIABLE, false)); // Adds variable to symbol table
        this->symbolTable.setInitializedSymbol(id, value);
        Variable* v = new Variable(id, type);
        VariableDeclaration* vD = new VariableDeclaration(type, v);
        vD->setEncapsulation(encapsulation);
        if(encapsulation == 1)
          this->symbolTable.getSymbol(id).setEncapsulation(true);
        v->setSymbolTable(this->symbolTable);
        vD->setSymbolTable(this->symbolTable);
        this->lastStatement = vD;
        o->setSymbolTable(this->symbolTable);
        return vD;
    }

  return NULL;
}

TreeNode* SemanticAnalyzer::declareMethod(std::string id, CodeBlock* params, CodeBlock* body, Data::Type returnType, int encapsulation) {
  if(this->symbolTable.getParentStructure() == NULL || this->symbolTable.getParentStructure()->classType() != TreeNode::OBJECT)
      ERROR_LOGGER->log(ErrorLogger::SEMANTIC, "Encapsulation method out of object scope.");

    Function* function;
    Object* o = (Object*)this->symbolTable.getParentStructure();
    if(this->checkIdentifier(id)) {
        function = new Function(id, params, body, NULL);
        function->setType(returnType);
        function->setEncapsulation(encapsulation);

        this->symbolTable.addSymbol(id, Symbol(returnType, Symbol::FUNCTION, true, function));
        this->currentStructure = function;
        this->lastStatement = function;
        o->setSymbolTable(this->symbolTable);
        return function;
  }

  return NULL;
}

TreeNode* SemanticAnalyzer::declareFunction(std::string id, CodeBlock* params, CodeBlock* body, Data::Type returnType) {
    if(this->checkIdentifier(id)) {
        TreeNode* function;

        if(!id.compare("toc")) { // Se é a função toc, cria a mesma
            if(!checkStatement(TreeNode::TOC_FUNCTION))
              ERROR_LOGGER->log(ErrorLogger::SEMANTIC, "Illegal toc function declaration in this scope." );
            function = new TocFunction(body);
        } else { // Outra função qualquer
            if(!checkStatement(TreeNode::FUNCTION))
              ERROR_LOGGER->log(ErrorLogger::SEMANTIC, "Illegal function declaration in this scope." );

            function = new Function(id, params, body, NULL);
            function->setType(returnType);
        }

        this->symbolTable.addSymbol(id, Symbol(returnType, Symbol::FUNCTION, true, function));
        this->currentStructure = function;
        this->lastStatement = function;
        return function;
    }

    return NULL;
}

TreeNode* SemanticAnalyzer::declareFunctionReturn(TreeNode* ret) {
    Function* f = NULL;
    if(this->symbolTable.getParentStructure()->classType() == TreeNode::FUNCTION)
      f = (Function*) this->symbolTable.getParentStructure();
    if(f->dataType() != ret->dataType()){
      ERROR_LOGGER->log(ErrorLogger::SEMANTIC, "Return value for function " + f->getId() + "is different from expected;" );
    }

    f->setReturn(ret);
    return NULL; // TODO
}

TreeNode* SemanticAnalyzer::declareCondition(TreeNode* expression, CodeBlock* body) {
    if(!checkStatement(TreeNode::CONDITIONAL))
        ERROR_LOGGER->log(ErrorLogger::SEMANTIC, "Illegal declaration of if in this scope." );

    Conditional* cond = new Conditional(expression, body, NULL);
    this->currentStructure = cond;
    this->lastStatement = cond;
    return cond;

}

TreeNode* SemanticAnalyzer::declareElseCondition(CodeBlock* body) {
    std::string elseError = "Else without a if.";

    if(this->lastStatement->classType() != TreeNode::CONDITIONAL){
        ERROR_LOGGER->log(ErrorLogger::SEMANTIC, elseError);
      }

    Conditional* cond = (Conditional*) this->lastStatement;

    if(cond->hasElse())
        ERROR_LOGGER->log(ErrorLogger::SEMANTIC, elseError);

    cond->setElse(true);
    this->currentStructure = this->lastStatement;
    return this->currentStructure;
}

TreeNode* SemanticAnalyzer::declareLoop(TreeNode* init, TreeNode* test, TreeNode* attribuition) {
  if(!checkStatement(TreeNode::LOOP))
      ERROR_LOGGER->log(ErrorLogger::SEMANTIC, "Illegal declaration of loop in this scope." );

    Loop* loop;

    if(test == NULL) {
      Variable* v = (Variable*) attribuition;
      std::string id = v->getId();
      Array* array = (Array*)this->symbolTable.getSymbol(id, true).getData();
      loop = new Loop(init, test, array);
    }else{
      loop = new Loop(init, test, attribuition);

  }
    this->currentStructure = loop;
    this->lastStatement = loop;
    return loop;
}

TreeNode* SemanticAnalyzer::declarePrint(TreeNode* param) {
    TreeNode* paramPrint = param;

    if(param->dataType() != Data::STR)
        paramPrint = new TypeCasting(Data::STR, paramPrint);

    return new PrintFunction(paramPrint);
}


TreeNode* SemanticAnalyzer::assignVariable(std::string id, TreeNode* value, TreeNode* index) {
  if(!this->symbolTable.existsSymbol(id, true)) {
      ERROR_LOGGER->log(ErrorLogger::SEMANTIC, "Undeclared variable " + id + ".");
      return new Variable(id, Data::UNKNOWN); //Creates variable node anyway
  } else if (index != NULL) {
        this->symbolTable.setInitializedSymbol(id);
        Array* a = (Array*)this->symbolTable.getSymbol(id).getData();
        return new Array(id, this->symbolTable.getSymbol(id).getDataType(), index, value);
  }  else {
      this->symbolTable.setInitializedSymbol(id, value);
      Variable* v = new Variable(id, this->symbolTable.getSymbol(id, true).getDataType());
      v->setSymbolTable(this->symbolTable);
      return v;
  }
}

TreeNode* SemanticAnalyzer::declareAssignVariable(std::string id, Data::Type dataType, TreeNode* value, int size) {
    if(this->checkIdentifier(id)) {
        // sempre que size é maior do que zero, trata-se de uma declaração de array
        if(size > 0) {
          if(!checkStatement(TreeNode::ARRAY))
              ERROR_LOGGER->log(ErrorLogger::SEMANTIC, "Declaration of array "+id+" expected encapsulation.");

            Array* array = new Array(id, dataType, new Integer(size), value);
            this->symbolTable.addSymbol(id, Symbol(dataType, Symbol::VARIABLE, false, array)); // Adds variable to symbol table and save array size
            this->symbolTable.setInitializedSymbol(id, array);
            return array;
        }
        if(!checkStatement(TreeNode::VARIABLE_DECLARATION))
            ERROR_LOGGER->log(ErrorLogger::SEMANTIC, "Declaration of variable "+id+" expected encapsulation.");

        this->symbolTable.addSymbol(id, Symbol(dataType, Symbol::VARIABLE, false, value)); // Adds variable to symbol table
        this->symbolTable.setInitializedSymbol(id, value);

        Variable* v = new Variable(id, dataType);
        VariableDeclaration* vD = new VariableDeclaration(dataType, v);
        v->setSymbolTable(this->symbolTable);
        vD->setSymbolTable(this->symbolTable);
        this->lastStatement = vD;
        return vD;
    }

  // return a random variable case id is in use
  return new VariableDeclaration(dataType, new Variable(id, dataType));
}
TreeNode* SemanticAnalyzer::useObject(std::string id,std::string value){
  return NULL;

}
TreeNode* SemanticAnalyzer::initializeObject(std::string classe, std::string object){
  return NULL;
}

TreeNode* SemanticAnalyzer::useVariable(std::string id, TreeNode* index) {
  if(!this->symbolTable.existsSymbol(id, true)) {
      ERROR_LOGGER->log(ErrorLogger::SEMANTIC, "Undeclared variable " + id + ".");
      return new Variable(id, Data::UNKNOWN); //Creates variable node anyway
  } else if(!this->symbolTable.isSymbolInitialized(id, true)) {
      ERROR_LOGGER->log(ErrorLogger::SEMANTIC, "Variable " + id + " used but not initialized.");
  }

  TreeNode* t = this->symbolTable.getSymbol(id, true).getData();
  if (index != NULL and t->classType() == TreeNode::ARRAY) {
    Array* array = (Array*)t;
    if (array != NULL and array->getSize()->classType() == TreeNode::INTEGER) {
      if(((Integer*)index)->getValue() > ((Integer*)(array->getSize()))->getValue() || ((Integer*)index)->getValue() < 0)
        ERROR_LOGGER->log(ErrorLogger::SEMANTIC, "Index out of bounds " + id + ".");
    }
    return new Array(id, this->symbolTable.getSymbol(id,true).getDataType(), index);
  }
  Variable* v = new Variable(id, this->symbolTable.getSymbol(id,true).getDataType());
  v->setSymbolTable(this->symbolTable);
  return v;
}
