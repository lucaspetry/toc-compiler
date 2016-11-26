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

void Boolean::setBody(CodeBlock* codeBlock) {
}
