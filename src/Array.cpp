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
    // [in] str saladas_de_frutas[5] >>> [out] str saladas_de_frutas[5]
    return this->id;
}
