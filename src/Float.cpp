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

void Float::generateCode(llvm::IRBuilder<>* builder) {
    if(this->code == NULL)
        this->code = llvm::ConstantFP::get(llvm::getGlobalContext(), llvm::APFloat(value));
}