#ifndef ARRAY_H_
#define ARRAY_H_

#include "TreeNode.h"
#include <string>

/**
 * Array
 */
class Array : public TreeNode {

    public:
        Array(std::string id, Data::Type type, TreeNode* size, TreeNode* values = NULL);
        virtual ~Array();
        TreeNode::ClassType classType() const;
        std::string printInOrder() const;
        TreeNode* getValues();
        void setBody(CodeBlock* codeBlock);
        void setEncapsulation(int value);
        TreeNode* getSize();
        llvm::Value* generateCode();

    private:
      std::string id;
      TreeNode* size;
      TreeNode* values;
      int encapsulation;
};
#endif
