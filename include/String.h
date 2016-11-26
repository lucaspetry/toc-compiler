#ifndef STRING_H_
#define STRING_H_

#include "TreeNode.h"
#include <ctype.h>
#include <string>

/**
 * Valor textual
 */
class String : public TreeNode {

    public:
        String(std::string value);
        virtual ~String();
        TreeNode::ClassType classType() const;
        std::string printInOrder() const;
        llvm::Value* generateCode();
        void setBody(CodeBlock* codeBlock);
        std::string getValue();
        bool isBoolean();
        bool isNumber();

    private:
        std::string value;

};

#endif
