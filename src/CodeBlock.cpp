#include "CodeBlock.h"

CodeBlock::CodeBlock(int indentation) : TreeNode(Data::UNKNOWN) {
    this->indentation = indentation;
}

CodeBlock::~CodeBlock() {
}

TreeNode::ClassType CodeBlock::classType() const {
    return TreeNode::CODE_BLOCK;
}

std::string CodeBlock::printInOrder() const {
    std::string output = "";

    for(TreeNode* myTreenode: this->lines){
        output += this->printIndentation();
        output += myTreenode->printInOrder();
        if(myTreenode->classType()!= TreeNode::VARIABLE)
            output += "\n";
    }
    return output;
}

int CodeBlock::numberOfLines() const {
    return this->lines.size();
}

TreeNode* CodeBlock::getLine(int lineNumber) {
    return this->lines[lineNumber];
}

void CodeBlock::insertLine(TreeNode* line) {
    this->lines.insert(this->lines.begin(), line);
}

std::string CodeBlock::printIndentation() const {
    std::string output = "";
    for(int i = 1; i <= this->indentation; i++){
        output += "  ";
    }
    return output;
}
