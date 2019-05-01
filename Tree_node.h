#ifndef AVL_TREE_TREE_NODE_H
#define AVL_TREE_TREE_NODE_H
/*
 *   @Daniil Samoylov
 *
 *      @volyomaS
 */
template <class T>
struct node
{
    node *left, *right, *parent;
    T value;
    int height_;
    node(T value_)
        :value(value_),
        left(nullptr),
        right(nullptr),
        parent(nullptr){};
};
#endif //AVL_TREE_TREE_NODE_H
