#include "Variable.h"

Variable::Variable(std::string id) : TreeNode(Data::STR) {
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
