#include "TreeNode.h"

class Float : public TreeNode {

    public:
        Float(float value);
        virtual ~Float();
        TreeNode::ClassType classType() const;
        std::string printInOrder() const;
        llvm::Value* generateCode(llvm::IRBuilder<>* builder);

    private:
        float value;

};
