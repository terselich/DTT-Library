/*
------------------------------------------------------------------------------------------
							HEADER:       DOUBLY_LIST.H
------------------------------------------------------------------------------------------
 Summary:		Sequence data structures that implements list interface

 Authors:		Mateo Terselich

 Started:		30 April 2018

 Collections:	1) DOUBLY_NODE (Private class)
				2) DOUBLY_LIST
*/
//defines
#pragma once
//includes
#include "lists.h"
#include "doubly_node.h"

namespace dt
{
	template <class S> class doubly_list final : lists<S>
	{
		//----------------------------------
		//			DATA MEMBERS
		//----------------------------------
		doubly_node <S>* head_, * tail_;
		size_t length_;
	public:
		//----------------------------------
		//				CONSTRUCTORS
		//----------------------------------
		doubly_list();
		explicit doubly_list(S&& r_ref) noexcept;
		explicit doubly_list(const S& data);
		doubly_list(const doubly_list<S>& copy);
		doubly_list(const doubly_list<S>&& ref) noexcept;
		//----------------------------------
		//		PUBLIC METHOD MEMBERS
		//----------------------------------
		bool append(const S& data) override;
		bool append(S&& r_ref) noexcept override;
		bool append(S* pointer) override;
		bool push(const S& data) override;
		bool push(S&& r_ref) noexcept override;
		bool push(S* pointer) override;
		bool pop() override;
		bool pull() override;
		//empty list
		bool empty() override;
		bool is_empty() const override;
		//getters
		size_t size() const override;
		const S& get_head() const;
		S& get_head();
		const S& get_tail() const;
		S& get_tail();
		const S& get_at(size_t index) const;
		S& get_at(size_t index) override;
		//insert, delete.. node at index given
		bool insert_at(const S& data, size_t index);
		bool insert_at(S&& r_ref, size_t index);
		bool insert_at(S* pointer, size_t index);
		bool delete_at(size_t index);
		//equal operator
		S& operator[](size_t index);
		doubly_list<S>& operator=(const doubly_list<S>& list);
		doubly_list<S>& operator=(doubly_list<S>&& r_value_list) noexcept;
		doubly_list<S>& operator=(S&& r_value) noexcept;
		//----------------------------------
		//				DESTRUCTOR
		//----------------------------------
		~doubly_list();
	};

}
