#ifndef COMMENT_H_
#define COMMENT_H_

#include <string>
#include "TreeNode.h"

class Comment : public TreeNode {

    public:
        Comment(std::string comment);
        virtual ~Comment();
        TreeNode::ClassType classType() const;
        std::string printInOrder() const;
        void generateCode() const;

    private:
      std::string comment;

};

#endif