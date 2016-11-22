#include "TypeCasting.h"

TypeCasting::TypeCasting(Data::Type left, TreeNode* next) : TreeNode(left) {
    this->left = left;
    this->next = next;
}

TypeCasting::~TypeCasting() {
}

TreeNode::ClassType TypeCasting::classType() const {
    return TreeNode::TYPE_CASTING;
}

std::string TypeCasting::printInOrder() const {
  std::string output = "(" + typeToString(this->left) + ") ";
  if(next != NULL){
    output+= next->printInOrder();
  }
  return output;
}

std::string TypeCasting::typeToString(Data::Type type) const{
    switch(type) {
        case Data::INT:
            return "int";
        case Data::BOO:
            return "boo";
        case Data::FLT:
            return "flt";
        default:
            return "unknown";
    }
}
