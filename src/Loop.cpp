#include "Loop.h"

Loop::Loop(TreeNode* init, TreeNode* test, TreeNode* attribuition, TreeNode* body) : TreeNode(Data::UNKNOWN) {
    this->init = init;
    this->test = test;
    this->attribuition = attribuition;
    this->body = body;
}

Loop::~Loop() {

}

TreeNode::ClassType Loop::classType() const {
    return Loop::LOOP;
}

std::string Loop::printInOrder() const {
    std::string output = "";

    output += "for";
    output += "(";

    output += this->init->printInOrder();
    output += "; ";

    output += this->test->printInOrder();
    output += "; ";

    output += this->attribuition->printInOrder();
    output += ")";

    if(this->body != NULL)
      this->body->printInOrder();

    return output;
}

void Loop::setBody(CodeBlock* codeBlock) {
}
