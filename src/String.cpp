#include "String.h"

String::String(std::string value) : TreeNode(Data::STR) {
    this->value = value;

    this->valuePrint = this->value;

    if(this->valuePrint.at(0) == '\"')
        this->valuePrint = this->valuePrint.substr(1, this->valuePrint.size());

    if(this->valuePrint.at(this->valuePrint.size()-1) == '\"')
        this->valuePrint = this->valuePrint.substr(0, this->valuePrint.size()-1);

    while(this->valuePrint.find("\\n") != std::string::npos) {
        this->valuePrint.replace(this->valuePrint.find("\\n"), 2, "\n");
    }
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
    return this->value;
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
