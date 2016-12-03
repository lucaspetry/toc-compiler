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
            MULT_ASSIGN,
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
        void setBody(CodeBlock* codeBlock);
        llvm::Value* generateCode();

    private:
        Type operation;
        TreeNode* left;
        TreeNode* right;

};

#endif
