#include "pch.h"
#include "tree_map.h"

namespace dt
{
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//																				RECURSIVE PRIVATE METHODS
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//insert l value
	template<class Key, class Value> rb_node<pair<Key, Value>>* tree_map<Key, Value>::insert_recursively(const Pair& new_pair, rb_node<Pair>* head_node)
	{
		//base case
		if(head_node == nullptr)
		{
			head_node = new rb_node<Pair>{ new_pair };
			length_++;
			return head_node;
		}
		//when head is not null search path to be insert in BTS right comparing hashed values of the key (STD::HASH returns a SIZE_T value)
		if (std::hash<Key>(new_pair->key_) > std::hash<Key>(head_node->data.key_))
		{
			head_node->right = insert_recursively(new_pair, head_node->right);
		}
		//when head is not null search path to be insert in BTS left
		else if (std::hash<Key>(new_pair->key_) < std::hash<Key>(head_node->data.key_))
		{
			head_node->left = insert_recursively(new_pair, head_node->left);
		}
		//default
		return head_node;
	}
	//insert r value
	template<class Key, class Value> rb_node<pair<Key, Value>>* tree_map<Key, Value>::insert_recursively(Pair&& new_pair, rb_node<Pair>* head_node)
	{
		//base case
		if (head_node == nullptr)
		{
			head_node = new rb_node<Pair>{ std::move(new_pair) };
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
	
	template<class Key, class Value> bool tree_map<Key, Value>::search_recursively(const Key& key, rb_node<Pair>* head_node)
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
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//																				CONSTRUCTORS
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	template<class Key, class Value> tree_map<Key, Value>::tree_map() : root_{ nullptr }, length_{ 0 } {}
	//r value Pair constructor
	template<class Key, class Value> tree_map<Key, Value>::tree_map(Pair&& r_pair) : root_{ new doubly_node<Pair>{ std::move(r_pair) } }, length_{ 1 } {}
	//l value Pair constructor
	template<class Key, class Value> tree_map<Key, Value>::tree_map(const Pair& l_pair) : root_{ new doubly_node<Pair>{ l_pair } }, length_{ 1 } {}
	//make pair
	template<class Key, class Value> tree_map<Key, Value>::tree_map(Key&& r_key, Value&& r_value) : length_{ 1 }
	{
		//create a new pair and wrap it in a red black node
		root_ = new rb_node<Pair>{ pair<Key, Value>{ std::move(r_key), std::move(r_value) } };
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
	template<class Key, class Value> bool tree_map<Key, Value>::add(const Pair& data)
	{
		if(!search_recursively(data.key_, root_))
		{
			root_ = insert_recursively(data, root_);
			return true;
		}
		//return false pair is already in the map
		return false;
	}
	template<class Key, class Value> bool tree_map<Key, Value>::add(Pair&& r_ref)
	{
		if(!search_recursively(r_ref.key_, root_))
		{
			root_ = insert_recursively(std::move(r_ref), root_);
			return true;
		}
		return false;
	}
}
