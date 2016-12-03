#include "Variable.h"

Variable::Variable(std::string id, Data::Type type) : TreeNode(type) {
    this->id = id;
    this->obj = "";
}

Variable::~Variable() {
}

TreeNode::ClassType Variable::classType() const {
    return TreeNode::VARIABLE;
}

std::string Variable::printInOrder() const {
    std::string output = "";
    if(obj != "")
        output+= this->obj +".";

    return output+=this->id;
}

std::string Variable::getId() const {
    return id ;
}

void Variable::setBody(CodeBlock* codeBlock) {
}

void Variable::setObj(std::string obj){
  this->obj = obj;
}
