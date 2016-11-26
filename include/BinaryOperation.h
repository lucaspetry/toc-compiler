#ifndef BINARYOPERATION_H_
#define BINARYOPERATION_H_

#include "TreeNode.h"
#include "Variable.h"

/**
 * Operação binária
 */
class BinaryOperation : public TreeNode {

  friend class SemanticAnalyzer;

    public:
        enum Type {
            ASSIGN,
            DIVIDE,
            MINUS,
            PLUS,
            TIMES,
            COMMA,
            MULT_ATT,
            GREATER,
            GREATER_E,
            LOWER,
            LOWER_E,
            EQUAL,
            DIFF,
            NOT,
            AND,
            OR,
            UNKNOWN
        };

        BinaryOperation(TreeNode* left, Type operation, TreeNode* right);
        virtual ~BinaryOperation();
        TreeNode::ClassType classType() const;
        std::string printInOrder() const;
        std::string operationToString(Type operation) const;
        void setLeft(TreeNode* left);
        llvm::Value* generateCode();
        void setBody(CodeBlock* codeBlock);

    private:
        Type operation;
        TreeNode* left;
        TreeNode* right;

};

#endif
