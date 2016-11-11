#include "Float.h"

Float::Float(float value) : TreeNode(Data::FLT) {
    this->value = value;
}

Float::~Float() {
}

TreeNode::ClassType Float::classType() const {
    return TreeNode::FLOAT;
}

std::string Float::printInOrder() const{
    return std::to_string(value);
}

llvm::Value* Float::generateCode() {
    return llvm::ConstantFP::get(IR::Context, llvm::APFloat(value));
}