/*
------------------------------------------------------------------------------------------
							HEADER:       FUNCTIONAL.H
------------------------------------------------------------------------------------------
 Summary:		Associative structure AVL tree

 Authors:		Mateo Terselich

 Started:		3 December 2018

 Collections:	1) STRUCT PAIR
*/
//defines
#pragma once
//includes
#include <utility>

namespace dt
{
	template <class Key, class Value> struct pair
	{
		//friend class
		template<class Type> friend class rb_node;
		template<class K, class V> friend class tree_map;
		//make pair objects
		static pair& make_pair(Key&& r_k_value, Value&& r_v_value)
		{

			//return pair
			return std::move(pair{ std::move(r_k_value), std::move(r_v_value) });
		}
		static pair& make_pair(const Key& k, const Value& v)
		{
			return std::move(pair{ k, v });
		}
		//destructor
		~pair(){ /*destroys here*/ }
	private:
		//member variables private and private
		Key key_;
		Value value_;
		//private constructors
		pair(const Key& k, const Value& v) : key_{ k }, value_{ v } {}
		pair(Key&& r_k_value, Value&& r_v_value) : key_{ std::move(r_k_value) }, value_{ r_v_value } {}
		
	};
}

