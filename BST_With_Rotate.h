//
// Created by hloi on 11/28/2022.
//

#ifndef CH11AVLTREEFA22_BST_WITH_ROTATE_H
#define CH11AVLTREEFA22_BST_WITH_ROTATE_H
#include "Binary_Search_Tree.h"

template<typename  Item_Type>
class BST_With_Rotate : public Binary_Search_Tree<Item_Type> {
protected:
    void rotate_right(BTNode<Item_Type>*& local_root) {
    BTNode<Item_Type>* temp = local_root->left;
    local_root->left = temp->right;
    temp->right = local_root;
    local_root = temp;
}
    void rotate_left(BTNode<Item_Type>*& local_root)
};
#endif //CH11AVLTREEFA22_BST_WITH_ROTATE_H
