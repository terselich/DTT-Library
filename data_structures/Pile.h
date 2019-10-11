/*
------------------------------------------------------------------------------------------
							HEADER:       PILE.H
------------------------------------------------------------------------------------------
 Summary:		Adapter, depends on list implementations (ARRAY_LIST, LINKED_LIST and DOUBLY_LIST)
 Authors:		Mateo Terselich

 Started:		15 June 2018

 Collections:	1) PILE(STACK)


*/
//defines..
#pragma once
//includes..
#include "linked_list.h"
#include "array_list.h"
#include "doubly_list.h"

namespace dt
{
	template<class Linear, class E>
	//template options eliminator
	using List = typename std::enable_if < std::is_same<linked_list<E>, Linear>::value ||
		std::is_same<array_list<E>, Linear>::value ||
		std::is_same<doubly_list<E>, Linear>::value,
		Linear>::type;
	//stack class
	template <class Data_type, class List = array_list<Data_type>> class pile
	{
		using _STACK_ = pile<Data_type, List>;
		
		//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		//																				DATA MEMBERS
		//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		
		List list_;

	//public members
	public:
		
		//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		//																				CONSTRUCTORS
		//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		
		pile() : list_{} {}
		
		explicit pile(const Data_type& data) : list_{ data } {}
		
		explicit pile(Data_type* pointer) : list_{ *pointer } {}
		
		explicit pile(Data_type&& r_ref) : list_{ std::move(r_ref) } {}

		//copy constructor
		explicit pile(const _STACK_& copy) : list_{ copy.list_ } {}

		//move constructor
		explicit pile(_STACK_&& r_ref) noexcept : list_{ std::move(r_ref.list_) } {}
		
		//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		//																			PUBLIC METHOD MEMBERS
		//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		/*
		 *			PUSH ( ITEM 6 )
		 *
		 *			  [__ITEM 6__]
		 *				   |
		 *			|	   V	   |
		 *			|	    	   |
		 *			| [__ITEM 5__] |
		 *			| [__ITEM 4__] |
		 *			| [__ITEM 3__] |
		 *			| [__ITEM 2__] |
		 *			| [__ITEM 1__] |
		 *			|______________|
		 */
		bool push(const Data_type& data)
		{
			return list_.push(data);
		}
		
		bool push(Data_type&& r_ref)
		{
			return list_.push(std::move(r_ref));
		}
		
		bool push(Data_type* pointer)
		{
			return push(*pointer);
		}
		
		//POP: delete next element
			/*
		 *			   POP (  ) delete ITEM 6
		 *
		 *			    [__ITEM 6__]
							 ^
		 *				    /
		 *			|	   |	   |
		 *			|	   |	   |
		 *			| [__ITEM 5__] |
		 *			| [__ITEM 4__] |
		 *			| [__ITEM 3__] |
		 *			| [__ITEM 2__] |
		 *			| [__ITEM 1__] |
		 *			|______________|
		 */
		bool pop()
		{
			//when the list is empty case
			if (list_.size() == 0) throw std::range_error("Array length_ is 0");
			//pull the list pile!
			return list_.pull();
		}
		
		//POLL: calls pop and returns the item popped
		Data_type poll()
		{
			//when the list is empty case
			if (list_.size() == 0) throw std::range_error("Array length_ is 0");
			//to return value copy stack located
			auto to_return{ list_[0] };
			list_.pull();
			//return ..
			return std::move(to_return);
		}
		
		//empty entire list
		bool empty()
		{
			return list_.empty();
		}
		
		//check if the List is empty
		bool is_empty() const
		{
			return list_.is_empty();
		}
		
		//GETTERS
		size_t size() const
		{
			return list_.size();
		}
		
		Data_type& top() const
		{
			return list_[0];
		}
		
		//OPERATOR OVERLOADING
		pile& operator=(const _STACK_& copy)
		{
			//self assignment, compare addresses
			if (&copy == this) return *this;
			//else..
			//empty list and copy (list_ implementation deals with both
			list_ = copy.list_;
			return *this;
		}

		pile& operator=(_STACK_&& r_pile) noexcept
		{
			list_ = r_pile.list_;
			return  *this;
		}
		
		//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		//																					DESTRUCTOR
		//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		~pile() = default;
	};
}
