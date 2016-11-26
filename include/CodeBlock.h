#ifndef CODEBLOCK_H_
#define CODEBLOCK_H_

#include <string>
#include "TreeNode.h"

/**
 * Bloco de código
 */
class CodeBlock : public TreeNode {

    friend class SyntaxTree;

    public:
        CodeBlock(int indentation);
        CodeBlock();
        virtual ~CodeBlock();
        TreeNode::ClassType classType() const;
        std::string printInOrder() const;
        std::string printIndentation() const;
        int numberOfLines() const;
        TreeNode* getLine(int lineNumber);
        void insertLineFront(TreeNode* line);
        void insertLineBack(TreeNode* line);
        llvm::Value* generateCode();
        void setBody(CodeBlock* codeBlock);

    private:
        std::vector<TreeNode*> lines;
        int indentation;

};

#endif
