#include "BinaryOperation.h"
#include "CodeBlock.h"

BinaryOperation::BinaryOperation(TreeNode* left, BinaryOperation::Type operation, TreeNode* right) : TreeNode(Data::UNKNOWN) {
    this->left = left;
    this->operation = operation;
    this->right = right;

    // setando o tipo da BinaryOperation com o tipo mais forte
    if(left->dataType() > right->dataType())
      setType(left->dataType());
    else
      setType(right->dataType());

    if(operation == BinaryOperation::ASSIGN)
      setType(left->dataType());
}

BinaryOperation::~BinaryOperation() {
}

TreeNode::ClassType BinaryOperation::classType() const {
    return TreeNode::BINARY_OPERATION;
}

std::string BinaryOperation::printInOrder() const {
    std::string output = "";

    output += left->printInOrder();
    if(operation != COMMA)
        output += " ";

    output += operationToString(operation) + " ";

    if(operation == MULT_ASSIGN) {
        output += "{";
        CodeBlock* block = (CodeBlock*) right;
        output += block->printInLine() + "}";
    } else {
        output += right->printInOrder();
    }

  return output;
}

void BinaryOperation::setBody(CodeBlock* codeBlock) {
}

std::string BinaryOperation::operationToString(BinaryOperation::Type operation) const {
    switch(operation) {
        case COMMA:
            return ",";
        case ASSIGN:
            return "=";
        case MULT_ASSIGN:
            return "=";
        case PLUS:
            return "+";
        case TIMES:
            return "*";
        case MINUS:
            return "-";
        case DIVIDE:
            return "/";
        case GREATER:
            return ">";
        case GREATER_E:
            return ">=";
        case LOWER:
            return "<";
        case LOWER_E:
            return "<=";
        case EQUAL:
            return "==";
        case DIFF:
            return "!=";
        case NOT:
            return "not";
        case AND:
            return "and";
        case OR:
            return "or";
        default:
            return "unknown";
    }
}

void BinaryOperation::setLeft(TreeNode* left){
  this->left = left;
}
