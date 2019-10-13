/*
------------------------------------------------------------------------------------------
							HEADER:       DOUBLY_NODE.H
------------------------------------------------------------------------------------------
 Summary:		Helper to build doubly_list 

 Authors:		Mateo Terselich

 Started:		30 April 2018

 Collections:	1) DOUBLY_NODE (Private class)
*/
//definitions
#pragma once
//includes
#include <utility>

namespace  dt
{
	template<class E> class doubly_node
	{
	//proteceted
	protected:
		
		template<class S> friend class doubly_list;
		template<class S> friend class tree_set;
		template<class K, class C> friend class tree_map;
		
		//-----------------------------------------------------------------------------------------
		//											DATA MEMBERS
		//-----------------------------------------------------------------------------------------
		/*
						NODE
					+-+-----+-+
			NULL<----o| key |o---->NULL
					+-+-----+-+
		*/
		E data_;
		doubly_node<E>* left{ nullptr }, * right{ nullptr };
		
		//-----------------------------------------------------------------------------------------
		//											CONSTRUCTORS
		//-----------------------------------------------------------------------------------------
		
		//private constructors only friend classes can instantiate it
		explicit doubly_node(E&& r_ref) noexcept : data_{ std::move(r_ref) } {}
		
		explicit doubly_node(const E& data) : data_{ data } {}
		
		explicit doubly_node(const E* data) : doubly_node(&data) {}
		
		//copy constructor
		doubly_node(const doubly_node<E>& source) : data_{ source.data_ } {}
		
		//move constructor
		doubly_node(doubly_node<E>&& r_ref) noexcept : data_{ r_ref.data_ }, left{ r_ref.left }, right{ r_ref.right }
		{
			//pointer dangling
			if (r_ref.left != nullptr) r_ref.left = nullptr;
			if (r_ref.right != nullptr) r_ref.right = nullptr;
		}
		
		//-----------------------------------------------------------------------------------------
		//										PRIVATE METHOD MEMBERS
		//-----------------------------------------------------------------------------------------

		doubly_node<E>& operator=(const E& value)
		{
			data_ = value;
			return *this;
		}

		doubly_node<E>& operator=(const doubly_node<E>& copy)
		{
			//self assignment
			if (&copy == this) return *this;
			//key copy
			data_ = copy.data_;
			return *this;
		}

		doubly_node<E>& operator=(doubly_node<E>&& r_ref) noexcept
		{
			//self assignment
			if (&r_ref == this) return *this;
			//move or change ownership
			data_ = r_ref.data_;
			return *this;
		}

		doubly_node<E>& operator=(E&& data)
		{
			//self assignment
			if (&data == this) return *this;
			//else..
			data_ = data;
			return *this;
		}

		//-----------------------------------------------------------------------------------------
		//											DESTRUCTOR
		//-----------------------------------------------------------------------------------------
		
		~doubly_node()
		{
			//next points to NULL
			left = nullptr;
			right = nullptr;
		}
	};
}
