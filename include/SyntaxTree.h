#ifndef SYNTAXTREE_H_
#define SYNTAXTREE_H_

#include "TreeNode.h"
#include "LLVM.h"
#include <iostream>
#include <string>
#include <vector>

/**
 * Árvore sintática abstrata.
 */
class SyntaxTree {

    public:
        SyntaxTree();
        virtual ~SyntaxTree();
        void print();
        void insertLine(TreeNode* line);
        void generateCode();

    private:
        std::vector<TreeNode*> lines;

};

#endif
