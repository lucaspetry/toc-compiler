#include "Array.h"

Array::Array(std::string id, Data::Type type, int size) : TreeNode(Data::UNKNOWN) {
    this->id = id;
    this->type = type;
    this->size = size;
}

Array::~Array() {

}

TreeNode::ClassType Array::classType() const {
    return TreeNode::ARRAY;
}

std::string Array::printInOrder() const {
    std::string output = "";
    if (this->type != Data::UNKNOWN){
      output += this->toString(this->type);
      output += " ";
    }
    output += this->id;
    output += "[";
    output += std::to_string(size);
    output += "]";

    return output;
}

void Array::setType(Data::Type type){
  this->type = type;
}
