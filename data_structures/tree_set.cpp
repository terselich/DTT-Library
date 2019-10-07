#include "pch.h"
#include "tree_set.h"
#include "line.h"

namespace dt
{
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//																				RECURSIVE PRIVATE METHODS
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//inserting node L value ref
	template<class C> doubly_node<C>* tree_set<C>::insert_recursively(const C& new_node, doubly_node<C>* head_node)
	{
		//when node of the tree is node return new node
		if (head_node == nullptr)
		{
			head_node = new doubly_node<C>{ new_node };
			length_tree++;
			return head_node;
		}
		//when data value is less than the parent value
		if (new_node < head_node->key_)
		{
			head_node->left = insert_recursively(new_node, head_node->left);
		}
		//when data is more than parent value
		else if (new_node > head_node->key_)
		{
			head_node->right = insert_recursively(new_node, head_node->right);
		}
		//get balance of heights left and right
		const int balance = get_balance(head_node);
		//balance tree value, if balance more than 1, each rotation case
		if (balance > 1 && new_node < head_node->left->key_) return right_rotate(head_node);
		// Right-right Case  
		if (balance < -1 && new_node > head_node->right->key_) return left_rotate(head_node);
		// Left-right Case  
		if (balance > 1 && new_node > head_node->left->key_)
		{
			head_node->left = left_rotate(head_node->left);
			return right_rotate(head_node);
		}
		// Right-left Case  
		if (balance < -1 && new_node < head_node->right->key_)
		{
			head_node->right = right_rotate(head_node->right);
			return left_rotate(head_node);
		}
		//return statement
		return head_node;
	}
	//max depth recursively
	template<class C> int tree_set<C>::depth_recursively(const doubly_node<C>* head_node)
	{
		//base case
		if (head_node == nullptr)
			return 0;
		//recursive calls left node and right node else...
		const int left_depth = depth_recursively(head_node->left);
		const int right_depth = depth_recursively(head_node->right);
		//returns which one has more depth adding one
		if (left_depth > right_depth) return left_depth + 1;
		return right_depth + 1;	//else..
	}
	//search in the tree
	template<class C> bool tree_set<C>::search_recursively(const C& data, doubly_node<C>* head_node)
	{
		//base case when node is null
		if (head_node == nullptr)
		{
			return false;
		}
		//when the data value is equal
		if (head_node->key_ == data) return true;	//return true
		bool temp;
		if (data > head_node->key_) temp = search_recursively(data, head_node->right); //look on the right for data more than
		else temp = search_recursively(data, head_node->left); //look on the left for data less than
		return temp;
	}
	//delete tree
	template<class C> doubly_node<C>* tree_set<C>::delete_tree(doubly_node<C>* head_node)
	{
		if (head_node == nullptr)
			return nullptr;
		//delete left and the right subtrees
		head_node->left = delete_tree(head_node->left);
		head_node->right = delete_tree(head_node->right);
		//delete
		delete head_node;
		return nullptr;
	}
	//get balance of the tree
	template<class C> int tree_set<C>::get_balance(const doubly_node<C>* head_node)
	{
		//get balance of left and right sources
		const int balance_left = depth_recursively(head_node->left);
		const int balance_right = depth_recursively(head_node->right);
		//return difference
		return balance_left - balance_right;
	}
	//delete node given
	template<class C> doubly_node<C>* tree_set<C>::delete_node_recursive(C to_delete, doubly_node<C>* head_node)
	{
		//This process is performed with 2 steps (Standard BST deletion and then AVL balancing)
		//----------------------------------------------------------------------------------------
		// STEP 1: PERFORM STANDARD BST DELETE
		if (head_node == nullptr)
			return head_node;
		// If the node key to be deleted is smaller move left
		if (to_delete < head_node->key_)
			head_node->left = delete_node_recursive(to_delete, head_node->left);
		// If the node key to be deleted is greater
		else if (to_delete > head_node->key_)
			head_node->right = delete_node_recursive(to_delete, head_node->right);
		//to be deleted by default equality, else if ( to_delete == head_node)
		else if (to_delete == head_node->key_)
		{
			// node with only one child or no child
			if ((head_node->left == nullptr) || (head_node->right == nullptr))
			{
				//for either one (left or right node) is not NULL
				doubly_node<C>* temp = head_node->left ? head_node->left : head_node->right;
				//No child case
				if (temp == nullptr)
				{
					delete head_node;
					return nullptr;
				}//else... both are null
				// Copy the in order successor's data to this node and assign null pointers
				head_node->key_ = std::move(temp->key_);
				delete temp;
				temp = nullptr;
				head_node->right = nullptr;
				head_node->left = nullptr;
				// Delete the in order successor
				return head_node;
			}
			// else ..more than one child case
			// node with two children (smallest in the right subtree)
			doubly_node<C>* temp = min_node(head_node->right);
			// Copy the in order successor's data to this node
			head_node->set_key(temp->key_);
			// Delete the in order successor
			head_node->right = delete_node_recursive(temp, head_node->right);
		}
		else return head_node;
		//-----------------------------------------------------------------------------------------
		// STEP 2: GET THE BALANCE
		const int balance{ get_balance(head_node) };
		// If this node becomes unbalanced, then there are 4 cases
		// Left-Left Case
		if (balance > 1 && get_balance(head_node->left) >= 0) return right_rotate(head_node);
		// Right-Right Case
		if (balance < -1 && get_balance(head_node->right) <= 0) return left_rotate(head_node);
		// Left-Right Case
		if (balance > 1 && get_balance(head_node->left) < 0)
		{
			head_node->left = left_rotate(head_node->left);
			return right_rotate(head_node);
		}
		// Right-Left Case
		if (balance < -1 && get_balance(head_node->right) > 0)
		{
			head_node->right = right_rotate(head_node->right);
			return left_rotate(head_node);
		}
		return head_node;
	}
	//balancing tree methods
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
	template<class C> doubly_node<C>* tree_set<C>::left_rotate(doubly_node<C>* x)
	{
		//y initialization and pointing to x right node
		auto* y{ x->right };
		//T2 pointing to y left now
		auto* t2{ y->left };
		//Perform rotation
		y->left = x;
		x->right = t2;
		// Return new root_tree  
		return y;
	}
	template<class C> doubly_node<C>* tree_set<C>::min_node(doubly_node<C>* head_node)
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
	template<class C> doubly_node<C>* tree_set<C>::right_rotate(doubly_node<C>* y)
	{
		//x initialization and pointing to y left node
		auto* x{ y->left };
		//T2 pointing to x right now
		auto* t2{ x->right };
		// Perform rotation
		x->right = y;
		y->left = t2;
		// Return new root_tree  
		return x;
	}
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//																				CONSTRUCTORS
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//constructors
	/*
			CONSTRUCTOR WITH A NEW OBJECT AS A PARAMETER
						+-+------+-+
					-----o| root_tree |o-----
				   /    +-+------+-+    \
				  /                      \
				 /                        \
			   NULL						 NULL
	*/
	template<class C> tree_set<C>::tree_set() : root_tree{ nullptr }, length_tree{ 0 } {}
	template<class C> tree_set<C>::tree_set(C&& r_ref) : length_tree{ 1 }
	{
		//move to heap..
		root_tree = new doubly_node<C>{ std::move(r_ref) };
	}
	template<class C> tree_set<C>::tree_set(const C& data) : root_tree{ new doubly_node<C>{ data } }, length_tree{ 1 } {}
	template<class C> tree_set<C>::tree_set(const tree_set<C>& copy) : length_tree{ copy.size() }
	{
		line<doubly_node<C>*> q;
		auto* temp{ copy.root_tree };
		q.push(temp);
		//while the q is not empty add values left and right and pop them
		while (q.is_empty() == false)
		{
			//update temp
			temp = q.next();
			//add value of the queue
			this->add(q.next());
			//point to null prevent deletion
			temp = nullptr;
			//poll temp
			q.poll();
			//add to the queue left and right
			if (temp->left != nullptr) q.push(temp->left);
			if (temp->right != nullptr) q.push(temp->right);
		}
	}
	template<class C>tree_set<C>::tree_set(tree_set<C>&& r_set) noexcept : root_tree{ r_set.root_tree }, length_tree{ r_set.size() }
	{
		//pointer dangling
		r_set.root_tree = nullptr;
	}

	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//																			PUBLIC METHOD MEMBERS
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//insert data a new node
	/*

										INSERT NODE
										+-+------+-+
									-----o| root_tree |o-----
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
	template<class C> bool tree_set<C>::add(const C& data)
	{
		//calling recursive method
		if (!search_recursively(data, root_tree))
		{
			root_tree = insert_recursively(data, root_tree);
			return true;
		}
		return false;
	}
	template<class C> bool tree_set<C>::add(C&& r_ref)
	{
		//calling recursive method
		if (!search_recursively(r_ref, root_tree))
		{
			root_tree = insert_recursively(r_ref, root_tree);
			return true;
		}
		return false;
	}
	template<class C> bool tree_set<C>::add(C* pointer)
	{
		//copy data that is pointed and pass it s new pointer
		return add(*pointer);
	}
	//search for a value in the TREE SET and remove it
	template<class C> bool tree_set<C>::remove(C& data)
	{
		if (search_recursively(data, root_tree))
		{
			root_tree = delete_node_recursive(data, root_tree);
			--length_tree;
			return true;
		}
		return false;
	}
	template<class C> bool tree_set<C>::remove(C&& r_ref)
	{
		if (search_recursively(r_ref, root_tree))
		{
			root_tree = delete_node_recursive(std::move(r_ref), root_tree);
			--length_tree;
			return true;
		}
		return false;
	}
	template<class C> bool tree_set<C>::remove(C* pointer)
	{
		return remove(*pointer);
	}
	//clears the TREE SET deleting every node
	template<class C> bool tree_set<C>::empty()
	{
		if (is_empty()) return false;
		//call recursive delete
		root_tree = delete_tree(root_tree);
		//free root_tree
		length_tree = 0;
		return true;

	}
	//check if the TREE SET is empty
	template<class C> bool tree_set<C>::is_empty()
	{
		return root_tree == nullptr;
	}
	//getter of size of tree_set
	template<class C> unsigned int tree_set<C>::size() const
	{
		return length_tree;
	}
	template<class C> tree_set<C>& tree_set<C>::operator=(const tree_set<C>& set)
	{
		if (&set == *this) return *this;
		//copy tree
		if (set.root_tree == nullptr)
		{
			root_tree = nullptr;
			length_tree = 0;
			return *this;
		}
		//delete current
		delete this;
		//empty queue list
		line<doubly_node<C>*> q;
		auto* temp{ set.root_tree };
		q.push(temp);
		//while the q is not empty add values left and right and pop them
		while (q.is_empty() == false)
		{
			//update temp
			temp = q.next();
			//add value of the queue
			this->add(q.next());
			q.poll();
			//add to the queue left and right
			if (temp->left != nullptr) q.push(temp->left);
			if (temp->right != nullptr) q.push(temp->right);
		}
		return *this;
	}
	template<class C> tree_set<C>& tree_set<C>::operator=(tree_set<C>&& r_set) noexcept
	{
		//avoid self assignment
		if (&r_set == this) return *this;
		//delete
		if (root_tree != nullptr) delete this;
		//transfer ownership
		root_tree = r_set.root_tree;
		return *this;
	}
	template<class C>
	tree_set<C>& tree_set<C>::operator=(C&& r_value)
	{
		if (r_value == *(this)->root_tree) return *this;
		if (root_tree != nullptr) delete this;
		//transfer ownership
		root_tree = new doubly_node<C>{ std::move(r_value) };
		length_tree = 1;
		return *this;
	}
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//																					DESTRUCTOR
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	template<class C> tree_set<C>::~tree_set()
	{
		//call recursive delete
		while (empty());
	}

}
