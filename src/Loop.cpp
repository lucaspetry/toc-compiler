#include "Loop.h"

Loop::Loop(TreeNode* init, TreeNode* test, TreeNode* attribuition) : TreeNode(Data::UNKNOWN) {
    this->init = init;
    this->test = test;
    this->attribuition = attribuition;
}

Loop::~Loop() {

}

TreeNode::ClassType Loop::classType() const {
    return Loop::LOOP;
}

std::string Loop::printInOrder() const {
    std::string output = "";

    output += "for";
    output += "(";

    if(test != NULL){

      output += this->init->printInOrder();
      output += "; ";
      output += this->test->printInOrder();
      output += "; ";
      output += this->attribuition->printInOrder();

    }else{

      VariableDeclaration* vd = (VariableDeclaration*)this->init;
      Variable* v = (Variable*) vd->getNext();
      // Array* a = (Array*) attribuition;
      attribuition->setType(Data::UNKNOWN);

      output += v->printInOrder();
      output += " in ";
      output += attribuition->printInOrder();

    }

    output += ")";

    if(this->body != NULL){
      output += "\n";
      output += this->body->printInOrder();
    }

    return output;
}

void Loop::setBody(CodeBlock* codeBlock) {
  this->body = codeBlock;
}
