#ifndef INTEGER_H_
#define INTEGER_H_

#include <string>
#include "TreeNode.h"

/**
 * Valor inteiro
 */
class Integer : public TreeNode {

    public:
        Integer(int value);
        virtual ~Integer();
        TreeNode::ClassType classType() const;
        std::string printInOrder() const;
        int getValue();
        llvm::Value* generateCode();
        void setBody(CodeBlock* codeBlock);

    private:
        int value;

};

#endif
