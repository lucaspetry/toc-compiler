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

void Integer::generateCode(llvm::IRBuilder<>* builder) {
    if(this->code == NULL)
        this->code = llvm::ConstantInt::get(llvm::getGlobalContext(), llvm::APInt(64, value));
}