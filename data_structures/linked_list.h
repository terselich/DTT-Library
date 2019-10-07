/*
------------------------------------------------------------------------------------------
							HEADER:       LINKED_LIST.H
------------------------------------------------------------------------------------------
 Summary:		Sequence data structures that implements list interface

 Authors:		Mateo Terselich

 Started:		30 April 2018

 Collections:	1) NODE (Private class)
				2) LINKED_LIST
*/
//defines
#pragma once
//includes
#include "lists.h"
#include "node.h"

namespace dt
{
	template<class T> class linked_list final : lists<T>
	{
		//----------------------------------
		//			DATA MEMBERS
		//----------------------------------
		node<T>* _head, * _tail;
		size_t _length;
	public:
		//----------------------------------
		//				CONSTRUCTORS
		//----------------------------------
		linked_list();
		explicit linked_list(T&& r_ref) noexcept;
		explicit linked_list(const T& data);
		linked_list(const linked_list<T>& source);
		linked_list(linked_list<T>&& data) noexcept;
		//----------------------------------
		//		PUBLIC METHOD MEMBERS
		//----------------------------------
		//append: new _tail, push: new _head, pop delete _head, push delete _head
		bool append(const T& data) override;
		bool append(T&& r_ref) noexcept override;
		bool append(T* pointer) override;
		bool push(const T& data) override;
		bool push(T&& r_ref) noexcept override;
		bool push(T* pointer) override;
		bool pop() override;
		bool pull() override;
		//empty list
		bool empty() override;
		bool is_empty() const override;
		//getters
		size_t size() const override;
		const T& get_head() const;
		T& get_head();
		const T& get_tail() const;
		T& get_tail();
		const T& get_at(size_t index) const;
		T& get_at(size_t index) override;
		//insert, delete.. node at index given
		bool insert_at(const T& data, size_t index);
		bool insert_at(T&& r_ref, size_t index);
		bool insert_at(T* pointer, size_t index);
		bool delete_at(size_t index);
		//operator overloading
		T& operator[](size_t index);
		linked_list<T>& operator=(const linked_list<T>& list);
		linked_list<T>& operator=(linked_list<T>&& r_value_list) noexcept;
		linked_list<T>& operator=(T&& r_value) noexcept;
		//----------------------------------
		//				DESTRUCTOR
		//----------------------------------
		~linked_list();
	};
}
