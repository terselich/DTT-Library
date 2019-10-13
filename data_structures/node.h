/*
------------------------------------------------------------------------------------------
							HEADER:       NODE.H
------------------------------------------------------------------------------------------
 Summary:		Helper to build linked_list

 Authors:		Mateo Terselich

 Started:		29 April 2018

 Collections:	1) NODE (Private class)

*/
//definitions
#pragma once
//include
#include <utility>

namespace dt
{
	template <class T> class node
	{
		//friend classes
		template<class C> friend class linked_list;
		template<class C> friend class queue;
		template<class C> friend class stack;
		
		//-----------------------------------------------------------------------------------------
		//											DATA MEMBERS
		//-----------------------------------------------------------------------------------------
		/*
				  node
				+-----+-+
				| key |o---->NULL
				+-----+-+
		*/
		T key_;
		//public next pointer of node
		node<T>* next{ nullptr };
		
		//-----------------------------------------------------------------------------------------
		//											CONSTRUCTORS
		//-----------------------------------------------------------------------------------------

		//private, only linked_list can create nodes
		explicit node(T&& r_ref) noexcept : key_{ std::move(r_ref) } {}
		
		explicit node(const T& data) : key_{ data } {}
		
		explicit node(const T* data) : node(*data) {}

		//copy constructor
		node(const node<T>& source) : key_{ source.key_ } {}

		//move constructor
		node(node<T>&& source) noexcept : key_{ source.key_ }, next{ source.next }
		{
			//pointer dangling
			if (source.next != nullptr) source.next = nullptr;
		}
		
		//-----------------------------------------------------------------------------------------
		//										PRIVATE METHOD MEMBERS
		//-----------------------------------------------------------------------------------------

		//Operator assignment copy equals
		node<T>& operator=(const node<T>& source)
		{
			//self assignment
			if (&source == this) return *this;
			//key_ copy
			key_ = source.key_;
			return *this;
		}
		
		//move node object
		node<T>& operator=(node<T>&& data) noexcept
		{
			//self assignment
			if (&data == this) return *this;
			//move or change ownership
			key_ = data.key_;
			return *this;
		}

		//-----------------------------------------------------------------------------------------
		//											DESTRUCTOR
		//-----------------------------------------------------------------------------------------
		
		~node()
		{
			//next points to NULL
			next = nullptr;
		}
	};
}


