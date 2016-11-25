#include "Conditional.h"

Conditional::Conditional(TreeNode* condition, CodeBlock* bodyIf, CodeBlock* bodyElse) : TreeNode(Data::UNKNOWN) {
    this->condition = condition;
    this->bodyIf = bodyIf;
    this->bodyElse = bodyElse;
}

Conditional::Conditional(TreeNode* condition, CodeBlock* bodyIf) : TreeNode(Data::UNKNOWN) {
    this->condition = condition;
    this->bodyIf = bodyIf;
}

Conditional::~Conditional() {
}

TreeNode::ClassType Conditional::classType() const {
    return TreeNode::CONDITIONAL;
}

std::string Conditional::printInOrder() const {
    return NULL;
}
