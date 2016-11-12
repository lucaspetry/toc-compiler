#include "Variable.h"

Variable::Variable(std::string id, Data::Type type) : TreeNode(type) {
    this->id = id;

}

Variable::~Variable() {
}

TreeNode::ClassType Variable::classType() const {
    return TreeNode::VARIABLE;
}

std::string Variable::getId() const {
    return id ;
}

std::string Variable::printInOrder() const {
    return id;
}

/**
 * llvm::Value* Variable::generateCode() no CodeGenerator.cpp
 */