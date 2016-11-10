#include "TreeNode.h"

class Boolean : public TreeNode {

    public:
        Boolean(bool value);
        virtual ~Boolean();
        TreeNode::ClassType classType() const;
        std::string printInOrder() const;
        void generateCode(llvm::IRBuilder<>* builder);

    private:
        bool value;

};
