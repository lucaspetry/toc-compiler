#ifndef COMMENT_H_
#define COMMENT_H_

#include "TreeNode.h"
#include <string>

/**
 * Comentário
 */
class Comment : public TreeNode {

    public:
        Comment(std::string comment);
        virtual ~Comment();
        TreeNode::ClassType classType() const;
        std::string printInOrder() const;
        std::string getValue() const;
        void setBody(CodeBlock* codeBlock);
        llvm::Value* generateCode();

    private:
      std::string comment;

};

#endif
