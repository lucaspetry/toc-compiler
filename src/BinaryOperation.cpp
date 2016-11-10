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

void BinaryOperation::generateCode(llvm::IRBuilder<>* builder) {
    if(code != NULL)
        return;
    
    if (this->operation == BinaryOperation::ASSIGN) {
        Variable* lvar = dynamic_cast<Variable *>(left); // TODO pode ser VariableDeclaration
        right->generateCode(builder);
        code = builder->CreateAdd(right->code, IR::Zero, lvar->getId().c_str());
        //symbolTable.updateVariable(lvar->id, code); /*Gives the new code and value to the variable in the symbol table.*/
    } else {
        left->generateCode(builder);
        right->generateCode(builder);
        switch(this->operation){
//            case plus:
//                code = builder->CreateAdd(left->code, right->code, "addtmp");
//                break;
//            case times:
//                code = builder->CreateMul(left->code, right->code, "multmp");
//                break;
            default:
                code = NULL; //Not the greatest error capture, but okay for the example
                break;
        }
    }

}
