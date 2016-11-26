#include "Array.h"

Array::Array(std::string id, Data::Type type, TreeNode* size, std::vector<TreeNode*> *values) : TreeNode(Data::UNKNOWN) {
    this->id = id;
    this->type = type;
    this->size = size;
    this->values = values;
}

Array::~Array() {

}

TreeNode::ClassType Array::classType() const {
    return TreeNode::ARRAY;
}

std::string Array::printInOrder() const {
    std::string output = "";
    if (this->type != Data::UNKNOWN and this->values == NULL){
      output += Data::toString(this->type);
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
