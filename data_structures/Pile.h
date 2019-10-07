/*
------------------------------------------------------------------------------------------
							HERADER:       PILE.H
------------------------------------------------------------------------------------------
 Summary:		Adaptor depends on list implementations
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
	//template options limitator
	using List = typename std::enable_if < std::is_same<linked_list<E>, Linear>::value ||
		std::is_same<array_list<E>, Linear>::value ||
		std::is_same<ring<E>, Linear>::value,
		Linear>::type;
	//stack class
	template <class E, class List = array_list<E>> class pile
	{
		//----------------------------------
		//			DATA MEMBERS
		//----------------------------------
		List list_;
	public:
		//----------------------------------
		//				CONSTRUCTORS
		//----------------------------------
		pile() : list_{} {}
		explicit pile(const E& data) : list_{ data } {}
		explicit pile(E* pointer) : list_{ *pointer } {}
		explicit pile(E&& r_ref) : list_{ std::move(r_ref) } {}
		explicit pile(const pile<E, List>& copy) : list_{ copy.list_ } {}
		explicit pile(const List& copy) : list_{ copy } {}
		explicit pile(pile<E, List>&& r_ref) noexcept : list_{ std::move(r_ref.list_) } {}
		explicit pile(List&& r_ref) noexcept : list_{ std::move(r_ref) } {}
		//----------------------------------
		//		PUBLIC METHOD MEMBERS
		//----------------------------------

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
		bool push(const E& data)
		{
			return list_.push(data);
		}
		bool push(E&& r_ref)
		{
			return list_.push(std::move(r_ref));
		}
		bool push(E* pointer)
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
		E& poll()
		{
			//when the list is empty case
			if (list_.size() == 0) throw std::range_error("Array length_ is 0");
			//to return value copy
			auto to_return{ list_[0] };
			list_.pull();
			//return ..
			return to_return;
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
		E& top() const
		{
			return list_[0];
		}
		//OPERATOR OVERLOADING
		pile<E, List>& operator=(const pile<E, List>& copy)
		{
			//self assignment, compare addresses
			if (&copy == this) return *this;
			//else..
			list_ = copy.list_;
			return *this;
		}

		pile<E, List>& operator=(pile<E, List>&& r_pile) noexcept
		{
			list_ = r_pile.list_;
			return  *this;
		}
		pile<E, List>& operator=(linked_list<E>&& r_list) noexcept
		{
			list_ = std::move(r_list);
			return *this;
		}
		//----------------------------------
		//				DESTRUCTOR
		//----------------------------------
		~pile() = default;
	};
}
