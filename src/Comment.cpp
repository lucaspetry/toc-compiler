#include "Comment.h"

Comment::Comment(std::string comment) : TreeNode(Data::STR) {
    this->comment = comment;
}

Comment::~Comment() {
}

TreeNode::ClassType Comment::classType() const {
    return TreeNode::COMMENT;
}

std::string Comment::printInOrder() const {
    return this->comment;
}

void Comment::generateCode(llvm::IRBuilder<>* builder) const {
  //TODO;
}
