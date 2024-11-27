#pragma once
struct Node {
    int data;
    int color;          //  RED - 0 | BLACK - 1
    Node* left, * right, * parent;

    Node(int data) : data(data), color(0), left(nullptr), right(nullptr), parent(nullptr) {}
};


