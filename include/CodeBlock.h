#ifndef CODEBLOCK_H_
#define CODEBLOCK_H_

#include <string>
#include "TreeNode.h"
#include "SemanticAnalyzer.h"

class CodeBlock : public TreeNode {

    public:
        CodeBlock(int indentation);
        CodeBlock();
        virtual ~CodeBlock();
        TreeNode::ClassType classType() const;
        std::string printInOrder() const;
        std::string printIndentation() const;
        int numberOfLines() const;
        void insertLine(TreeNode* line);
        llvm::Value* generateCode();

    private:
        std::vector<TreeNode*> lines;
        int indentation;

};

#endif
