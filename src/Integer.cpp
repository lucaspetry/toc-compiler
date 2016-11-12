#include "Integer.h"

Integer::Integer(int value) : TreeNode(Data::INT) {
    this->value = value;
}

int Integer::getValue(){
  return value;
}
Integer::~Integer() {
}

TreeNode::ClassType Integer::classType() const {
    return TreeNode::INTEGER;
}

std::string Integer::printInOrder() const {
    return std::to_string(value);
}

/**
 * llvm::Value* Integer::generateCode() no CodeGenerator.cpp
 */