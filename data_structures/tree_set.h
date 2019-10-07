/*
------------------------------------------------------------------------------------------
							HEADER:       TREE_SET.H
------------------------------------------------------------------------------------------
 Summary:		Associative structure AVL tree

 Authors:		Mateo Terselich

 Started:		3 December 2018

 Collections:	1) TREE_SET
*/
//definitions
#pragma once
//includes
#include "doubly_node.h"

namespace dt
{
	template <class C> class tree_set
	{
		//_head of the Tree-set, size MEMBER VARIABLES
		doubly_node<C>* root_tree;
		unsigned int length_tree;
		//----------------------------------
		//		PRIVATE METHOD MEMBERS
		//----------------------------------
		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!RECURSION!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		doubly_node<C>* insert_recursively(const C& new_node, doubly_node<C>* head_node);
		//get height of a given node
		int depth_recursively(const doubly_node<C>* head_node);
		//search a value in the tree
		bool search_recursively(const C& data, doubly_node<C>* head_node);
		//delete tree
		doubly_node<C>* delete_tree(doubly_node<C>* head_node);
		//get balance for factor of node 
		int get_balance(const doubly_node<C>* head_node);
		//delete node given
		doubly_node<C>* delete_node_recursive(C to_delete, doubly_node<C>* head_node);
		//AVL rotation
		doubly_node<C>* right_rotate(doubly_node<C>* y);
		doubly_node<C>* left_rotate(doubly_node<C>* x);
		//min node in the subtree-tree
		doubly_node<C>* min_node(doubly_node<C>* head_node);
	public:
		//----------------------------------
		//				CONSTRUCTORS
		//----------------------------------
		tree_set();
		explicit tree_set(C&& r_ref);
		explicit tree_set(const C& data);
		tree_set(const tree_set<C>& copy);
		tree_set(tree_set<C>&& r_set) noexcept;
		//----------------------------------
		//		PUBLIC METHOD MEMBERS
		//----------------------------------
		//add new value or node
		bool add(const C& data);
		bool add(C&& r_ref);
		bool add(C* pointer);
		//remove in the Tree
		bool remove(C& data);
		bool remove(C&& r_ref);
		bool remove(C* pointer);
		//clear set, is empty?
		bool empty();
		bool is_empty();
		//getters
		unsigned int size() const;
		//operator overloading
		tree_set<C>& operator=(const tree_set<C>& set);
		tree_set<C>& operator=(tree_set<C>&& r_set) noexcept;
		tree_set<C>& operator=(C&& r_value);
		//destructor
		~tree_set();
	};
}
