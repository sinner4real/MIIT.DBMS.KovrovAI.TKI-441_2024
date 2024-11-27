#include <iostream>
#include "../triangle/figure.h"

/**
* @brief Point of entering the programm
* @return 0 in case of unluck
*/


int main()
{ 
    redblack tree;

        // Вставляем данные
    tree.insert(1);
    tree.insert(6);
    tree.insert(8);
    tree.insert(11);
    tree.insert(13);
    tree.insert(17);
    tree.insert(15);
    tree.insert(25);
    tree.insert(22);
    tree.insert(27);


    std::cout << "Inorderrrr traversal of created Tree\n";
    tree.inorder();

    tree.delete_value(1);
    tree.inorder();

    return 0;
}