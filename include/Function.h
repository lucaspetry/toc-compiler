#ifndef FUNCTION_H_
#define FUNCTION_H_

#include <string>
#include "TreeNode.h"
#include "CodeBlock.h"

class Function : public TreeNode {

    public:
        Function(std::string id, CodeBlock* params, CodeBlock* body);
        virtual ~Function();
        TreeNode::ClassType classType() const;
        std::string printInOrder() const;
        void generateCode() const;
        
    private:
      std::string id;
      CodeBlock* params;
      CodeBlock* body;

};

#endif
