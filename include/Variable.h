#ifndef VARIABLE_H_
#define VARIABLE_H_

#include "TreeNode.h"
#include "SymbolTable.h"
#include <string>

/**
 * Variável
 */
class Variable : public TreeNode {

    friend class SemanticAnalyzer;
    public:
        Variable(std::string id, Data::Type type);
        virtual ~Variable();
        TreeNode::ClassType classType() const;
        std::string getId() const;
        std::string printInOrder() const;
        void setObj(std::string);
        llvm::Value* generateCode();
        void setBody(CodeBlock* codeBlock);

    private:
        std::string id;
        std::string obj;
};

#endif
