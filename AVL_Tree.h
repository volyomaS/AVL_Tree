#ifndef AVL_TREE_AVL_TREE_H
#define AVL_TREE_AVL_TREE_H
/*
 *   @Daniil Samoylov
 *
 *      @volyomaS
 */
#include <iostream>
#include "Tree_node.h"
#include "AVL_Iter.h"

template <class T>
class AVL_Tree
{
public:
    typedef AVL_Iter<T> iterator;
    typedef AVL_Iter<const T> const_iterator;

    AVL_Tree()
        :root(nullptr),
        size_(0) {};
    AVL_Tree(const AVL_Tree& bst);
    AVL_Tree& operator=(const AVL_Tree& bst);
    template <class InputIt>
    void assign(InputIt first, InputIt last);
    iterator begin();
    const_iterator cbegin();
    iterator end();
    const_iterator cend();
    iterator insert(const T& value);
    iterator remove(const T& value);
    iterator find(const T& value);
    const_iterator find(const T& value) const;

    bool empty() const;
    size_t size() const;

private:
    node<T>* root;
    size_t size_;
    int height(node<T>* p);
    int bfactor(node<T>* p);
    void fixheight(node<T>* p);
    node<T>* rotateright(node<T>* p);
    node<T>* rotateleft(node<T>* q);
    node<T>* balance(node<T>* p);
    node<T>* insert(node<T>* p, T k, node<T>* par);
    node<T>* findmin(node<T>* p);
    node<T>* removemin(node<T>* p);
    node<T>* remove(node<T>* p, T k);
};

template<class T>
bool AVL_Tree<T>::empty() const
{
    return !root;
}

template<class T>
size_t AVL_Tree<T>::size() const
{
    return size_;
}

template<class T>
AVL_Iter<T> AVL_Tree<T>::begin() {
    node<T>* begin = root;
    while(begin -> left != nullptr)
    {
        begin = begin -> left;
    }
    return begin;
}

template<class T>
AVL_Iter<const T> AVL_Tree<T>::cbegin() {
    node<T>* begin = root;
    while(begin -> left != nullptr)
    {
        begin = begin -> left;
    }
    return begin;
}

template<class T>
AVL_Iter<T> AVL_Tree<T>::end() {
    return nullptr;
}

template<class T>
AVL_Iter<const T> AVL_Tree<T>::cend() {
    return nullptr;
}

template<class T>
int AVL_Tree<T>::height(node<T>* p)
{
    return p ? p->height_ : 0;
}

template<class T>
int AVL_Tree<T>::bfactor(node<T>* p)
{
    return height(p->right)-height(p->left);
}

template<class T>
void AVL_Tree<T>::fixheight(node<T>* p)
{
    int hl = height(p->left);
    int hr = height(p->right);
    p->height_ = (hl > hr ? hl : hr) + 1;
}

template<class T>
node<T>* AVL_Tree<T>::rotateright(node<T>* p)
{
    node<T>* q = p->left;
    p->left = q->right;
    node<T>* an = q->right;
    if (an)
        an->parent = p;
    q->parent = p->parent;
    node<T>* par = p->parent;
    if (par && par->left == p)
        par->left = q;
    else if (par)
        par->right = q;
    p->parent = q;
    q->right = p;
    fixheight(p);
    fixheight(q);
    return q;
}

template<class T>
node<T>* AVL_Tree<T>::rotateleft(node<T>* q)
{
    node<T>* p = q->right;
    q->right = p->left;
    node<T>* an = p->left;
    if (an)
        an->parent = q;
    p->parent = q->parent;
    node<T>* par = q->parent;
    if (par && par->left == q)
        par->left = p;
    else if (par)
        par->right = p;
    q->parent = p;
    p->left = q;
    fixheight(q);
    fixheight(p);
    return p;
}

template<class T>
node<T>* AVL_Tree<T>::balance(node<T>* p)
{
    fixheight(p);
    if( bfactor(p)==2 )
    {
        if( bfactor(p->right) < 0 )
            p->right = rotateright(p->right);
        return rotateleft(p);
    }
    if( bfactor(p)==-2 )
    {
        if( bfactor(p->left) > 0  )
            p->left = rotateleft(p->left);
        return rotateright(p);
    }
    return p;
}

template<class T>
node<T>* AVL_Tree<T>::insert(node<T>* p, T k, node<T>* par)
{
    if (!p)
    {
        size_++;
        node<T>* n = new node<T>(k);
        n->parent = par;
        return n;
    }
    if( k < p->value )
        p->left = insert(p->left,k,p);
    else
        p->right = insert(p->right,k,p);
    return balance(p);
}

template<class T>
node<T>* AVL_Tree<T>::findmin(node<T>* p)
{
    return p->left ? findmin(p->left) : p;
}

template<class T>
node<T>* AVL_Tree<T>::removemin(node<T>* p)
{
    if( p->left==0 )
        return p->right;
    p->left = removemin(p->left);
    return balance(p);
}

template<class T>
node<T>* AVL_Tree<T>::remove(node<T>* p, T k)
{
    if (!p) return 0;
    if( k < p->value )
        p->left = remove(p->left,k);
    else if( k > p->value )
        p->right = remove(p->right,k);
    else
    {
        node<T>* q = p->left;
        node<T>* r = p->right;
        delete p;
        size_--;
        if(!r) return q;
        node<T>* min = findmin(r);
        min->right = removemin(r);
        min->left = q;
        return balance(min);
    }
    return balance(p);
}

template <class T>
template <class InputIt>
void AVL_Tree<T>::assign(InputIt first, InputIt last)
{

};

template<class T>
AVL_Iter<T> AVL_Tree<T>::insert(const T& value)
{
    root = this->insert(root, value, nullptr);
    return root;
}

template<class T>
AVL_Iter<T> AVL_Tree<T>::remove(const T& value)
{
    root = this->remove(root, value);
    return root;
}

template<class T>
AVL_Iter<T> AVL_Tree<T>::find(const T& value)
{
    node<T>* res = root;
    while(!res)
    {
        if (res->value = value)
            return res;
        else if (value > res->value)
            res = res->right;
        else
            res = res->left;
    }
    return res;
}

template<class T>
AVL_Iter<const T> AVL_Tree<T>::find(const T& value) const
{
    node<T>* res = root;
    while(!res)
    {
        if (res->value = value)
            return res;
        else if (value > res->value)
            res = res->right;
        else
            res = res->left;
    }
    return res;
}

template<class T>
AVL_Tree<T>::AVL_Tree(const AVL_Tree &bst)
{
    root = new node<T>(bst.root);
    size_ = bst.size_;
}

template<class T>
AVL_Tree<T>& AVL_Tree<T>::operator=(const AVL_Tree<T>& bst)
{
    return (new AVL_Tree(bst.root->value));
}
#endif //AVL_TREE_AVL_TREE_H
