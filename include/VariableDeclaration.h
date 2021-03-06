#ifndef VARIABLEDECLARATION_H_
#define VARIABLEDECLARATION_H_

#include "TreeNode.h"

/**
 * Declaração de variável
 */
class VariableDeclaration : public TreeNode {

    public:
        VariableDeclaration(Data::Type type, TreeNode* next);
        virtual ~VariableDeclaration();
        TreeNode::ClassType classType() const;
        std::string printInOrder() const;
        llvm::Value* generateCode();
        void setEncapsulation(int n);
        TreeNode* getNext();
        void setBody(CodeBlock* codeBlock);

    private:
        TreeNode* next;
        int encapsulation;

};

#endif
