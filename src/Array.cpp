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
    std::string output = "";
    output += this->toString(this->type);
    output += " ";
    output += this->id;
    output += "[";
    output += std::to_string(size);
    output += "]";
    std::cout << output << std::endl;

    return output;
}
