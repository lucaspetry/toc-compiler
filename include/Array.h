#ifndef ARRAY_H_
#define ARRAY_H_

#include <string>
#include "TreeNode.h"

// to test
#include <iostream>

class Array : public TreeNode {

    public:
        Array(std::string id, Data::Type type, int size); // type name [size]
        virtual ~Array();
        TreeNode::ClassType classType() const;
        std::string printInOrder() const;
        std::string toString(Data::Type type) const;

    private:
      std::string id;
      Data::Type type;
      int size;

};
#endif
