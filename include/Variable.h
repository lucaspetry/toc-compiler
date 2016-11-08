#ifndef VARIABLE_H_
#define VARIABLE_H_

#include <string>
#include "TreeNode.h"

class Variable : public TreeNode {

    public:
        Variable(std::string id);
        virtual ~Variable();
        TreeNode::ClassType classType() const;
        std::string printInOrder() const;

    private:
      std::string id;

};

#endif
