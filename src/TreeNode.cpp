#include "TreeNode.h"
#include "SymbolTable.h"

TreeNode::TreeNode(Data::Type type) {
    this->type = type;
}

TreeNode::~TreeNode() {
}

Data::Type TreeNode::dataType() const {
    return this->type;
}

void TreeNode::setType(Data::Type type) {
    this->type = type;
}

void TreeNode::setSymbolTable(SymbolTable table){
    this->symbolTable = table;
}

std::string TreeNode::toString(Data::Type type) const {
    switch(type) {
        case Data::UNKNOWN:
            return "unknown";
        case Data::BOO:
            return "boo ";
        case Data::FLT:
            return "flt ";
        case Data::INT:
            return "int ";
        case Data::STR:
            return "str ";
        case Data::VOID:
            return "void ";
    }
}
