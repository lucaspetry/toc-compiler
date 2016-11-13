#include "String.h"

String::String(std::string text) : TreeNode(Data::STR) {
    this->text = text;
}

std::string String::getText(){
  return text;
}
String::~String() {
}

TreeNode::ClassType String::classType() const {
    return TreeNode::STRING;
}

std::string String::printInOrder() const {
    return text;
}

/**
 * llvm::Value* Integer::generateCode() no CodeGenerator.cpp
 */
