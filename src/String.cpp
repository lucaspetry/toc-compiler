#include "String.h"

String::String(std::string value) : TreeNode(Data::STR) {
    this->value = value;
}

String::~String() {
}

TreeNode::ClassType String::classType() const {
    return TreeNode::STRING;
}

std::string String::printInOrder() const {
    std::string valuePrint = this->value;

    while(valuePrint.find("\n") != std::string::npos)
        valuePrint.replace(valuePrint.find("\n"), 1, "\\n");

    return valuePrint;
}

void String::setBody(CodeBlock* codeBlock) {
}

std::string String::getValue() {
    std::string value = this->value;

    if(value.at(0) == '\"')
        value = value.substr(1, value.size());

    if(value.at(value.size()-1) == '\"')
        value = value.substr(0, value.size()-1);

    while(value.find("\\n") != std::string::npos) {
        value.replace(value.find("\\n"), 2, "\n");
    }

    return value;
}

bool String::isBoolean(){
  if(this->value == "true" || this->value == "false")
    return true;
  return false;
}

bool String::isNumber(){
  if (std::all_of(this->value.begin(), this->value.end(), ::isdigit))
    return true;
  return false;
}
