/*
------------------------------------------------------------------------------------------
							HERADER:       LINE.H
------------------------------------------------------------------------------------------
 Summary:		Adaptor depends of list sequence

 Authors:		Mateo Terselich

 Started:		15 June 2018

 Collections:	1) LINE(QUEUE)


*/
//defines..
#pragma once
//includes...
#include "linked_list.h"
#include "array_list.h"
#include "doubly_list.h"

namespace dt
{
	template<class Linear, class C>
	//template options limitation
	using Sequence = typename std::enable_if < std::is_same<linked_list<C>, Linear>::value ||
		std::is_same<array_list<C>, Linear>::value ||
		std::is_same<doubly_list<C>, Linear>::value,
		Linear>::type;
	//queue class
	template <class Class, class Sequence = array_list<Class>> class line
	{
		using _QUEUE_ = line<Class, Sequence>;
		//-----------------------------------------------------------------------------------------
		//											DATA MEMBERS
		//-----------------------------------------------------------------------------------------
		
		Sequence list_;
		
	public:
		
		//-----------------------------------------------------------------------------------------
		//											CONSTRUCTORS
		//-----------------------------------------------------------------------------------------

		line() {}
		
		explicit line(const Class& data) : list_{ data } {}
		
		explicit line(Class* pointer) : queue(*pointer) {}
		
		explicit line(Class&& r_ref) : list_{ std::move(r_ref) } {}
		
		line(const _QUEUE_& copy) : list_{ copy.list_ } {}

		line(_QUEUE_&& r_ref) noexcept : list_{ std::move(r_ref.list_) } {}

		//-----------------------------------------------------------------------------------------
		//										PUBLIC METHOD MEMBERS
		//-----------------------------------------------------------------------------------------

		bool push(const Class& data)
		{
			return list_.append(data);
		}
		
		bool push(Class&& r_ref)
		{
			return list_.append(std::move(r_ref));
		}
		
		bool push(Class* pointer)
		{

			return list_.append(*pointer);
		}
		
		bool pop()
		{
			//when the list is empty case
			if (list_.size() == 0) throw std::range_error("Array length_ is 0");
			//for queue pull the first element
			return list_.pull();
		}
		
		//removes and returns element removed
		Class poll()
		{
			//when the list is empty case
			if (list_.size() == 0) throw std::range_error("Array length_ is 0");
			//create copy of head/front, stack locally
			Class copy{ list_[0] };
			list_.pull();
			return std::move(copy);
		}
		
		bool empty()
		{
			return list_.empty();
		}
		
		bool is_empty()
		{
			return list_.is_empty();
		}
		
		//getters
		Class& next() const
		{
			return list_[0];
		}
		
		Class& next()
		{
			return const_cast<Class&>(const_cast<const line*>(this)->next());
		}
		
		//operator overloading
		line& operator=(const _QUEUE_& copy)
		{
			//compare addresses to avoid self assignment
			if (&copy == this) return *this;
			//else..
			this->list_ = copy.list_;
			return *this;
		}
		
		line& operator=(_QUEUE_&& r_line) noexcept
		{
			this->list_ = std::move(r_line);
			return *this;
		}
		
		line < Class, Sequence>& operator=(linked_list<Class>&& r_list) noexcept
		{
			this->list_ = std::move(r_list);
			return *this;
		}
		
		//-----------------------------------------------------------------------------------------
		//											DESTRUCTOR
		//-----------------------------------------------------------------------------------------
		
		~line() {}
	};
}

