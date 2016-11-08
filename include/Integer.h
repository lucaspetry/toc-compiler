#ifndef INTEGER_H_
#define INTEGER_H_

#include <string>
#include "TreeNode.h"

class Integer : public TreeNode {

    public:
        Integer(int integer);
        virtual ~Integer();
        TreeNode::ClassType classType() const;
        std::string printInOrder() const;

    private:
      int integer;

};

#endif
