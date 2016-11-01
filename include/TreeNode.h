#ifndef TREENODE_H_
#define TREENODE_H_

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
        VOID = 0
    };
}


class TreeNode {

    public:
        enum ClassType {
            UNKNOWN
        };

        TreeNode(Data::Type type);
        virtual ~TreeNode();
        Data::Type dataType() const;
        void setType(Data::Type type);
        virtual TreeNode::ClassType classType() const = 0;
        virtual std::string printInOrder() = 0;

    protected:
        Data::Type type;

};

#endif
