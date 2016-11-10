#ifndef TREENODE_H_
#define TREENODE_H_

#include "LLVM.h"
#include <string>
#include <vector>

class SemanticAnalyzer;
class SyntaxTree;
class TreeNode;

/**
 * Namespace de dados.
 */
namespace Data {
    enum Type {
        UNKNOWN = -1,
        BOO = 1,
        FLT = 2,
        INT = 3,
        STR = 4,
        VOID = 5
    };
    
    std::string toString(Data::Type type);
}

class TreeNode {
    
    friend class BinaryOperation;

    public:
        enum ClassType {
            ARRAY,
            BINARY_OPERATION,
            CODE_BLOCK,
            COMMENT,
            FUNCTION,
            VARIABLE,
            VARIABLE_DECLARATION,
            BOOLEAN,
            INTEGER,
            FLOAT,
            UNKNOWN
        };

        TreeNode(Data::Type type);
        virtual ~TreeNode();
        Data::Type dataType() const;
        void setType(Data::Type type);

        virtual TreeNode::ClassType classType() const = 0;
        virtual llvm::Value* generateCode(llvm::IRBuilder<>* builder) = 0;
        virtual std::string printInOrder() const = 0;

    protected:
        Data::Type type;

};

#endif
