#include <string>
#include "TreeNode.h"

class VariableDeclaration : public TreeNode {

    public:
        VariableDeclaration(Data::Type type, TreeNode* next);
        virtual ~VariableDeclaration();
        TreeNode::ClassType classType() const;
        std::string printInOrder() const;
        std::string typeToString(Data::Type type) const;
        void generateCode() const;

    private:
        TreeNode* next;

};
