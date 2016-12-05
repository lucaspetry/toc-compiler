#include "FunctionCall.h"

FunctionCall::FunctionCall(std::string id, CodeBlock* params) : TreeNode(Data::UNKNOWN) {
    this->id = id;
    this->params = params;
    this->classe = "";
    this->obj = "";
}

FunctionCall::~FunctionCall() {
}

TreeNode::ClassType FunctionCall::classType() const {
    return TreeNode::FUNCTION_CALL;
}

std::string FunctionCall::printInOrder() const {
    std::string output = "";
    if(this->obj != "")
      output+=this->obj+".";

    output += this->id;
    if(this->classe != "")
      output+= " " + this->classe;

    output+="(";
    // Imprime os parâmetros
    if(this->params != NULL) {
        for(int i = 0; i < params->numberOfLines(); i++)
            output += this->params->getLine(i)->printInOrder() + ", ";
        output = output.substr(0, output.size() - 2);
      }

    output += ")";
    return output;
}

void FunctionCall::setBody(CodeBlock* codeBlock) {
}

std::string FunctionCall::getId() const{
    return this->id;
}
void FunctionCall::setClass(std::string classe) {
    this->classe = classe;
}

void FunctionCall::setObj(std::string obj) {
    this->obj = obj;
}
