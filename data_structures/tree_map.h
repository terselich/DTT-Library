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
#include "pch.h"
#include "rb_node.h"
#include "helper.h"


namespace dt
{
	
	template <class Key, class Value> class tree_map
	{
		using Pair = pair<Key, Value>;
		using _NODE_ = rb_node<Pair>;
		using _RB_TREE_ = tree_map<Key, Value>;
		//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		//																						DATA MEMBERS
		//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		_NODE_ * root_;
		size_t length_;
		//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		//																				RECURSIVE PRIVATE METHODS
		//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!RECURSION!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

		//insert l value
		_NODE_* insert_recursively(const Pair& new_pair, _NODE_* head_node)
		{
			//base case
			if (head_node == nullptr)
			{
				head_node = new _NODE_{ new_pair };
				length_++;
				return head_node;
			}
			//when head is not null search path to be insert in BTS right comparing hashed values of the key (STD::HASH returns a SIZE_T value)
			if (std::hash<Key>(new_pair->key_) > std::hash<Key>(head_node->data.key_))
			{
				head_node->right = insert_recursively(new_pair, head_node->right);
				//connect with parent
				head_node->right->parent_ = head_node;
			}
			//when head is not null search path to be insert in BTS left
			else if (std::hash<Key>(new_pair->key_) < std::hash<Key>(head_node->data.key_))
			{
				head_node->left = insert_recursively(new_pair, head_node->left);
				//connect with parent
				head_node->left->parent_ = head_node;
			}
			//default
			return head_node;
		}

		//insert r value
		_NODE_* insert_recursively(Pair&& new_pair, _NODE_* head_node)
		{
			//base case
			if (head_node == nullptr)
			{
				head_node = new _NODE_{ std::move(new_pair) };
				length_++;
				return head_node;
			}
			//when head is not null search path to be insert in BTS right comparing hashed values of the key (STD::HASH returns a SIZE_T value)
			if (std::hash<Key>(new_pair->key_) > std::hash<Key>(head_node->data.key_))
			{
				head_node->right = insert_recursively(std::move(new_pair), head_node->right);
			}
			//when head is not null search path to be insert in BTS left
			else if (std::hash<Key>(new_pair->key_) < std::hash<Key>(head_node->data.key_))
			{
				head_node->left = insert_recursively(std::move(new_pair), head_node->left);
			}
			//default
			return head_node;
		}
		
		//search node
		bool search_recursively(const Key& key, _NODE_* head_node)
		{
			//base case
			if (head_node == nullptr) return false;
			//when hashed key are equals
			if (std::hash<Key>(key) == std::hash<Key>(head_node->data.key_)) return true;
			//search path left or right
			bool temp;
			if (std::hash<Key>(key) > std::hash<Key>(head_node->data_.key_)) temp = search_recursively(key, head_node->right);
			else temp = search_recursively(key, head_node->left);
			//return temp
			return temp;
		}
		
		//rotations
		void rotate_left(_NODE_*& root, _NODE_*& parent_x)
		{
			//temp T2
			_NODE_* temp{ parent_x->right };
			//right point to node_x (X)
			parent_x->right = temp->left;
			//connect parent right to parent_x (P)
			if (parent_x->right != nullptr) parent_x->right->parent_ = parent_x;
			//
			temp->parent_ = parent_x->parent_;
			//
			if (parent_x->parent_ == nullptr) root = temp;

			else if (parent_x == parent_x->parent_->left) parent_x->parent_->left = temp;

			else parent_x->parent_->right = temp;

			temp->left = parent_x;

			parent_x->parent_ = temp;
		}
		
		void rotate_right(_NODE_*& root, _NODE_*& parent_x)
		{
			_NODE_* temp{ parent_x->left };

			parent_x->left = temp->right;

			if (parent_x->left != nullptr) parent_x->left->parent_ = parent_x;

			temp->parent_ = parent_x->parent_;

			if (parent_x->parent == nullptr)
				root = temp;

			else if (parent_x == parent_x->parent->left)
				parent_x->parent->left = temp;

			else
				parent_x->parent->right = temp;

			temp->right = parent_x;
			parent_x->parent = temp;
		}
		
	public:
		//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		//																				CONSTRUCTORS
		//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		tree_map() : root_{ nullptr }, length_{ 0 } {}
		explicit tree_map(Pair&& r_pair ) : root_{ new _NODE_{ std::move(r_pair) } }, length_{ 1 } {}

		explicit tree_map(const Pair& l_pair) : root_{ new _NODE_{ l_pair } }, length_{ 1 } {}

		explicit tree_map(Key&& r_key, Value&& r_value) : length_{ 1 }
		{
			//create a new pair and wrap it in a red black node
			root_ = new _NODE_{ pair<Key, Value>{ std::move(r_key), std::move(r_value) } };
		}
		//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		//																			PUBLIC METHOD MEMBERS
		//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		//insert data a new node
		/*
				
													   INSERT NODE
													+-+-----------+-+
												-----o| root_tree |o------
											   /    +-+-----------+-+     \
											  /                            \
									   +-+------+-+					     +-+------+-+
									 ---o| node |o---                  ---o| node |o---
									/  +-+------+-+  \                /  +-+------+-+  \
								   /                  \              /                  \
							 +-+------+-+			   \            NULL                 NULL
						   ---o| node |o--              \
						  /  +-+------+-+ \			+-+------+-+
						 /                 \	  ---o| NEW! |o---
					 NULL				  NULL   /  +-+------+-+  \
												/                  \
											 NULL				   NULL
					1) Inserts depending the value of the Key, maintains the Binary Search Trees Law (lesser, bigger)
					2) Uses > and < to compare between data, if an object is implemented in the structure must override < and > operators
					3) Complexity of insertion Big-oh(log n) when the tree is balanced
		*/
		tree_map(const _RB_TREE_& copy);
		tree_map(_RB_TREE_&& r_tree);
		//----------------------------------
		//		PUBLIC METHOD MEMBERS
		//----------------------------------

		//make pair insertion
		bool add(const Pair& data)
		{
			if (!search_recursively(data.key_, root_))
			{
				root_ = insert_recursively(data, root_);
				return true;
			}
			//return false pair is already in the map
			return false;
		}
		
		bool add(Pair&& r_ref)
		{
			if (!search_recursively(r_ref.key_, root_))
			{
				root_ = insert_recursively(std::move(r_ref), root_);
				//fix insertion violation
				return true;
			}
			return false;
		}

		//insert  no pair R values
		bool add(Key&& r_key, Value&& r_val)
		{
			if (!search_recursively(r_key, root_))
			{
				root_ = insert_recursively(std::move(pair<Key, Value>{ std::move(r_key), std::move(r_val) }));
				length_++;
				return  true;
			}
			return false;
		}
		
		bool add(Pair* pointer)
		{
			return add(*pointer);
		}

		//remove in the Tree
		bool remove(Pair& data);
		bool remove(Pair&& r_ref);
		bool remove(Pair* pointer);
		//clear set, is empty?
		bool empty();
		
		bool is_empty() const
		{
			return length_ == 0;
		}
		
		//getters
		size_t size() const
		{
			return length_;
		}
		
		//operator overloading
		tree_map& operator=(const _RB_TREE_& copy);
		tree_map& operator=(_RB_TREE_&& r_tree) noexcept;

		//----------------------------------
		//				DESTRUCTOR
		//----------------------------------
		~tree_map();
	};
}

