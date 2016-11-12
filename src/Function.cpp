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
    std::string output;
    output = Data::toString(this->dataType()) + " " + id + "(";

    // Imprime os parâmetros
    if(this->params != NULL)
        output += this->params->printInOrder();

    output += ")";
    output += "\n";

    // Imprime o corpo da função
    if(this->body != NULL) {
        output += this->body->printInOrder();
    }

    // Imprimir retorno

    return output;
}

/**
 * llvm::Value* Function::generateCode() no CodeGenerator.cpp
 */