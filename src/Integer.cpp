#include "Integer.h"

Integer::Integer(int value) : TreeNode(Data::INT) {
    this->value = value;
}

Integer::~Integer() {
}

int Integer::getValue(){
  return value;
}

TreeNode::ClassType Integer::classType() const {
    return TreeNode::INTEGER;
}

std::string Integer::printInOrder() const {
    return std::to_string(value);
}

llvm::Value* Integer::generateCode(llvm::IRBuilder<>* builder) {
    return llvm::ConstantInt::get(llvm::getGlobalContext(), llvm::APInt(64, value));
}
