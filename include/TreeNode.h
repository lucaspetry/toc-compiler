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
}


class TreeNode {

    public:
        enum ClassType {
            CODE_BLOCK,
            COMMENT,
            FUNCTION,
            UNKNOWN
        };

        TreeNode(Data::Type type);
        virtual ~TreeNode();
        Data::Type dataType() const;
        void setType(Data::Type type);
        virtual TreeNode::ClassType classType() const = 0;
        virtual std::string printInOrder() const = 0;
        virtual void generateCode(llvm::IRBuilder<>* builder) const = 0;
        //llvm:Value* code;

    protected:
        Data::Type type;

};

#endif
