/*
|------------------------------------------------------------------------------------------
|							HEADER:       TREE_MAP.H
|------------------------------------------------------------------------------------------
| Summary:		Associative structure AVL tree
|
| Authors:		Mateo Terselich
|
| Started:		7 October 2019
|
| Collections:	1) TREE_MAP
*/
//definitions
#pragma once
//includes
#include "rb_node.h"
#include "helper.h"


namespace dt
{
	
	template <class Key, class Value> class tree_map
	{
		using Pair = pair<Key, Value>;
		//----------------------------------
		//			DATA MEMBERS
		//----------------------------------
		rb_node<Pair> * root_;
		size_t length_;
		//----------------------------------
		//		PRIVATE METHOD MEMBERS
		//----------------------------------
		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!RECURSION!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		//insert node pointer
		rb_node<Pair>* insert_recursively(const Pair& new_pair, rb_node<Pair>* head_node);
		rb_node<Pair>* insert_recursively(Pair&& new_pair, rb_node<Pair>* head_node);

		//search node
		bool search_recursively(const Key& key, rb_node<Pair>* head_node);
	public:
		//----------------------------------
		//				CONSTRUCTORS
		//----------------------------------
		tree_map();
		explicit tree_map(Pair&& r_pair );
		explicit tree_map(const Pair& l_pair);
		explicit tree_map(Key&& r_key, Value&& r_value);
		tree_map(const tree_map<Key, Value>& copy);
		tree_map(tree_map<Key, Value>&& r_tree);
		//----------------------------------
		//		PUBLIC METHOD MEMBERS
		//----------------------------------
		bool add(const Pair& data);
		bool add(Pair&& r_ref);
		bool add(Pair* pointer);
		//remove in the Tree
		bool remove(Pair& data);
		bool remove(Pair&& r_ref);
		bool remove(Pair* pointer);
		//clear set, is empty?
		bool empty();
		bool is_empty();
		//getters
		size_t size() const;
		//operator overloading
		tree_map<Key, Value>& operator=(const tree_map<Key, Value>& copy);
		tree_map<Key, Value>& operator=(tree_map<Key, Value>&& r_tree) noexcept;
		tree_map<Key, Value>& operator=(Pair&& r_value);
		//----------------------------------
		//				DESTRUCTOR
		//----------------------------------
		~tree_map();
	};
}

