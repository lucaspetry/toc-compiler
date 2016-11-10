#include "TreeNode.h"

class Integer : public TreeNode {

    public:
        Integer(int value);
        virtual ~Integer();
        TreeNode::ClassType classType() const;
        std::string printInOrder() const;
        llvm::Value* generateCode(llvm::IRBuilder<>* builder);
        int getValue();
    
    private:
        int value;

};
