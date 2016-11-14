#ifndef FLOAT_H_
#define FLOAT_H_

#include "TreeNode.h"

/**
  Class Float 
**/

class Float : public TreeNode {

    public:
        Float(float value);
        virtual ~Float();
        TreeNode::ClassType classType() const;
        std::string printInOrder() const;
        llvm::Value* generateCode();

    private:
        float value;

};

#endif
