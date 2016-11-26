#ifndef FLOAT_H_
#define FLOAT_H_

#include "TreeNode.h"

/**
 * Valor de ponto flutuante
 */
class Float : public TreeNode {

    public:
        Float(float value);
        virtual ~Float();
        TreeNode::ClassType classType() const;
        std::string printInOrder() const;
        llvm::Value* generateCode();
        void setBody(CodeBlock* codeBlock);

    private:
        float value;

};

#endif
