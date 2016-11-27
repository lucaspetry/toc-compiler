#ifndef TYPECASTING_H_
#define TYPECASTING_H_

#include "TreeNode.h"

/**
 * Conversão de tipos
 */
class TypeCasting : public TreeNode {

    public:
        TypeCasting(Data::Type type, TreeNode* next);
        virtual ~TypeCasting();
        TreeNode::ClassType classType() const;
        std::string printInOrder() const;
        llvm::Value* generateCode();
        std::string toLLVMString();
        void setBody(CodeBlock* codeBlock);

    private:
        TreeNode* next;
        Data::Type type;

};

#endif
