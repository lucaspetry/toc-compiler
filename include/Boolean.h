#ifndef BOOLEAN_H_
#define BOOLEAN_H_

#include "TreeNode.h"

/**
  Class Boolean 
**/

class Boolean : public TreeNode {

    public:
        Boolean(bool value);
        virtual ~Boolean();
        TreeNode::ClassType classType() const;
        std::string printInOrder() const;
        llvm::Value* generateCode();

    private:
        bool value;

};

#endif
