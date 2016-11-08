#include "TreeNode.h"

class Integer : public TreeNode {

    public:
        Integer(int value);
        virtual ~Integer();
        TreeNode::ClassType classType() const;
        std::string printInOrder() const;
        virtual void generateCode() const;
        int getValue();
    private:
        int value;

};
