#include "TypeCasting.h"

TypeCasting::TypeCasting(Data::Type type, TreeNode* next) : TreeNode(type) {
    this->type = type;
    this->next = next;
}

TypeCasting::~TypeCasting() {
}

TreeNode::ClassType TypeCasting::classType() const {
    return TreeNode::TYPE_CASTING;
}

std::string TypeCasting::printInOrder() const {
  std::string output = "(" + Data::toString(this->type) + ") ";
  if(next != NULL){
    output+= next->printInOrder();
  }
  return output;
}

void TypeCasting::setBody(CodeBlock* codeBlock) {
}
