#ifndef BOOLEAN_H_
#define BOOLEAN_H_

#include "TreeNode.h"

/**
 * Valor booleano 
 */
class Boolean : public TreeNode {

    public:
        Boolean(bool value);
        virtual ~Boolean();
        TreeNode::ClassType classType() const;
        std::string printInOrder() const;
        llvm::Value* generateCode();

    private:
        bool value;

};

#endif
