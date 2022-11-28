//
// Created by hloi on 11/21/2022.
//

#ifndef CH11AVLTREEFA22_BTNODE_H
#define CH11AVLTREEFA22_BTNODE_H
#include <cstddef>
#include <string>
#include <sstream>

#include "Binary_Search_Tree.h"
template<typename Item_Type>
struct BTNode {
    Item_Type data;
    BTNode<Item_Type>* left;
    BTNode<Item_Type>* right;

    BTNode(const Item_Type& the_data,
           BTNode<Item_Type>* left_val = NULL,
           BTNode<Item_Type>* right_val = NULL
    ) : data(the_data), left(left_val), right(right_val) {}

    virtual ~BTNode() {}

    virtual std::string to_string() const {
        std::ostringstream os;
        os << data;
        return os.str();
    }
};

template<typename Item_Type>
std::ostream& operator<<(std::ostream& out,
                         const BTNode<Item_Type>& node) {
    return out << node.to_string();
}


#endif //CH11AVLTREEFA22_BTNODE_H
