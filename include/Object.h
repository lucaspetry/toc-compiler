#ifndef OBJECT_H_
#define OBJECT_H_

#include "TreeNode.h"
#include "CodeBlock.h"
#include <string>

/**
 * Objeto
 */
class Object : public TreeNode {

    public:
        Object(std::string id, CodeBlock* params, CodeBlock* body);
        virtual ~Object();
        TreeNode::ClassType classType() const;
        std::string printInOrder() const;
        void setBody(CodeBlock* codeBlock);
        llvm::Value* generateCode();

    protected:
        std::string id;
        CodeBlock* params;
        CodeBlock* body;

};

#endif
