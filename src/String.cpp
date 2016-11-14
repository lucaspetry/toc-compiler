#include "String.h"

String::String(std::string value) : TreeNode(Data::STR) {
    if(value.at(0) == '\"')
        this->value = value.substr(1, value.size());
    
    if(this->value.at(this->value.size()-1) == '\"')
        this->value = this->value.substr(0, this->value.size()-1);
    
    while(this->value.find("\\n") != std::string::npos) {
        this->value.replace(this->value.find("\\n"), 2, "\n");
    }
}

String::~String() {    
}

TreeNode::ClassType String::classType() const {
    return TreeNode::STRING;
}

std::string String::printInOrder() const {
    return this->value;
}

std::string String::getValue() {
    return this->value;
}

/**
 * llvm::Value* Integer::generateCode() no CodeGenerator.cpp
 */
