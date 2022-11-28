//
// Created by hloi on 11/21/2022.
//

#ifndef CH11AVLTREEFA22_BINARY_TREE_H
#define CH11AVLTREEFA22_BINARY_TREE_H


#include <cstddef>
#include <string>
#include <sstream>
#include <iostream>
#include "BTNode.h"

template<typename  Item_Type>
class Binary_Tree {
public:
    Binary_Tree() : root(NULL) {}

    Binary_Tree(const Item_Type& the_data,
                const Binary_Tree<Item_Type>& left_child = Binary_Tree(),
                const Binary_Tree<Item_Type>& right_child = Binary_Tree()) :
            root(new BTNode<Item_Type>(the_data, left_child.root, right_child.root)) {}

            virtual ~Binary_Tree() {}

            Binary_Tree<Item_Type> get_left_subtree() const;

            Binary_Tree<Item_Type> get_right_subtree() const;

            const Item_Type& get_data() const;

            bool is_null() const;

            bool is_leaf() const;

            virtual std::string to_string() const;

            static Binary_Tree<Item_Type> read_binary_tree(std::istream& in);

protected:

    Binary_Tree(BTNode<Item_Type>* new_root) : root(new_root) {}

    BTNode<Item_Type>* root;

};

template<typename Item_Type>
Binary_Tree<Item_Type> Binary_Tree<Item_Type>::get_left_subtree() const {
    if (root == NULL) {
        throw std::invalid_argument("get left subtree on empty tree");
    }
    return Binary_Tree<Item_Type>(root->left);
}

template<typename Item_Type>
Binary_Tree<Item_Type> Binary_Tree<Item_Type>::get_right_subtree() const {
    if (root == NULL) {
        throw std::invalid_argument("get right subtree on empty tree");
    }
    return Binary_Tree<Item_Type>(root->right);
}


template<typename Item_Type>
const Item_Type& Binary_Tree<Item_Type>::get_data() const {
    if (root == NULL) {
        throw std::invalid_argument("get data on empty tree");
    }
    return Binary_Tree<Item_Type>(root->data);
}

template<typename Item_Type>
bool Binary_Tree<Item_Type>::is_null() const {
    return root == NULL;
}

template<typename Item_Type>
bool Binary_Tree<Item_Type>::is_leaf() const {
    if (root == NULL) {
        throw std::invalid_argument("get data on empty tree");
    }
    return root->left == NULL && root->right == NULL;
}

template<typename Item_Type>
std::string Binary_Tree<Item_Type>::to_string() const {
    std::ostringstream  os;
    if (is_null()) {
        os << "NULL" << std::endl;
    }
}

template<typename Item_Type>
Binary_Tree<Item_Type> Binary_Tree<Item_Type>::read_binary_tree(std::istream &in) {
    std::string next_line;
    std::getline(in, next_line);
    if (next_line == "NULL") {
        return Binary_Tree<Item_Type>();
    }
    else {
        Item_Type the_data;
        std::istringstream ins(next_line);
        ins >> the_data;
        Binary_Tree<Item_Type> left = read_binary_tree(in);
        Binary_Tree<Item_Type> right = read_binary_tree(in);
        return Binary_Tree<Item_Type>(the_data, left, right);
    }

}


template<typename  Item_Type>
std::ostream& operator<<(std::ostream& out,
        const Binary_Tree<Item_Type>& tree) {
    return out << tree.to_string();
}

template<typename Item_Type>
std::istream& operator>>(std::istream& in,
        Binary_Tree<Item_Type>& tree) {
    tree = Binary_Tree<Item_Type>::read_binary_tree(in);
}


#endif //CH11AVLTREEFA22_BINARY_TREE_H
