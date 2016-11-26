#ifndef VARIABLE_H_
#define VARIABLE_H_

#include <string>
#include "TreeNode.h"
#include "SymbolTable.h"

/**
 * Variável
 */
class Variable : public TreeNode {

    public:
        Variable(std::string id, Data::Type type);
        virtual ~Variable();
        TreeNode::ClassType classType() const;
        std::string getId() const;
        std::string printInOrder() const;
        llvm::Value* generateCode();
        void setBody(CodeBlock* codeBlock);

    private:
        std::string id;
};

#endif
