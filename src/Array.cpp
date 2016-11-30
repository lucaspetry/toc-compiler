#include "Array.h"

Array::Array(std::string id, Data::Type type, TreeNode* size, std::vector<TreeNode*> *values) : TreeNode(Data::UNKNOWN) {
    this->id = id;
    this->type = type;
    this->size = size;
    this->values = values;
    this->encapsulation = 2;
}

Array::~Array() {

}

TreeNode::ClassType Array::classType() const {
    return TreeNode::ARRAY;
}

std::string Array::printInOrder() const {
    std::string output = "";

    switch (encapsulation) {
      case 0: output+= "pub ";
      break;
      case 1: output+= "prv ";
      break;
      default: break;
    }

    if (this->type != Data::UNKNOWN and this->values == NULL){
      output += Data::toString(this->type);
      output += " ";
    }
    output += this->id;
    output += "[";
    output += this->size->printInOrder();
    output += "]";

    return output;
}

void Array::setBody(CodeBlock* codeBlock) {
}

void Array::setType(Data::Type type){
  this->type = type;
}

std::vector<TreeNode*>* Array::getValues(){
  return this->values;
}

TreeNode* Array::getSize(){
  return this->size;
}

void Array::setEncapsulation(int value){
  this-> encapsulation = value;
}
