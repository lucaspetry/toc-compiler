#include "Conditional.h"
#include <iostream>


Conditional::Conditional(TreeNode* condition, CodeBlock* thenCode, CodeBlock* elseCode) : TreeNode(Data::UNKNOWN) {
    this->condition = condition;
    this->thenCode = thenCode;
    this->elseCode = elseCode;
    this->settingElse = false;
}

Conditional::~Conditional() {
}

TreeNode::ClassType Conditional::classType() const {
    return TreeNode::CONDITIONAL;
}

std::string Conditional::printInOrder() const {
    std::string output = "if("+ condition->printInOrder() + ")\n";

    if(this->thenCode != NULL)
        output += this->thenCode->printInOrder();

    if(this->elseCode != NULL) {
        std::string indent = this->elseCode->printIndentation();
        output += "\n" + indent.substr(2, indent.length()) + "else\n";
        output += this->elseCode->printInOrder();
    }

    return output;
}

bool Conditional::hasElse() const {
    return this->elseCode != NULL;
}

void Conditional::setElse(bool settingElse) {
    this->settingElse = settingElse;
}

void Conditional::setBody(CodeBlock* codeBlock) {
    if(!this->settingElse) {
        this->thenCode = codeBlock;
    } else {
        this->elseCode = codeBlock;
    }
}
