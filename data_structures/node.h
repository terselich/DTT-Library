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
		//----------------------------------
		//			DATA MEMBERS
		//----------------------------------
		/*
				  node
				+-----+-+
				| key |o---->NULL
				+-----+-+
		*/
		T key_;
		//----------------------------------
		//				CONSTRUCTORS
		//----------------------------------
		//private, only linked_list can create nodes
		explicit node(T&& r_ref) noexcept : key_{ std::move(r_ref) } {}
		explicit node(const T& data) : key_{ data } {}
		explicit node(const T* data) : node(*data) {}
	public:
		//public next pointer of node
		node<T>* next{ nullptr };
		//copy constructor
		node(const node<T>& source) : key_{ source.get_key() } {}
		//move constructor
		node(node<T>&& source) noexcept : key_{ source.key_ }, next{ source.next }
		{
			//pointer dangling
			if (source.next != nullptr) source.next = nullptr;
		}
		//----------------------------------
		//		PUBLIC METHOD MEMBERS
		//----------------------------------
		//Operator assignment copy equals
		node<T>& operator=(const node<T>& source)
		{
			//self assignment
			if (&source == this) return *this;
			//key_ copy
			key_ = source.get_key();
			return *this;
		}
		//move node object
		node<T>& operator=(node<T>&& data) noexcept
		{
			//self assignment
			if (&data == this) return *this;
			//move or change ownership
			key_ = data.get_key();
			return *this;
		}
		//move T r values
		node<T>& operator=(T&& r_type) noexcept
		{
			//move ownership
			key_ = r_type;
			return *this;
		}
		//		COMPARISON OPERATORS OVERLOADING
		friend bool operator==(node<T>& a, node<T>& b)
		{
			return a.get_key() == b.get_key();
		}
		friend bool operator !=(node<T>& a, node<T>& b)
		{
			return !(a.get_key() == b.get_key());
		}
		friend bool operator>=(node<T>& a, node<T>& b)
		{
			return (a.get_key() >= b.get_key());
		}
		friend bool operator>(node<T>& a, node<T>& b)
		{
			return (a.get_key() > b.get_key());
		}
		friend bool operator<(node<T>& a, node<T>& b)
		{
			return (a.get_key() < b.get_key());
		}
		friend bool operator <=(node<T>& a, node<T>& b)
		{
			return (a.get_key() <= b.get_key());
		}
		//getter and setter
		const T& get_key() const
		{
			return key_;
		}
		//getter conversion
		T& get_key()
		{
			return const_cast<T&>(const_cast<const node*>(this)->get_key());
		}
		void set_key(const T& data)
		{
			key_ = data;
		}
		bool swap(node<T> node_a, node<T> node_b)
		{
			T temp{ std::move(node_a.get_key()) };
			node_a = std::move(node_b.get_key());
			node_b = std::move(temp);

			if (node_a != node_b) return true;
			return false;
		}
		//----------------------------------
		//				DESTRUCTOR
		//----------------------------------
		~node()
		{
			//next points to NULL
			next = nullptr;
		}
	};
}


