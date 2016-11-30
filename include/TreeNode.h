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
    friend class SymbolTable;

    public:
        /**
         * Tipos de nodos
         */
        enum ClassType {
            ARRAY = 1,
            BINARY_OPERATION = 2,
            BOOLEAN = 3,
            CODE_BLOCK = 4,
            COMMENT = 5,
            CONDITIONAL = 6,
            FLOAT = 7,
            FUNCTION = 8,
            INTEGER = 9,
            LOOP = 10,
            PRINT_FUNCTION = 11,
            STRING = 12,
            TOC_FUNCTION = 13,
            TYPE_CASTING = 14,
            UNARY_OPERATION = 16,
            VARIABLE_DECLARATION = 15,
            OBJECT = 17,
            VARIABLE = 18,
            UNKNOWN = 19
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
