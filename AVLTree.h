//
// Created by hloi on 11/21/2022.
//

#ifndef CH11AVLTREEFA22_AVLTREE_H
#define CH11AVLTREEFA22_AVLTREE_H
#include <string>
#include <sstream>
#include "BST_With_Rotate.h"
#include "AVLNode.h"

template<typename Item_Type>
class AVL_Tree : public BST_With_Rotate<Item_Type> {
public :
    AVL_Tree() : BST_With_Rotate<Item_Type() {}
    void rebalance_left(BTNode<Item_Type>*& local_root);
    virtual bool insert(const Item_Type& item) {
        return insert(this->root, item);
    }
    /** Remove an item from the tree by calling overridden erase function.
     post: The item is no longer in the tree.
     @param item The item to be removed
     @return true only if the item was in the tree
    */
    virtual bool erase(const Item_Type& item) {
        return erase(this->root, item); }

private:
    virtual bool insert(BTNode<Item_Type>*& local_root, const Item_Type& item);
    /** Remove an item from the tree
         @param local_root A reference to the current root
         @param item The item to be removed
         @return true only if the item was in the tree
         Post: The item is no longer in the tree.
     */
    /** Correct a critical left balance condition
     pre:  local_root is the root of an AVL subtree that is
     critically heavy.
     post: balance is restored
     @param local_root is the root of the AVL subtree
     that needs rebalancing
 */
    void rebalance_left(BTNode<Item_Type>*& local_root);

    /** Correct a critical right balance condition
        pre:  local_root is the root of an AVL subtree that is
        critically heavy.
        post: balance is restored
        @param local_root is the root of the AVL subtree
        that needs rebalancing
    */
    void rebalance_right(BTNode<Item_Type>*& local_root);
    /** Remove an item from the tree
      @param local_root A reference to the current ro
      @param item The item to be removed
      @return true only if the item was in the tree
      Post: The item is no longer in the tree.
  */
    virtual bool erase(BTNode<Item_Type>*& local_root,
                       const Item_Type& item);

    /** Find a replacement for a node that is being deleted
        This function finds the right-most local root that
        does not have a right child. The data in this local_root
        replaces the data in old_root. The pointer to local_root
        is then saved in old_root and local_root is replaced
        by its left child.
        @param old_root Reference to the pointer to old parent
        @param local_root Reference to the pointer to local root
    */
    virtual void replace_parent(BTNode<Item_Type>*& old_root,
                                BTNode<Item_Type>*& local_root);

    /** Correct a critical left balance condition due to erase
    pre:  local_root is the root of an AVL subtree that is
    critically heavy.
    post: balance is restored
    @param local_root is the root of the AVL subtree
    that needs rebalancing
*/
    void erase_rebalance_left(BTNode<Item_Type>*& local_root);

    /** Correct a critical right balance condition due to erase
        pre:  local_root is the root of an AVL subtree that is
        critically heavy.
        post: balance is restored
        @param local_root is the root of the AVL subtree
        that needs rebalancing
    */
    void erase_rebalance_right(BTNode<Item_Type>*& local_root);

    bool increase;
    bool decrease;
};

template<typename Item_Type>
bool AVL_Tree<Item_Type>::insert(BTNode<Item_Type> *&local_root, const Item_Type &item) {
    if (local_root == NULL) {
        local_root = new AVLNode<Item_Type>(item);
        increase = true;
        return true;
    }
    else {
        if (item < local_root->data) {
            bool return_value = insert(local_root->left, item);
            if (increase) {
                AVLNode<Item_Type> AVL_local_root = dynamic_cast<AVLNode<Item_Type>*>(local_root);
                switch (AVL_local_root->balance) {
                    case AVLNode<Item_Type>::BALANCE :
                        AVL_local_root->balance = AVLNode<Item_Type>::LEFT_HEAVY;
                        break;
                    case AVLNode<Item_Type>::RIGHT_HEAVY :
                        AVL_local_root->balance = AVLNode<Item_Type>::BALANCE;
                        increase = false;
                        break;
                    case AVLNode<Item_Type>::LEFT_HEAVY :
                        rebalance_left(local_root);
                        increase = false;
                        break;
                }  // switch
            } // increase
            return return_value;
        }
        else if (item > local_root->data) {
            bool return_value = insert(local_root->right, item);
            if (increase) {
                AVLNode<Item_Type> AVL_local_root = dynamic_cast<AVLNode<Item_Type>*>(local_root);
                switch (AVL_local_root->balance) {
                    case AVLNode<Item_Type>::BALANCE :
                        AVL_local_root->balance = AVLNode<Item_Type>::RIGHT_HEAVY;
                        break;
                    case AVLNode<Item_Type>::RIGHT_HEAVY :
                        rebalance_right(local_root);
                        increase = false;
                        break;
                    case AVLNode<Item_Type>::LEFT_HEAVY :
                        AVL_local_root->balance = AVLNode<Item_Type>::BALANCED;
                        increase = false;
                        break;
                }  // switch
            } // increase
            return return_value;
        }
        else {  // item is found in the tree
            increase = false;
            return false;
        }
    }
}

template<typename Item_Type>
void AVL_Tree<Item_Type>::rebalance_left(BTNode<Item_Type> *&local_root) {
    AVLNode<Item_Type> AVL_local_root = dynamic_cast<AVLNode<Item_Type>*>(local_root);
    AVLNode<Item_Type>* left_child = dynamic_cast<AVLNode<Item_Type>*>(local_root->left);
    if (left_child->balance == AVLNode<Item_Type>::RIGHT_HEAVY) { // left right
        AVLNode<Item_Type>* left_right_child = dynamic_cast<AVLNode<Item_Type>*>(left_child->right);
        // adjust the balances to be the new values after the rotation
        if (left_right_child->balance == AVLNode<Item_Type>::LEFT_HEAVY) { // left right left
            left_child->balance = AVLNode<Item_Type>::BALANCED;
            left_right_child->balance = AVLNode<Item_Type>::BALANCED;
            AVL_local_root.balance = AVLNode<Item_Type>::RIGHT_HEAVY;
        } else if (left_right_child->balance == AVLNode<Item_Type>::BALANCED) {  // left right right
            left_child->balance = AVLNode<Item_Type>::BALANCED;
            left_right_child->balance = AVLNode<Item_Type>::BALANCED;
            AVL_local_root.balance = AVLNode<Item_Type>::BALANCED;
        }
        else {  // left right blance
            left_child->balance = AVLNode<Item_Type>::LEFT_HEAVY;
            left_right_child->balance = AVLNode<Item_Type>::BALANCED;
            AVL_local_root.balance = AVLNode<Item_Type>::BALANCED;
        }
        this->rotate_left(local_root->left);

    } else { // left-left
        left_child->balance = AVLNode<Item_Type>::BALANCED;
        AVL_local_root.balance = AVLNode<Item_Type>::BALANCED;
    }
    this->rotate_right(local_root);
}

/**
 *
 * @tparam Item_Type
 * @param local_root
 * @param item
 * @return
 */
 /** override erase funcction from binary_search_tree
template<typename Item_Type>
bool AVL_Tree<Item_Type>::erase(
        BTNode<Item_Type>*& local_root,
        const Item_Type& item) {
    if (local_root == NULL) {
        decrease = false;  // modified for AVL_Tree erase
        return false;
    } else {
        if (item < local_root->data)
            erase(local_root->left, item);
            // after return, adjust height of left subtree
            // add code below
        else if (local_root->data < item)
            erase(local_root->right, item);
            // after return, adjust height of right subtree
            // add code below
        else { // Found item
            BTNode<Item_Type>* old_root = local_root;
            if (local_root->left == NULL) {
                local_root = local_root->right;
                // set decrease to true
            } else if (local_root->right == NULL) {
                local_root = local_root->left;
                // set decrease to true
            } else {
                replace_parent(old_root, old_root->left);
            }
            delete old_root;
            return true;
        }
    }
}
  */

#endif //CH11AVLTREEFA22_AVLTREE_H
