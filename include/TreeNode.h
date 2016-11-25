#ifndef TREENODE_H_
#define TREENODE_H_

#include "LLVM.h"
#include "SymbolTable.h"
#include "Data.h"
#include <string>
#include <vector>

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
            FLOAT,
            FUNCTION,
            INTEGER,
            PRINT_FUNCTION,
            STRING,
            LOOP,
            TOC_FUNCTION,
            VARIABLE,
            VARIABLE_DECLARATION,
            TYPE_CASTING,
            UNARY_OPERATION,
            UNKNOWN
        };

        TreeNode(Data::Type type);
        virtual ~TreeNode();
        virtual TreeNode::ClassType classType() const = 0;
        virtual llvm::Value* generateCode() = 0;
        virtual std::string printInOrder() const = 0;
        void setType(Data::Type type);
        void setSymbolTable(SymbolTable table);
        Data::Type dataType() const;

    protected:
        Data::Type type;
        SymbolTable symbolTable;
};

#endif
