#ifndef FUNCTION_H_
#define FUNCTION_H_

#include <string>
#include "TreeNode.h"
#include "CodeBlock.h"

class Function : public TreeNode {

    public:
        Function(std::string id, Data::Type type, CodeBlock* params, TreeNode* body);
        virtual ~Function();
        TreeNode::ClassType classType() const;
        std::string printInOrder() const;

    private:
      std::string id;
      CodeBlock* params;
      TreeNode* body;
      Data::Type type;

};

#endif
