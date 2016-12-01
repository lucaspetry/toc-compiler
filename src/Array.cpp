#include "Array.h"

Array::Array(std::string id, Data::Type type, TreeNode* size, TreeNode* values) : TreeNode(type) {
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

    if(this->values != NULL && this->values->classType() == TreeNode::BINARY_OPERATION
      && this->type != Data::UNKNOWN){
      output += toString(this->type);
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

TreeNode* Array::getValues(){
  return this->values;
}

TreeNode* Array::getSize(){
  return this->size;
}

void Array::setEncapsulation(int value){
  this-> encapsulation = value;
}
