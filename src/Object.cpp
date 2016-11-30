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
    if(params != NULL)
      output+= params->printInOrder();
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
