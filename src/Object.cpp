#include "Object.h"
Object::Object(std::string id, CodeBlock* params, CodeBlock* body) : TreeNode(Data::UNKNOWN) {
    this->id = id;
    this->params = params;
    this->body = body;
}

Object::~Object() {
}

TreeNode::ClassType Object::classType() const {
    return TreeNode::OBJECT;
}

std::string Object::printInOrder() const {
    std::string output = "";
    output+= "obj "+ id + "(";

    // Imprime os parâmetros
    if(this->params != NULL) {
        for(int i = 0; i < params->numberOfLines(); i++)
            output += this->params->getLine(i)->printInOrder() + ", ";
        output = output.substr(0, output.size() - 2);
    }

    output+=")";
    output+="\n";
    if(this->body != NULL){
      output+=this->body->printInOrder();
    }
    return output;
}

void Object::setBody(CodeBlock* codeBlock) {
    this->body = codeBlock;
}

std::string Object::getId(){
  return this->id;
}
