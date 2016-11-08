#include "Integer.h"

Integer::Integer(int integer) : TreeNode(Data::STR) {
    this->integer = integer;
}

Integer::~Integer() {
}

TreeNode::ClassType Integer::classType() const {
    return TreeNode::INTEGER;
}

std::string Integer::printInOrder() const {
    return std::to_string(this->integer);
}
