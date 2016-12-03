#ifndef CODEBLOCK_H_
#define CODEBLOCK_H_

#include "TreeNode.h"
#include <string>

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
        std::string printInLine() const;
        std::string printIndentation() const;
        int numberOfLines() const;
        TreeNode* getLine(int lineNumber);
        void insertLineFront(TreeNode* line);
        void insertLineBack(TreeNode* line);
        void setBody(CodeBlock* codeBlock);
        llvm::Value* generateCode();

    private:
        std::vector<TreeNode*> lines;
        int indentation;

};

#endif
