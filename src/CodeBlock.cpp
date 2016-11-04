#include "CodeBlock.h"

CodeBlock::CodeBlock() : TreeNode(Data::UNKNOWN) {
}

CodeBlock::~CodeBlock() {
}

TreeNode::ClassType CodeBlock::classType() const {
    return TreeNode::CODE_BLOCK;
}

std::string CodeBlock::printInOrder() const {
    std::string output;
    for(TreeNode* myTreenode: this->lines){
      if(myTreenode != NULL)
        output += myTreenode->printInOrder();
    }
    return output;
}

int CodeBlock::numberOfLines() const {
    return this->lines.size();
}

void CodeBlock::insertLine(TreeNode* line) {
    this->lines.insert(this->lines.begin(), line);
}
