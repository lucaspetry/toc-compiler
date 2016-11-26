#include "Comment.h"

Comment::Comment(std::string comment) : TreeNode(Data::STR) {
    this->comment = comment;

    if(this->comment.at(0) == '#')
        this->comment = this->comment.substr(1, this->comment.size());
}

Comment::~Comment() {
}

TreeNode::ClassType Comment::classType() const {
    return TreeNode::COMMENT;
}

std::string Comment::printInOrder() const {
    return "#" + this->comment;
}

std::string Comment::getValue() const {
    return this->comment;
}

void Comment::setBody(CodeBlock* codeBlock) {
}
