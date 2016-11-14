#ifndef STRING_H_
#define STRING_H_

#include "TreeNode.h"
#include <string>

/**
  Class String
**/

class String : public TreeNode {

    public:
        String(std::string value);
        virtual ~String();
        TreeNode::ClassType classType() const;
        std::string printInOrder() const;
        llvm::Value* generateCode();
        std::string getValue();

    private:
        std::string value;

};

#endif
