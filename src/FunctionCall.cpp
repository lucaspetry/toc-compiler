#include "FunctionCall.h"

FunctionCall::FunctionCall(std::string id, CodeBlock* params) : TreeNode(Data::UNKNOWN) {
    this->id = id;
    this->params = params;
}

FunctionCall::~FunctionCall() {
}

TreeNode::ClassType FunctionCall::classType() const {
    return TreeNode::FUNCTION_CALL;
}

std::string FunctionCall::printInOrder() const {
    std::string output = this->id + "(";

    // Imprime os parâmetros
    if(this->params != NULL)
        output += this->params->printInOrder();

    output += ")";
    return output;
}

void FunctionCall::setBody(CodeBlock* codeBlock) {
}

std::string FunctionCall::getId() const{
    return this->id;
}
