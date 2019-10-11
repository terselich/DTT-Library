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
// ReSharper disable once CppUnusedIncludeDirective
#include "pch.h"
#include "doubly_node.h"
#include <queue>

namespace dt
{
	
	template <class Data_type = int> class tree_set
	{
		using _NODE_ = doubly_node<Data_type>;
		using _AVL_ = tree_set<Data_type>;
		
		//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		//																					 DATA MEMBERS
		//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		//_head of the Tree-set, size MEMBER VARIABLES

		_NODE_* root_;
		int length_;
		
		//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		//																				RECURSIVE PRIVATE METHODS
		//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!RECURSION!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

		_NODE_* insert_recursively(const Data_type& new_, _NODE_ * source_)
		{
			//when node of the tree is node return new node
			if (source_ == nullptr)
			{
				source_ = new _NODE_{ new_ };
				length_++;
				return source_;
			}
			//when data value is less than the parent value
			if (new_ < source_->data_)
			{
				source_->left = insert_recursively(new_, source_->left);
			}
			//when data is more than parent value
			else if (new_ > source_->data_)
			{
				source_->right = insert_recursively(new_, source_->right);
			}
			//get balance of heights left and right
			const int balance = get_balance(source_);
			//balance tree value, if balance more than 1, each rotation case
			if (balance > 1 && new_ < source_->left->data_) return right_rotate(source_);
			// Right-right Case  
			if (balance < -1 && new_ > source_->right->data_) return left_rotate(source_);
			// Left-right Case  
			if (balance > 1 && new_ > source_->left->data_)
			{
				source_->left = left_rotate(source_->left);
				return right_rotate(source_);
			}
			// Right-left Case  
			if (balance < -1 && new_ < source_->right->data_)
			{
				source_->right = right_rotate(source_->right);
				return left_rotate(source_);
			}
			//return statement
			return source_;
		}
		
		//get balance for factor of node 
		int get_balance(const _NODE_* head_node)
		{
			//get balance of left and right sources
			const int balance_left = depth_recursively(head_node->left);
			const int balance_right = depth_recursively(head_node->right);
			//return difference
			return balance_left - balance_right;
		}
		
		//get height of a given node
		int depth_recursively(const _NODE_* source)
		{
			//base case
			if (source == nullptr)
				return 0;
			//recursive calls left node and right node else...
			const int left_depth = depth_recursively(source->left);
			const int right_depth = depth_recursively(source->right);
			//returns which one has more depth adding one
			if (left_depth > right_depth) return left_depth + 1;
			return right_depth + 1;	//else..
		}
		
		//search a value in the tree
		bool search_recursively(const Data_type& data, _NODE_* source)
		{
			//base case when node is null
			if (source == nullptr)
			{
				return false;
			}
			//when the data value is equal
			if (source->data_ == data) return true;	//return true
			bool temp;
			if (data > source->data_) temp = search_recursively(data, source->right); //look on the right for data more than
			else temp = search_recursively(data, source->left); //look on the left for data less than
			return temp;
		}

		//delete tree
		_NODE_* delete_tree(_NODE_* source)
		{
			if (source == nullptr)
				return nullptr;
			//delete left and the right subtrees
			source->left = delete_tree(source->left);
			source->right = delete_tree(source->right);
			//delete
			delete source;
			return nullptr;
		}

		//delete node given
		_NODE_* delete_node_recursive(Data_type to_delete, _NODE_* source)
		{
			//This process is performed with 2 steps (Standard BST deletion and then AVL balancing)
			//----------------------------------------------------------------------------------------
			// STEP 1: PERFORM STANDARD BST DELETE
			if (source == nullptr)
				return source;
			// If the node key to be deleted is smaller move left
			if (to_delete < source->data_)
				source->left = delete_node_recursive(to_delete, source->left);
			// If the node key to be deleted is greater
			else if (to_delete > source->data_)
				source->right = delete_node_recursive(to_delete, source->right);
			//to be deleted by default equality, else if ( to_delete == source)
			else if (to_delete == source->data_)
			{
				// node with only one child or no child
				if ((source->left == nullptr) || (source->right == nullptr))
				{
					//for either one (left or right node) is not NULL
					_NODE_* temp = source->left ? source->left : source->right;
					//No child case
					if (temp == nullptr)
					{
						delete source;
						return nullptr;
					}//else... both are null
					// Copy the in order successor's data to this node and assign null pointers
					source->data_ = std::move(temp->data_);
					delete temp;
					temp = nullptr;
					source->right = nullptr;
					source->left = nullptr;
					// Delete the in order successor
					return source;
				}
				// else ..more than one child case
				// node with two children (smallest in the right subtree)
				Data_type temp = min_node(source->right)->data_;
				// Copy the in order successor's data to this node
				source->set_key(temp);
				// Delete the in order successor
				source->right = delete_node_recursive(temp, source->right);
			}
			else return source;
			//-----------------------------------------------------------------------------------------
			// STEP 2: GET THE BALANCE
			const int balance{ get_balance(source) };
			// If this node becomes unbalanced, then there are 4 cases
			// Left-Left Case
			if (balance > 1 && get_balance(source->left) >= 0) return right_rotate(source);
			// Right-Right Case
			if (balance < -1 && get_balance(source->right) <= 0) return left_rotate(source);
			// Left-Right Case
			if (balance > 1 && get_balance(source->left) < 0)
			{
				source->left = left_rotate(source->left);
				return right_rotate(source);
			}
			// Right-Left Case
			if (balance < -1 && get_balance(source->right) > 0)
			{
				source->right = right_rotate(source->right);
				return left_rotate(source);
			}
			return source;
		}

		/*
						   T1, T2, T3 and T4 are subtrees.
					 z                                      y
					/ \                                   /   \
				   y   T4      Right Rotate (z)          x      z
				  / \          - - - - - - - - ->      /  \    /  \
				 x   T3                               T1  T2  T3  T4
				/ \
			  T1   T2
		*/
		//AVL rotations
		_NODE_* right_rotate(_NODE_* y)
		{
			//x initialization and pointing to y left node
			auto* x{ y->left };
			//T2 pointing to x right now
			auto* t2{ x->right };
			// Perform rotation
			x->right = y;
			y->left = t2;
			// Return new root_  
			return x;
		}
		
		_NODE_* left_rotate(_NODE_* x)
		{
			//y initialization and pointing to x right node
			auto* y{ x->right };
			//T2 pointing to y left now
			auto* t2{ y->left };
			//Perform rotation
			y->left = x;
			x->right = t2;
			// Return new root_  
			return y;
		}

		//min node in the subtree-tree
		_NODE_* min_node(_NODE_* head_node)
		{
			//temp traverse
			auto* traverse{ head_node };
			//loop until finds NULL, moving to left,, like traversing a LinkedList
			while (traverse->left != nullptr)
			{
				traverse = traverse->left;
			}
			//return traverse
			return traverse;
		}
		
	//public part
	public:
		
		//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		//																				CONSTRUCTORS
		//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		//constructors
		/*
				CONSTRUCTOR WITH A NEW OBJECT AS A PARAMETER
							+-+------+-+
						-----o| root_ |o-----
					   /    +-+------+-+    \
					  /                      \
					 /                        \
				   NULL						 NULL
		*/
		tree_set() : root_{ nullptr }, length_{ 0 } {}

		explicit tree_set(Data_type&& r_ref) : length_{ 1 }
		{
			//move to heap..
			root_ = new _NODE_{ std::move(r_ref) };
		}
		
		explicit tree_set(const Data_type& data) : root_{ new _NODE_{ data } }, length_{ 1 } {}
		
		tree_set(const _AVL_& copy)
		{
			std::queue<_NODE_*> q;
			auto* temp{ copy.root_ };
			q.push(temp);
			//while the q is not empty add values left and right and pop them
			while (q.empty() == false)
			{
				//update temp
				temp = q.front();
				//add value of the queue copying data of node
				this->add(q.front()->data_);
				q.pop();
				//add to the queue left and right
				if (temp->left != nullptr) q.push(temp->left);
				if (temp->right != nullptr) q.push(temp->right);
			}
		}
		
		tree_set(_AVL_&& r_set) noexcept : root_{ r_set.root_ }, length_{ r_set.size() }
		{
			//pointer dangling
			r_set.root_ = nullptr;
		}
		
		//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		//																			PUBLIC METHOD MEMBERS
		//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		//insert data a new node
		/*

											INSERT NODE
											+-+------+-+
										-----o| root_ |o-----
									   /    +-+------+-+    \
									  /                      \
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
		
		//insert data in the tree_set
		bool add(const Data_type& data)
		{
			//calling recursive method
			if (!search_recursively(data, root_))
			{
				root_ = insert_recursively(data, root_);
				return true;
			}
			return false;
		}
		
		bool add(Data_type&& r_ref)
		{
			//calling recursive method
			if (!search_recursively(r_ref, root_))
			{
				root_ = insert_recursively(std::move(r_ref), root_);
				return true;
			}
			return false;
		}
		
		bool add(Data_type* pointer)
		{
			//copy data that is pointed and pass it s new pointer
			return add(*pointer);
		}
		
		//search for a value in the TREE SET and remove it
		 bool remove(Data_type& data)
		{
			if (search_recursively(data, root_))
			{
				//delete, decrease length and return true
				root_ = delete_node_recursive(data, root_);
				--length_;
				return true;
			}
			return false;
		}
		
		bool remove(Data_type&& r_ref)
		{
			if (search_recursively(r_ref, root_))
			{
				root_ = delete_node_recursive(std::move(r_ref), root_);
				--length_;
				return true;
			}
			return false;
		}
		
		bool remove(Data_type* pointer)
		{
			return remove(*pointer);
		}
		
		//clear set, is empty? clears the TREE SET deleting every node
		bool empty()
		{
			if (is_empty()) return false;
			//call recursive delete
			root_ = delete_tree(root_);
			//free root_
			length_ = 0;
			return true;

		}
		
		bool is_empty()
		{
			//if root is null, no elements in the tree
			return root_ == nullptr;
		}
		
		//getters
		int size() const
		{
			return length_;
		}
		
		//operator overloading
		auto operator=(const _AVL_& set) -> tree_set&
		{
			if (&set == this) return *this;
			//copy tree
			if (set.root_ == nullptr)
			{
				root_ = nullptr;
				length_ = 0;
				return *this;
			}
			//delete current
			this->empty();
			//empty queue list
			std::queue<_NODE_*> q;
			auto* temp{ set.root_ };
			q.push(temp);
			//while the q is not empty add values left and right and pop them
			while (q.empty() == false)
			{
				//update temp
				temp = q.front();
				//add value of the queue copying data of node
				this->add(q.front()->data_);
				q.pop();
				//add to the queue left and right
				if (temp->left != nullptr) q.push(temp->left);
				if (temp->right != nullptr) q.push(temp->right);
			}
			return *this;
		}
		
		//move assignment operator
		auto operator=(_AVL_&& r_set) noexcept -> tree_set&
		{
			//avoid self assignment
			if (&r_set == this) return *this;
			//delete
			if (root_ != nullptr) this->empty();
			//transfer ownership
			root_ = r_set.root_;
			return *this;
		}

		//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		//																					DESTRUCTOR
		//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		~tree_set()
		{
			//call recursive delete
			while (this->empty());
		}
	};
}
