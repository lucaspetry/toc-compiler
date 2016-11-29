#ifndef TREENODE_H_
#define TREENODE_H_

#include "LLVM.h"
#include "SymbolTable.h"
#include "Data.h"
#include <string>
#include <vector>

class CodeBlock;
class SemanticAnalyzer;
class SyntaxTree;

/**
 * Nodo da árvore sintática
 */
class TreeNode {

    friend class BinaryOperation;
    friend class SymbolTable;

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
            INTEGER,
            LOOP,
            PRINT_FUNCTION,
            STRING,
            TOC_FUNCTION,
            TYPE_CASTING,
            UNARY_OPERATION,
            VARIABLE,
            VARIABLE_DECLARATION,
            UNKNOWN
        };

        TreeNode(Data::Type type);
        virtual ~TreeNode();
        virtual TreeNode::ClassType classType() const = 0;
        virtual std::string printInOrder() const = 0;
        virtual void setBody(CodeBlock* codeBlock) = 0;
        void setType(Data::Type type);
        void setSymbolTable(SymbolTable& table);
        Data::Type dataType() const;

        virtual llvm::Value* generateCode() = 0;

    protected:
        Data::Type type;
        SymbolTable symbolTable;
};

#endif
