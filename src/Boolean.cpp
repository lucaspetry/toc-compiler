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
  switch(value) {
    case true:
       return "true";
    default:
       return "false";
  }
}

void Boolean::generateCode() const {
  //TODO;
}
