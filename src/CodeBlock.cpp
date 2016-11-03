#include "CodeBlock.h"

CodeBlock::CodeBlock() : TreeNode(Data::UNKNOWN) {
}

CodeBlock::~CodeBlock() {
}

TreeNode::ClassType CodeBlock::classType() const {
    return TreeNode::CODE_BLOCK;
}

std::string CodeBlock::printInOrder() const {
    return ""; // TODO
}

int CodeBlock::numberOfLines() const {
    return this->lines.size();
}

void CodeBlock::insertLine(TreeNode* line) {
    this->lines.insert(this->lines.begin(), line);
}

void CodeBlock::generateCode() const{
  //TODO;
}
