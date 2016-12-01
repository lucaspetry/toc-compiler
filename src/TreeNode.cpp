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
std::string TreeNode::toString(TreeNode::ClassType tipo) {
  switch (tipo) {
    case ARRAY: return "array";
    case BINARY_OPERATION: return "binary operation" ;
    case BOOLEAN: return "boolean" ;
    case CODE_BLOCK: return "code block" ;
    case COMMENT: return "comment" ;
    case CONDITIONAL: return "conditional" ;
    case FLOAT: return "float" ;
    case FUNCTION: return "function" ;
    case INTEGER: return "integer" ;
    case LOOP: return "loop" ;
    case PRINT_FUNCTION: return "print function" ;
    case STRING: return "string" ;
    case TOC_FUNCTION: return "toc funcion" ;
    case TYPE_CASTING: return "type cassting" ;
    case UNARY_OPERATION: return "unary operation" ;
    case VARIABLE_DECLARATION: return "variable declaration" ;
    case OBJECT: return "object" ;
    case VARIABLE: return "variable" ;
  }
}
