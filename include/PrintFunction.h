#ifndef PRINTFUNCTION_H_
#define PRINTFUNCTION_H_

#include "Function.h"

/**
 * Função de impressão na tela 
 */
class PrintFunction : public Function {

    public:
        PrintFunction(TreeNode* param);
        virtual ~PrintFunction();
        TreeNode::ClassType classType() const;
        std::string printInOrder() const;
        llvm::Value* generateCode();

};

#endif
