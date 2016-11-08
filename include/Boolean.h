#include "TreeNode.h"

class Boolean : public TreeNode {

    public:
        Boolean(bool value);
        virtual ~Boolean();
        TreeNode::ClassType classType() const;
        std::string printInOrder() const;
        virtual void generateCode() const;

    private:
        bool value;

};
