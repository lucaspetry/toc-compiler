#include <string>
#include "TreeNode.h"

class Variable : public TreeNode {

    public:
        Variable(std::string id, Data::Type type);
        virtual ~Variable();
        TreeNode::ClassType classType() const;
        std::string getId() const;
        std::string printInOrder() const;
        void generateCode() const;

    private:
        std::string id;

};
