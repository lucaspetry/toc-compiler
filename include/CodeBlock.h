#ifndef CODEBLOCK_H_
#define CODEBLOCK_H_

#include <string>
#include "TreeNode.h"

class CodeBlock : public TreeNode {

    public:
        CodeBlock();
        virtual ~CodeBlock();
        TreeNode::ClassType classType() const;
        std::string printInOrder() const;
        int numberOfLines() const;
        void insertLine(TreeNode* line);

    private:
        std::vector<TreeNode*> lines;

};

#endif
