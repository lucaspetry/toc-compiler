#include "Function.h"

Function::Function(std::string id, Data::Type type, CodeBlock* params, TreeNode* body) : TreeNode(Data::UNKNOWN) {
    this->id = id;
    this->params = params;
    this->body = body;
    this->type = type;
}

Function::~Function() {

}

TreeNode::ClassType Function::classType() const {
    return TreeNode::FUNCTION;
}

std::string Function::printInOrder() const {
    std::string output;

    output += toString(type);
    output += " ";
    output += this->id;
    output += "(";

    // print the params
    if(this->params != NULL)
      output += this->params->printInOrder();

    output = Data::toString(type) + " " + id + "(";

    // Imprime os parâmetros
    if(this->params != NULL)
        output += this->params->printInOrder();

    output += ")";
    output += "\n";

    // print the Function body
    if(this->body != NULL){
      output += this->body->printInOrder();
    }

    return output;
}

llvm::Value* Function::generateCode(llvm::IRBuilder<>* builder) {
    return NULL;//TODO;
}
