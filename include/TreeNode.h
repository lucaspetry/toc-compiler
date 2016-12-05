#ifndef TREENODE_H_
#define TREENODE_H_

#include "LLVM.h"
#include "SymbolTable.h"
#include "Data.h"
#include <string>
#include <iostream>
#include <vector>

class CodeBlock;
class SemanticAnalyzer;
class SyntaxTree;

/**
 * Nodo da árvore sintática
 */
class TreeNode {

    friend class BinaryOperation;
    friend class Conditional;
    friend class Function;
    friend class SymbolTable;
    friend class SemanticAnalyzer;

    public:
        /**
         * Tipos de nodos
         */
        enum ClassType {
            ARRAY,
            BINARY_OPERATION,
            BOOLEAN,
            CODE_BLOCK,
            COMMENT,
            CONDITIONAL,
            FLOAT,
            FUNCTION,
            FUNCTION_CALL,
            INTEGER,
            LOOP,
            OBJECT,
            PRINT_FUNCTION,
            STRING,
            TOC_FUNCTION,
            TYPE_CASTING,
            UNARY_OPERATION,
            VARIABLE_DECLARATION,
            VARIABLE,
            UNKNOWN
        };

        TreeNode(Data::Type type);
        virtual ~TreeNode();
        virtual TreeNode::ClassType classType() const = 0;
        virtual std::string printInOrder() const = 0;
        virtual void setBody(CodeBlock* codeBlock) = 0;
        void setType(Data::Type type);
        std::string toString(TreeNode::ClassType tipo);
        void setSymbolTable(SymbolTable& table);
        Data::Type dataType() const;

        virtual llvm::Value* generateCode() = 0;

    protected:
        Data::Type type;
        SymbolTable symbolTable;
};

#endif
