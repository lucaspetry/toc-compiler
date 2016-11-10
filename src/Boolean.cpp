#include "Boolean.h"

Boolean::Boolean(bool value) : TreeNode(Data::BOO) {
    this->value = value;
}

Boolean::~Boolean() {
}

TreeNode::ClassType Boolean::classType() const {
    return TreeNode::BOOLEAN;
}

std::string Boolean::printInOrder() const {
    if(value)
        return "true";
    
    return "false";
}

llvm::Value* Boolean::generateCode(llvm::IRBuilder<>* builder) {
    // TODO não sei se isso está ok
    bool equivalent = value ? 1 : 0;
    return llvm::ConstantInt::get(llvm::getGlobalContext(), llvm::APInt(64, equivalent));
}