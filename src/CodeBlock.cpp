#include "CodeBlock.h"

CodeBlock::CodeBlock(int indentation) : TreeNode(Data::UNKNOWN) {
  this->indentation = indentation;
}
CodeBlock::CodeBlock() : TreeNode(Data::UNKNOWN){
}

CodeBlock::~CodeBlock() {
}

TreeNode::ClassType CodeBlock::classType() const {
    return TreeNode::CODE_BLOCK;
}

std::string CodeBlock::printInOrder() const {
    std::string output = "";
    printIndentation();
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

void CodeBlock::insertLine(TreeNode* line) {
    this->lines.insert(this->lines.begin(), line);
}

llvm::Value* CodeBlock::generateCode() {
    for (TreeNode* line: lines) {
        line->generateCode();
    }

    return NULL;
}

std::string CodeBlock::printIndentation() const {
  std::string output = "";
  for(int a = 0; a <= this->indentation; a++){
    output += "  ";
  }
  return output;
}
