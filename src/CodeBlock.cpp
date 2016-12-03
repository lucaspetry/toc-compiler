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

    for(TreeNode* node : this->lines){
        if(node->classType() != TreeNode::CODE_BLOCK)
            output += this->printIndentation();
        output += node->printInOrder();
        output += "\n";
    }
    return output.substr(0, output.size()-1);
}

std::string CodeBlock::printInLine() const {
    std::string output = "";

    for(TreeNode* node : this->lines){
        output += node->printInOrder();
        output += ", ";
    }
    return output.substr(0, output.size()-2);
}

void CodeBlock::setBody(CodeBlock* codeBlock) {
}

int CodeBlock::numberOfLines() const {
    return this->lines.size();
}

TreeNode* CodeBlock::getLine(int lineNumber) {
    return this->lines[lineNumber];
}

void CodeBlock::insertLineFront(TreeNode* line) {
    this->lines.insert(this->lines.begin(), line);
}

void CodeBlock::insertLineBack(TreeNode* line) {
    this->lines.insert(this->lines.end(), line);
}

std::string CodeBlock::printIndentation() const {
    std::string output = "";
    for(int i = 1; i <= this->indentation; i++){
        output += "  ";
    }
    return output;
}
