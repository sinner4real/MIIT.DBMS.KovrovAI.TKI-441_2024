#pragma once
#include "../struckk/rooot.h"
using namespace std;

/*
*  @brief Class Figure
*/


class redblack
{
	private:
		/*
		*  @brief sides of a triangle
		*/
		Node* root;
		Node* grandparent(Node* n);
		Node* uncle(Node* n);
		void rotate_left(Node* n);
		void rotate_right(Node* n);
		void delete_tree(Node* node);
		void insert_case1(Node* n);
		void insert_case2(Node* n);
		void insert_case3(Node* n);
		void insert_case4(Node* n);
		void insert_case5(Node* n);
		void inorderHelper(Node* root, string indent, bool last);
		Node* sibling(Node* n);
		void replace_node(Node* n, Node* child);
		void delete_one_child(Node* n);
		void delete_case1(Node* n);
		void delete_case2(Node* n);
		void delete_case3(Node* n);
		void delete_case4(Node* n);
		void delete_case5(Node* n);
		void delete_case6(Node* n);
		bool is_leaf(Node* n);
		Node* copy_tree(Node* other_root, Node* parent);
		int count_nodes_helper(Node* node) const;




	public:
		void inorder();
		void insert(int value);
		void delete_value(int value);
		redblack();
		redblack(const initializer_list<int>& values); // Список инициализации
		redblack(const redblack& other); // Конструктор копирования
		redblack(redblack&& other) noexcept; // Конструктор перемещения
		~redblack();
		int count_nodes() const;
};

