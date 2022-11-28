//
// Created by hloi on 11/21/2022.
//

#ifndef CH11AVLTREEFA22_AVLNODE_H
#define CH11AVLTREEFA22_AVLNODE_H
#include "BTNode.h"
template<typename Item_Type>
struct AVLNode : public BTNode<Item_Type> {
enum balance_Type {LEFT_HEAVY = -1, BALANCED = 0, RIGHT_HEAVY = 1};
balance_Type balance;

AVLNode(const Item_Type& the_data,
        BTNode<Item_Type>* left_val= NULL,
        BTNode<Item_Type>* right_val = NULL) :
        BTNode<Item_Type>(the_data, left_val, right_val, balance(BALANCED)) {}

        virtual  ~AVLNode() {}

        virtual std::string to_string() const {
        std::ostringstream  os;
        os << balance << ": " << this->data;
        return os.str();
}
};


#endif //CH11AVLTREEFA22_AVLNODE_H
