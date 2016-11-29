#include "Function.h"

Function::Function(std::string id, CodeBlock* params, CodeBlock* body, TreeNode* ret) : TreeNode(Data::UNKNOWN) {
    this->id = id;
    this->params = params;
    this->body = body;
    this->ret = ret;
}

Function::~Function() {
}

TreeNode::ClassType Function::classType() const {
    return TreeNode::FUNCTION;
}

std::string Function::printInOrder() const {
    std::string output = Data::toString(this->dataType());
    output += " " + id + "(";

    // Imprime os parâmetros
    if(this->params != NULL)
        output += this->params->printInOrder();

    output += ")\n";

    // Imprime o corpo
    if(this->body != NULL)
        output += this->body->printInOrder();

    // Imprime o retorno
    if(this->ret != NULL)
        output += "ret " + this->ret->printInOrder();

    return output;
}

void Function::setBody(CodeBlock* codeBlock) {
    this->body = codeBlock;
}
