#ifndef FUNCTIONCALL_H_
#define FUNCTIONCALL_H_

#include "TreeNode.h"
#include "CodeBlock.h"
#include <string>

/**
 * Função
 */
class FunctionCall : public TreeNode {

    public:
        FunctionCall(std::string id, CodeBlock* params);
        virtual ~FunctionCall();
        TreeNode::ClassType classType() const;
        std::string printInOrder() const;
        std::string getId() const;
        void setClass(std::string classe) ;
        void setObj(std::string obj) ;
        void setBody(CodeBlock* codeBlock);
        llvm::Value* generateCode();

    protected:
        std::string id;
        std::string classe;
        std::string obj;
        CodeBlock* params;

};

#endif
