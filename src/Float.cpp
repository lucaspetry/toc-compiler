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

void Float::setBody(CodeBlock* codeBlock) {
}
