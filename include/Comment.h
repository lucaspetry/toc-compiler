#ifndef COMMENT_H_
#define COMMENT_H_

#include <string>
#include "TreeNode.h"

/**
 * Comentário
 */
class Comment : public TreeNode {

    public:
        Comment(std::string comment);
        virtual ~Comment();
        TreeNode::ClassType classType() const;
        std::string printInOrder() const;
        llvm::Value* generateCode();
        std::string getValue() const;
        void setBody(CodeBlock* codeBlock);

    private:
      std::string comment;

};

#endif
