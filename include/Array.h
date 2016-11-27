#ifndef ARRAY_H_
#define ARRAY_H_

#include "TreeNode.h"
#include <string>

/**
 * Array
 */
class Array : public TreeNode {

    public:
        Array(std::string id, Data::Type type, TreeNode* size, std::vector<TreeNode*> *values = NULL);
        virtual ~Array();
        TreeNode::ClassType classType() const;
        std::string printInOrder() const;
        void setType(Data::Type type);
        std::vector<TreeNode*>* getValues();
        void setBody(CodeBlock* codeBlock);
        llvm::Value* generateCode();
        std::string toLLVMString();

    private:
      std::string id;
      Data::Type type;
      TreeNode* size;
      std::vector<TreeNode*> *values;
};
#endif
