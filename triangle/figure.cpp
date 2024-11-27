#include <stdexcept>
#include <cmath>
#include "figure.h"
#include <sstream>
#include <iostream>
using namespace std;


/*
*@brief конструктор обычный
*/
redblack::redblack()
{
	root = nullptr;
}


/*
*@brief деструктор
*/
redblack::~redblack()
{
    delete_tree(root);
}


/*
*@brief подсчет колличества элементов дерева
* @return колличество элементов
*/
int redblack::count_nodes() const
{
    return count_nodes_helper(root);
}

/*
*@brief функция для вставки новых корней дерева
*/
void redblack::insert(int value) {
    Node* newNode = new Node(value);

    if (root == nullptr) {
        root = newNode;
        insert_case1(newNode);
        return;
    }

    Node* current = root;
    Node* parent = nullptr;

    while (current != nullptr) {
        parent = current;
        if (value == current->data) {
            cout << "Duplicate value: " << value << endl;
            delete newNode;
            return;
        }
        else if (value < current->data) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }

    newNode->parent = parent;

    if (value < parent->data) {
        parent->left = newNode;
    }
    else {
        parent->right = newNode;
    }

    insert_case1(newNode);
}


/*
*@brief функция для удаления корня дерева
*/
void redblack::delete_value(int value)
{
    Node* nodeToDelete = root;
    while (nodeToDelete != nullptr && nodeToDelete->data != value) {
        if (value < nodeToDelete->data) {
            nodeToDelete = nodeToDelete->left;
        }
        else {
            nodeToDelete = nodeToDelete->right;
        }
    }

    if (nodeToDelete == nullptr) {
        cout << "Value " << value << " not found in the tree." << endl;
        return;
    }

    if (!is_leaf(nodeToDelete->left) && !is_leaf(nodeToDelete->right)) {
        // Найдём минимальный узел в правом поддереве (in-order successor)
        Node* successor = nodeToDelete->right;
        while (successor->left != nullptr) 
        {
            successor = successor->left;
        }
        nodeToDelete->data = successor->data;
        nodeToDelete = successor; // Удаляем преемника
    }

    delete_one_child(nodeToDelete);
}


/*
*@brief функция для поиска деда корня (корень->parent->parent)
*@return Node * n->parent->parent
*/
Node* redblack::grandparent(Node* n) {
    if ((n != nullptr) && (n->parent != nullptr)) {
        return n->parent->parent;
    }
    return nullptr;
}


/*
*@brief поиск дяди корня (брат отца)
* @return Node * n->parent->other_child
*/
Node* redblack::uncle(Node* n) {
    Node* g = grandparent(n);
    if (g == nullptr) return nullptr;
    if (n->parent == g->left) {
        return g->right;
    }
    return g->left;
}

/*
*@brief поворот дерева против часовой стрелки (налево)
*/
void redblack::rotate_left(Node* n) {
    Node* pivot = n->right;
    pivot->parent = n->parent;
    if (n->parent == nullptr) {
        root = pivot;
    }
    else if (n->parent->left == n) {
        n->parent->left = pivot;
    }
    else {
        n->parent->right = pivot;
    }

    n->right = pivot->left;
    if (pivot->left != nullptr) {
        pivot->left->parent = n;
    }

    n->parent = pivot;
    pivot->left = n;
}

/*
*@brief поворот дерева по часовой стрелке (направо)
*/
void redblack::rotate_right(Node* n) {
    Node* pivot = n->left;
    pivot->parent = n->parent;
    if (n->parent == nullptr) {
        root = pivot;
    }
    else if (n->parent->left == n) {
        n->parent->left = pivot;
    }
    else {
        n->parent->right = pivot;
    }

    n->left = pivot->right;
    if (pivot->right != nullptr) {
        pivot->right->parent = n;
    }

    n->parent = pivot;
    pivot->right = n;
}


/*
*@brief вспомогательная функция для удаления дерева
*/
void redblack::delete_tree(Node* node)
{
    if (node != nullptr) {
        delete_tree(node->left);  
        delete_tree(node->right); 
        delete node;              
    }
}

/*
*@brief балансировка дерева после добавления нового узла случай 1 (теория для этого взята из википедии)
*/
void redblack::insert_case1(Node* n) {
    if (n->parent == nullptr) {
        n->color = 1; // Корень всегда черный
        root = n;
    }
    else {
        insert_case2(n);
    }
}

/*
*@brief балансировка дерева после добавления нового узла случай 2 (теория для этого взята из википедии)
*/
void redblack::insert_case2(Node* n) {
    if (n->parent->color == 1) return; // Дерево корректно
    insert_case3(n);
}

/*
*@brief балансировка дерева после добавления нового узла случай 3 (теория для этого взята из википедии)
*/
void redblack::insert_case3(Node* n) {
    Node* u = uncle(n);
    Node* g;

    if ((u != nullptr) && (u->color == 0)) {
        n->parent->color = 1;
        u->color = 1;
        g = grandparent(n);
        g->color = 0;
        insert_case1(g);
    }
    else {
        insert_case4(n);
    }
}


/*
*@brief балансировка дерева после добавления нового узла случай 4 (теория для этого взята из википедии)
*/
void redblack::insert_case4(Node* n) {
    Node* g = grandparent(n);

    if ((n == n->parent->right) && (n->parent == g->left)) {
        rotate_left(n->parent);
        n = n->left;
    }
    else if ((n == n->parent->left) && (n->parent == g->right)) {
        rotate_right(n->parent);
        n = n->right;
    }
    insert_case5(n);
}


/*
*@brief балансировка дерева после добавления нового узла случай 5 (теория для этого взята из википедии)
*/
void redblack::insert_case5(Node* n) {
    Node* g = grandparent(n);
    if (g == nullptr) return;

    n->parent->color = 1;
    g->color = 0;
    if ((n == n->parent->left) && (n->parent == g->left)) {
        rotate_right(g);
    }
    else {
        rotate_left(g);
    }
}

/*
*@brief вспомогательная функция для красивого вывода целого дерева
*/
void redblack::inorderHelper(Node* root, string indent, bool last) {
    if (root != nullptr) {
        cout << indent;
        if (last) {
            cout << "R----";
            indent += "   ";
        }
        else {
            cout << "L----";
            indent += "|  ";
        }
        string sColor = (root->color == 0) ? "RED" : "BLACK";
        cout << root->data << "(" << sColor << ")" << endl;
        inorderHelper(root->left, indent, false);
        inorderHelper(root->right, indent, true);
    }
}

/*
*@brief функция для поиска брата узла
* @return Node* брат узла
*/
Node* redblack::sibling(Node* n)
{
    if (n == n->parent->left)
        return n->parent->right;
    else
        return n->parent->left;
}

void redblack::replace_node(Node* n, Node* child)
{
    if (n->parent == nullptr) {
        root = child;
    }
    else if (n == n->parent->left) {
        n->parent->left = child;
    }
    else {
        n->parent->right = child;
    }

    if (child != nullptr) {
        child->parent = n->parent;
    }
}

void redblack::delete_one_child(Node* n)
{
    Node* child = (n->right != nullptr) ? n->right : n->left;

    if (child != nullptr) {
        replace_node(n, child);
        if (n->color == 1) {
            if (child->color == 0) {
                child->color = 1;
            }
            else {
                delete_case1(child);
            }
        }
    }
    else if (n->parent == nullptr) {
        root = nullptr;
    }
    else {
        if (n->color == 1) {
            delete_case1(n);
        }
        replace_node(n, nullptr);
    }

    delete n;
}

void redblack::delete_case1(Node* n)
{
    if (n->parent != nullptr)
        delete_case2(n);
}

void redblack::delete_case2(Node* n)
{
    Node* s = sibling(n);

    if (s->color == 0) {
        n->parent->color = 0;
        s->color = 1;
        if (n == n->parent->left)
            rotate_left(n->parent);
        else
            rotate_right(n->parent);
    }
    delete_case3(n);
}

void redblack::delete_case3(Node* n)
{
    Node* s = sibling(n);

    if (s == nullptr) return; 

    if ((n->parent->color == 1) &&
        (s->color == 1) &&
        (s->left == nullptr || s->left->color == 1) &&
        (s->right == nullptr || s->right->color == 1)) {
        s->color = 0;
        delete_case1(n->parent);
    }
    else {
        delete_case4(n);
    }
}

void redblack::delete_case4(Node* n)
{
    Node* s = sibling(n);

    if (
        (n->parent->color == 0) &&
        (s->color == 1) &&
        (s->left->color == 1) &&
        (s->right->color == 1)
        )
    {
        s->color = 0;
        n->parent->color = 1;
    }
    else
        delete_case5(n);
}

void redblack::delete_case5(Node* n)
{
    Node* s = sibling(n);

    if (s->color == 1) { 
        if (
            (n == n->parent->left) &&
            (s->right->color == 1) &&
            (s->left->color == 0)
            )
        {
            s->color = 0;
            s->left->color = 1;
            rotate_right(s);
        }
        else if (
            (n == n->parent->right) &&
            (s->left->color == 1) &&
            (s->right->color == 0)
            )
        {
            s->color = 0;
            s->right->color = 1;
            rotate_left(s);
        }
    }
    delete_case6(n);
}

void redblack::delete_case6(Node* n)
{
    Node* s = sibling(n);

    s->color = n->parent->color;
    n->parent->color = 1;

    if (n == n->parent->left) {
        s->right->color = 1;
        rotate_left(n->parent);
    }
    else {
        s->left->color = 1;
        rotate_right(n->parent);
    }
}

bool redblack::is_leaf(Node* n)
{
    return n == nullptr || (n->left == nullptr && n->right == nullptr);
}

/*
*@brief
*/
void redblack::inorder() {
    if (root == nullptr)
        cout << "Tree is empty." << endl;
    else {
        cout << "Red-Black Tree:" << endl;
        inorderHelper(root, "", true);
    }
}

/*
*@brief Конструктор с инициализатором списка 
*/
redblack::redblack(const initializer_list<int>& values) : root(nullptr) {
    for (int value : values) {
        insert(value);
    }
}

/*
*@brief Конструктор копирования
*/
redblack::redblack(const redblack& other) : root(nullptr) {
    root = copy_tree(other.root, nullptr);
}

/*
*@brief Вспомогательная функция для копирования дерева
*/
Node* redblack::copy_tree(Node* other_root, Node* parent) {
    if (!other_root) return nullptr;

    Node* new_node = new Node(other_root->data);
    new_node->color = other_root->color;
    new_node->parent = parent;
    new_node->left = copy_tree(other_root->left, new_node);
    new_node->right = copy_tree(other_root->right, new_node);
    return new_node;
}

/*
*@brief Вспомогательная функция для подсчета узлов дерева
*/
int redblack::count_nodes_helper(Node* node) const
{
    if (node == nullptr) {
        return 0; 
    }
    return 1 + count_nodes_helper(node->left) + count_nodes_helper(node->right);
}


/*
*@brief Конструктор перемещения
*/
redblack::redblack(redblack&& other) noexcept : root(other.root) {
    other.root = nullptr; // Исходное дерево теряет владение
}

