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
	protected:
		template<class S> friend class doubly_list;
		template<class S> friend class tree_set;
		template<class K, class C> friend class tree_map;
		//----------------------------------
		//			DATA MEMBERS
		//----------------------------------
		/*
						NODE
					+-+-----+-+
			NULL<----o| key |o---->NULL
					+-+-----+-+
		*/
		E data_;
		//----------------------------------
		//				CONSTRUCTORS
		//----------------------------------
		//private constructors only friend classes can instantiate it
		explicit doubly_node(E&& r_ref) noexcept : data_{ std::move(r_ref) } {}
		explicit doubly_node(const E& data) : data_{ data } {}
		explicit doubly_node(const E* data) : doubly_node(&data) {}
	public:
		//public member variables
		doubly_node<E>* left{ nullptr }, * right{ nullptr };
		//copy constructor
		doubly_node(const doubly_node<E>& ref) : data_{ ref.get_key() } {}
		//move constructor
		doubly_node(doubly_node<E>&& r_ref) noexcept : data_{ r_ref.get_key() }, left{ r_ref.left }, right{ r_ref.right }
		{
			//pointer dangling
			if (r_ref.left != nullptr) r_ref.left = nullptr;
			if (r_ref.right != nullptr) r_ref.right = nullptr;
		}
		//----------------------------------
		//		PUBLIC METHOD MEMBERS
		//----------------------------------
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
			data_ = copy.get_key();
			return *this;
		}

		doubly_node<E>& operator=(doubly_node<E>&& data) noexcept
		{
			//self assignment
			if (&data == this) return *this;
			//move or change ownership
			data_ = data.get_key();
			return *this;
		}

		doubly_node<E>& operator=(E&& data)
		{
			data_ = data;
			return *this;
		}

		friend bool operator==(doubly_node<E>& a, doubly_node<E>& b)
		{
			return a.get_key() == b.get_key();
		}

		friend bool operator!=(doubly_node<E>& a, doubly_node<E>& b)
		{
			return !(a == b);
		}

		friend bool operator>(doubly_node<E>& a, doubly_node<E>& b)
		{
			return a.get_key() > b.get_key();
		}

		friend bool operator>=(doubly_node<E>& a, doubly_node<E>& b)
		{
			return a.get_key() >= b.get_key();
		}

		friend bool operator<(doubly_node<E>& a, doubly_node<E>& b)
		{
			return !(a > b);
		}

		friend bool operator<=(doubly_node<E>& a, doubly_node<E>& b)
		{
			return a.get_key() <= b.get_key();
		}

		//getter and setter
		const E& get_key() const
		{
			return data_;
		}
		//casting conversion
		E& get_key()
		{
			return const_cast<E&>(const_cast<const doubly_node*>(this)->get_key());
		}

		void set_key(const E& data)
		{
			data_ = data;
		}
		//swap values
		bool swap(doubly_node<E>& a, doubly_node<E>& b) noexcept
		{
			E temp{ std::move(a.get_key()) };
			a = std::move(b.get_key());
			b.set_key() = std::move(temp);
			return true;
		}
		//----------------------------------
		//				DESTRUCTOR
		//----------------------------------
		~doubly_node()
		{
			//next points to NULL
			left = nullptr;
			right = nullptr;
		}
	};
}
