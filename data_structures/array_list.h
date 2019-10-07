/*
------------------------------------------------------------------------------------------
							HEADER:       ARRAY_LIST.H
------------------------------------------------------------------------------------------
 Summary:		Sequence data structures that implements list interface

 Authors:		Mateo Terselich

 Started:		05 April 2018

 Collections:	1) ARRAY_LIST
*/
//defines
#pragma once

//includes...
#include "lists.h"

namespace dt
{
	template<class S = int> class array_list : lists<S>
	{
		//----------------------------------
		//			DATA MEMBERS
		//----------------------------------
		size_t capacity_;
		size_t length_;
		size_t front_index;
		//pointer array
		S* array_;
		//----------------------------------
		//		PRIVATE METHOD MEMBERS
		//----------------------------------
		bool resize(size_t new_capacity);
	public:
		//----------------------------------
		//			CONSTRUCTORS
		//----------------------------------
		explicit array_list(size_t&& capacity = 10);
		explicit array_list(S&& r_ref);
		explicit array_list(const S& data);
		explicit array_list(const S&& fill_with, size_t times);
		array_list(const array_list<S>& copy);
		array_list(array_list<S>&& r_list) noexcept;
		//----------------------------------
		//		PUBLIC METHOD MEMBERS
		//----------------------------------
		//add remove methods
		bool append(const S& data) override;
		bool append(S&& r_ref) override;
		bool append(S* pointer) override;
		bool push(const S& data) override;
		bool push(S&& r_ref) override;
		bool push(S* pointer) override;
		bool pop() override;
		bool pull() override;
		//resize
		bool shrink();
		bool empty() override;
		bool is_empty() const override;
		//getters
		size_t size() const override;
		size_t capacity() const;
		S& get_at(size_t index) const;
		S& get_at(size_t index) override;
		//operator overloading
		array_list<S>& operator=(const array_list& copy);
		array_list<S>& operator=(array_list&& r_list) noexcept;
		S& operator[](size_t index);
		//----------------------------------
		//			DESTRUCTOR
		//----------------------------------
		~array_list();
	};
}

