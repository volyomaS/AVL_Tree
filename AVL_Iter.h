#ifndef AVL_TREE_AVL_ITER_H
#define AVL_TREE_AVL_ITER_H
/*
 *   @Daniil Samoylov
 *
 *      @volyomaS
 */
#include "iostream"
#include "Tree_node.h"

template<class T>
class AVL_Iter: public std::iterator<std::bidirectional_iterator_tag, T>
{
public:
    AVL_Iter(node<T> *p) : root(p) {};
    AVL_Iter(const AVL_Iter &it) : root(it.root) {};
    bool operator!=(AVL_Iter const& other) const;
    bool operator==(AVL_Iter const& other) const;
    typename AVL_Iter::reference operator*() const{
        return root->value;
    }
    AVL_Iter& operator++(int);
    AVL_Iter& operator++();
    AVL_Iter& operator--(int);
    AVL_Iter& operator--();
private:
    node<T>* root;
};

template<class T>
bool AVL_Iter<T>::operator!=(AVL_Iter const &other) const
{
    return root != other.root;
}

template<class T>
bool AVL_Iter<T>::operator==(AVL_Iter const &other) const
{
    return root == other.root;
}

template <class T>
node<T>* minimum(node<T>* x)
{
    if (x->left == nullptr)
        return x;
    return minimum(x->left);
}

template <class T>
node<T>* maximum(node<T>* x)
{
    if (x->right == nullptr)
        return x;
    return maximum(x->right);
}

template<class T>
AVL_Iter<T>& AVL_Iter<T>::operator++()
{
    if (root->right != nullptr)
    {
        root = minimum(root->right);
        return *this;
    }
    node<T>* other = root->parent;
    while (other != nullptr && root == other->right)
    {
        root = other;
        other = other->parent;
    }
    root = other;
    return *this;
}

template<class T>
AVL_Iter<T>& AVL_Iter<T>::operator++(int)
{
    if (root->right != nullptr)
    {
        root = minimum(root->right);
        return *this;
    }
    node<T>* other = root->parent;
    while (other != nullptr && root == other->right)
    {
        root = other;
        other = other->parent;
    }
    root = other;
    return *this;
}

template<class T>
AVL_Iter<T>& AVL_Iter<T>::operator--()
{
    if (root->left != nullptr)
    {
        root = maximum(root->left);
        return *this;
    }
    node<T>* other = root->parent;
    while (other != nullptr && root == other->left)
    {
        root = other;
        other = other->parent;
    }
    root = other;
    return *this;
}

template<class T>
AVL_Iter<T>& AVL_Iter<T>::operator--(int)
{
    if (root->left != nullptr)
    {
        root = maximum(root->left);
        return *this;
    }
    node<T>* other = root->parent;
    while (other != nullptr && root == other->left)
    {
        root = other;
        other = other->parent;
    }
    root = other;
    return *this;
}
        #endif //AVL_TREE_AVL_ITER_H
