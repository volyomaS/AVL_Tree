/*
 *   @Daniil Samoylov
 *
 *      @volyomaS
 */
#include "AVL_Tree.h"
#include <algorithm>
int main() {
    AVL_Tree <int> my_tree;

    my_tree.insert(5);
    my_tree.insert(6);
    my_tree.insert(4);
    my_tree.insert(2);
    my_tree.insert(7);
    std::cout << std::all_of(my_tree.begin(), my_tree.end(), [](int i){return i > 0;});
    std::cout << "\n";
    std::cout << std::all_of(my_tree.begin(), my_tree.end(), [](int i){return i > 5;});


    return 0;
}