#ifndef ARRAY_H_
#define ARRAY_H_

#include <string>
#include "TreeNode.h"

/**
  Class Array 
**/

class Array : public TreeNode {

    public:
        Array(std::string id, Data::Type type, TreeNode* size, std::vector<TreeNode*> *values = NULL);
        virtual ~Array();
        TreeNode::ClassType classType() const;
        std::string printInOrder() const;
        void setType(Data::Type type);
        llvm::Value* generateCode();

    private:
      std::string id;
      Data::Type type;
      TreeNode* size;
      std::vector<TreeNode*> *values;
};
#endif
