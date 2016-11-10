#include "BinaryOperation.h"

BinaryOperation::BinaryOperation(TreeNode* left, BinaryOperation::Type operation, TreeNode* right) : TreeNode(Data::UNKNOWN) {
    this->left = left;
    this->operation = operation;
    this->right = right;
}

BinaryOperation::~BinaryOperation() {
}

TreeNode::ClassType BinaryOperation::classType() const {
    return TreeNode::BINARY_OPERATION;
}

std::string BinaryOperation::printInOrder() const {
  std::string output = left->printInOrder();
  if(operation != COMMA)
      output += " ";

  output += operationToString(operation) + " ";
  return output + right->printInOrder();
}

std::string BinaryOperation::operationToString(BinaryOperation::Type operation) const {
    switch(operation) {
        case BinaryOperation::COMMA:
            return ",";
        case BinaryOperation::ASSIGN:
            return "=";
        default:
            return "unknown";
    }
}

llvm::Value* BinaryOperation::generateCode(llvm::IRBuilder<>* builder) {
    if (this->operation == BinaryOperation::ASSIGN) {
        Variable* lvar = dynamic_cast<Variable *>(left); // TODO pode ser VariableDeclaration
        return builder->CreateAdd(right->generateCode(builder), IR::Zero, lvar->getId().c_str());
        //symbolTable.updateVariable(lvar->id, code); /*Gives the new code and value to the variable in the symbol table.*/
    } else {
        left->generateCode(builder); // TODO
        right->generateCode(builder); // TODO
        switch(this->operation){
//            case plus:
//                code = builder->CreateAdd(left->code, right->code, "addtmp");
//                break;
//            case times:
//                code = builder->CreateMul(left->code, right->code, "multmp");
//                break;
            default:
                return NULL; //Not the greatest error capture, but okay for the example
                break;
        }
    }

}