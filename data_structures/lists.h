/*
------------------------------------------------------------------------------------------
							HEADER:       LIST.H
------------------------------------------------------------------------------------------
 Summary:		Sequence data structures that implements list interface

 Authors:		Mateo Terselich

 Started:		01 April 2018

 Collections:	1) LISTS INTERFACE


*/
//defines
#pragma once
#include <utility>
#include <stdexcept>

namespace dt
{
	template <class E> class lists
	{
	public:
		//----------------------------------
		//			PURE FUNCTIONS
		//----------------------------------
		//add items
		virtual bool append(const E& data) = 0;
		virtual bool append(E&& r_ref) = 0;
		virtual bool append(E* pointer) = 0;
		virtual bool push(const E& data) = 0;
		virtual bool push(E&& r_ref) = 0;
		virtual bool push(E* pointer) = 0;
		//remove items
		virtual bool pop() = 0;
		virtual bool pull() = 0;
		//empty list
		virtual bool is_empty() const = 0;
		virtual bool empty() = 0;
		//getter
		virtual size_t size() const = 0;
		virtual E& get_at(size_t index) = 0;
		//----------------------------------
		//			 DESTRUCTOR
		//----------------------------------	
		virtual ~lists() { /* delete */ };
	};
}
