#include "TreeNode.h"

class String : public TreeNode {

    public:
        String(std::string text);
        virtual ~String();
        TreeNode::ClassType classType() const;
        std::string printInOrder() const;
        llvm::Value* generateCode();
        std::string getText();

    private:
        std::string text;

};
