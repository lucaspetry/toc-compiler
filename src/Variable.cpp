#include "Variable.h"

Variable::Variable(std::string id, Data::Type type) : TreeNode(type) {
    this->id = id;
}

Variable::~Variable() {
}

TreeNode::ClassType Variable::classType() const {
    return TreeNode::VARIABLE;
}

std::string Variable::printInOrder() const {
    return this->id;
}

std::string Variable::getId() const {
    return id;
}

llvm::Value* Variable::generateCode(llvm::IRBuilder<>* builder) {
    return NULL;// TODO;
}
