#include "BinaryOperation.h"

BinaryOperation::BinaryOperation(TreeNode* left, BinaryOperation::Type operation, TreeNode* right) : TreeNode(Data::UNKNOWN) {
    this->left = left;
    this->operation = operation;
    this->right = right;

    // setando o tipo da BinaryOperation com o tipo mais forte
    if(left->dataType() > right->dataType())
      setType(left->dataType());
    else
      setType(right->dataType());
}

BinaryOperation::~BinaryOperation() {
}

TreeNode::ClassType BinaryOperation::classType() const {
    return TreeNode::BINARY_OPERATION;
}

std::string BinaryOperation::printInOrder() const {
  std::string output = "";
  if(operation == MULT_ATT)
    output += "{";

  output += left->printInOrder();

  if(operation != COMMA)
      output += " ";

  output += operationToString(operation) + " ";

  output += right->printInOrder();

  if(operation == MULT_ATT)
    output += "}";

  return output;
}

std::string BinaryOperation::operationToString(BinaryOperation::Type operation) const {
    switch(operation) {
        case COMMA:
            return ",";
        case ASSIGN:
            return "=";
        case MULT_ATT:
            return ",";
        case PLUS:
            return "+";
        case TIMES:
            return "*";
        case MINUS:
            return "-";
        case DIVIDE:
            return "/";
        default:
            return "unknown";
    }
}

void BinaryOperation::setLeft(TreeNode* left){
  this->left = left;
}
