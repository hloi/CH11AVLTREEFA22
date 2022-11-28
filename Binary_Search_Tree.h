//
// Created by hloi on 11/21/2022.
//

#ifndef CH11AVLTREEFA22_BINARY_SEARCH_TREE_H
#define CH11AVLTREEFA22_BINARY_SEARCH_TREE_H
#include "Binary_Tree.h"

template<typename Item_Type>
class Binary_Search_Tree : public Binary_Tree<Item_Type> {

public:
    Binary_Search_Tree() :  Binary_Tree<Item_Type>() {}

    virtual bool insert(const Item_Type& item);

    virtual bool erase(const Item_Type& item);

    const Item_Type* find(const Item_Type& target) const;

private:
    virtual bool insert(BTNode<Item_Type>*& local_root,
                        const Item_Type& item);

    virtual bool erase(BTNode<Item_Type>*& local_root,
                        const Item_Type& item);

    const Item_Type* find(BTNode<Item_Type>*& local_root,
                          const Item_Type& target) const;

    virtual void replace_parent(BTNode<Item_Type>*& old_root,
                                BTNode<Item_Type>*& local_root);
};

template<typename Item_Type>
bool Binary_Search_Tree<Item_Type>::insert(const Item_Type &item) {
    return insert(this.root, item);
    return false;
}

template<typename Item_Type>
bool Binary_Search_Tree<Item_Type>::insert(BTNode<Item_Type> *&local_root, const Item_Type &item) {
    if (local_root == NULL) {
        local_root = new BTNode<Item_Type>(item);
        return true;
    }
    else {
        if (item < local_root->data) {
            return insert(local_root.left, item);
        } else if (item > local_root->data) {
            return insert(local_root.right, item);
        } else { // ==
            return false;
        }
    }
    return false;
}

template<typename Item_Type>
bool Binary_Search_Tree<Item_Type>::erase(const Item_Type &item) {
    return rase(this->root, item);
}

template<typename Item_Type>
bool Binary_Search_Tree<Item_Type>::erase(BTNode<Item_Type> *&local_root, const Item_Type &item) {
    if (local_root == NULL) {
        return false;
    } else {
        if (item < local_root->data) {
            return insert(local_root.left, item);
        } else if (item > local_root->data) {
            return insert(local_root.right, item);
        } else { // ==
            BTNode<Item_Type>* old_root = local_root;
            if (local_root->left == NULL) {
                local_root = local_root->right;
            } else if (local_root->right == NULL) {
                local_root = local_root->left;
            } else {
                replace_parent(old_root, old_root->left)
            }
            delete old_root;
            return true;
        }
    }
    return false;
}

template<typename Item_Type>
void Binary_Search_Tree<Item_Type>::replace_parent(BTNode<Item_Type> *&old_root, BTNode<Item_Type> *&local_root) {
    if (local_root->right != NULL) {
        replace_parent(old_root, local_root->right);
    } else {
        old_root->data = local_root->data;
        old_root = local_root;
        local_root = local_root->left;
    }
}

template<typename Item_Type>
const Item_Type *Binary_Search_Tree<Item_Type>::find(const Item_Type &target) const {
    return find(this->root, target);
}

template<typename Item_Type>
const Item_Type *Binary_Search_Tree<Item_Type>::find(BTNode<Item_Type> *&local_root, const Item_Type &target) const {
    if (local_root == NULL) {
        return NULL;
    }
    if (target < local_root->data) {
        return find(local_root->left, target);
    } else if (target > local_root->data) {
        return find(local_root->right, target);
    }
    else {
        return *(local_root->data);
    }
    return nullptr;
}


#endif //CH11AVLTREEFA22_BINARY_SEARCH_TREE_H
