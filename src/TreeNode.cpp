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

void TreeNode::setSymbolTable(SymbolTable& table) {
    this->symbolTable = table;
}
