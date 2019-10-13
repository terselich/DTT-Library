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
// ReSharper disable once CppUnusedIncludeDirective
#include "pch.h"
#include "lists.h"
#include "node.h"

namespace dt
{
	template<class Data_type> class linked_list final : lists<Data_type>
	{
		using _NODE_ = node<Data_type>;
		using _LINKED_ = linked_list<Data_type>;
		
		//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		//																				DATA MEMBERS
		//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		_NODE_* _head, * _tail;
		int _length;
		
	public:
		//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		//																				CONSTRUCTORS
		//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		//parameter less constructor
		linked_list() :_head{ nullptr }, _tail{ nullptr }, _length{ 0 } {}

		/*
					_head and _tail
					  +-----+-+
					  | key |o------>NULL
					  +-----+-+
		*/
		explicit linked_list(Data_type&& r_ref) noexcept : _length{ 1 }
		{
			_head = new _NODE_{ std::move(r_ref) };
			_tail = _head;
		}

		explicit linked_list(const Data_type& data) : _length{ 1 }
		{
			//_head and _tail points to the same unique T in the list
			_head = new _NODE_{ data };
			_tail = _head;
		}
		//copy constructor
		linked_list(const _LINKED_& source) : _length{ source.size() }
		{
			//copy list. *() copies data
			_head = new _NODE_{ *source._head->key_ };
			_NODE_* a{ source._head->next }, * b{ _head };
			//copy every node in the same order
			while (a != nullptr)
			{
				//copy a key
				b->next = new _NODE_{ *a->key_ };
				a = a->next;
				b = b->next;
			}
			_tail = b;
			//pointer dangling
			b = nullptr;
			a = nullptr;
		}

		//move constructor
		linked_list(_LINKED_&& data) noexcept : _head{ data._head }, _tail{ data._tail }, _length{ data.size() }
		{
			//pointer dangling for deletion
			data._head = nullptr;
			data._tail = nullptr;
		}

		//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		//																			PUBLIC METHOD MEMBERS
		//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		/*
			_head		Node		_tail		NODE TO APPEND!!!
			+-----+-+    +-----+-+    +-----+-+            +-----+-+
			| key |o---->| key |o---->| key |o---->NULL----| key |o----->NULL
			+-----+-+    +-----+-+    +-----+-+            +-----+-+
			No return T
			An integer data T as parameter
		*/

		//append: new _tail, push: new _head, pop delete _head, push delete _head
		bool append(const Data_type& data) override
		{
			//when the list is empty
			if (_length == 0)
			{
				_head = new _NODE_{ data };
				_tail = _head;
				//_length increments by one
				_length = 1;
				return true;
			}
			//else...
			auto* temp{ new _NODE_{ data } };
			_tail->next = temp;
			_tail = temp;
			//_length increments by one, pointer dangling
			temp = nullptr;
			_length++;
			return true;
		}

		bool append(Data_type&& r_ref) noexcept override
		{
			if (_length == 0)
			{
				_head = new _NODE_{ std::move(r_ref) };
				_tail = _head;
				//_length increments by one
				_length = 1;
				return true;
			}
			//else
			auto* temp{ new _NODE_{ std::move(r_ref) } };
			_tail->next = temp;
			_tail = temp;
			//_length increments by one, pointer dangling
			temp = nullptr;
			_length++;
			return true;
		}

		bool append(Data_type* pointer) override
		{
			//copy data from the pointer and call append
			return append(*pointer);
		}

		//add a node at the beginning of the list
		/*
								PUSH!!!!!
									_head	  Node				_tail
				 New Node		  +-----+-+		+-----+-+	  +-----+-+
				+-----+-+   ----->| key |o----->| key |o----->| key |o----->NULL
				| key |o---|      +-----+-+     +-----+-+     +-----+-+
				+-----+-+
		*/
		bool push(const Data_type& data) override
		{
			//when the list is empty
			if (_length == 0)
			{
				_head = new _NODE_{ data };
				_tail = _head;
				//_length increments by one
				_length = 1;
				return true;
			}
			//else..
			auto* temp{ new _NODE_{ data } };
			temp->next = _head;
			_head = temp;
			//pointer dangling
			temp = nullptr;
			_length++;
			return true;
		}

		bool push(Data_type&& r_ref) noexcept override
		{
			//when the list is empty
			if (_length == 0)
			{
				_head = new _NODE_{ std::move(r_ref) };
				_tail = _head;
				//_length increments by one
				_length = 1;
				return true;
			}
			//else..
			auto* temp{ new _NODE_{ std::move(r_ref) } };
			temp->next = _head;
			_head = temp;
			//pointer dangling
			temp = nullptr;
			_length++;
			return true;
		}

		bool push(Data_type* pointer) override\
		{
			//copy value to an r value ----> from the pointer data calling push
			return push(*pointer);
		}

		//delete last node of the list
		bool pop() override
		{
			if (_head == nullptr && _tail == nullptr)
				return false;
			if (_head == _tail) //addresses
			{
				//delete _head, _tail and _head now are null and _length is 0
				delete _head;
				_tail = nullptr;
				_head = nullptr;
				_length = 0;
				return true;
			}
			//else...
			auto* traverse{ _head };
			while (traverse->next != _tail)
			{
				traverse = traverse->next;
			}
			traverse->next = nullptr;
			delete _tail;
			//_tail now is temp (previous node)
			_tail = traverse;
			_length--;
			traverse = nullptr;	//pointer dangling
			return true;
		}

		//deletes first node
		bool pull() override
		{
			if (_head == _tail) //addresses
			{
				//delete _head, _tail and _head now are null and _length is 0
				delete _head;
				_tail = nullptr;
				_head = nullptr;
				_length = 0;
				return true;
			}
			// ReSharper disable once CppEntityAssignedButNoRead temp equals head
			auto* temp = _head;
			//head moves one forward, check if head is not null
			_head = _head->next;
			//delete temp, next NULL ~node destructor
			delete temp;
			//decrease _length by 1
			--_length;
			//temp dangling case
			temp = nullptr;
			return true;
		}
		/*						INSERT INDEX AT
								NODE INSERT AT 3
						_head		Node		.Node		  +-----+-+              _tail
					+-----+-+    +-----+-+    +-----+-+    -->| key |o---�         +-----+-+
					| key |o---->| key |o---->| key |o----/   +-----+-+  |-------->| key |o----->NULL
					+-----+-+    +-----+-+    +-----+-+                            +-----+-+
		*/
		//insert, delete.. node at index given
		bool insert_at(const Data_type& data, const int index)
		{
			//when the index given is the same than the _length of the list
			if (_length == index) return append(data);
			//when index is 0
			if (index == 0) return push(data);
			//else...for other values traverse pointer
			auto* traverse{ _head };
			auto count{ 0 };
			//goes before the index to insert at
			while (count < index - 1) {
				traverse = traverse->next;
				count++;
			}
			//connecting the node first to the list
			auto* temp{ new _NODE_{data} };
			temp->next = traverse->next;
			traverse->next = temp;
			_length++;
			//pointer dangling
			traverse = nullptr;
			temp = nullptr;
			return true;
		}
		
		bool insert_at(Data_type&& r_ref, const int index)
		{
			//when the index given is the same than the _length of the list
			if (_length == index) return append(std::move(r_ref));
			//when index is 0
			if (index == 0) return push(std::move(r_ref));
			//else...for other values traverse pointer
			auto* traverse{ _head };
			auto count{ 0 };
			//goes before the index to insert at
			while (count < index - 1) {
				traverse = traverse->next;
				count++;
			}
			//connecting the node first to the list
			auto* temp{ new _NODE_{ std::move(r_ref) } };
			temp->next = traverse->next;
			traverse->next = temp;
			_length++;
			//pointer dangling
			traverse = nullptr;
			temp = nullptr;
			return true;
		}
		
		bool insert_at(Data_type* pointer, int index)
		{
			//dereference pointer and copy its value and insert it at index given
			return insert_at(*pointer, index);
		}

		/*							DELETE AT INDEX GIVEN
										  Delete AT 3
															  +-----+-+
					_head		Node		.Node			  | key |o----->NULL          _tail
				+-----+-+    +-----+-+    +-----+-+           +-----+-+                 +-----+-+
				| key |o---->| key |o---->| key |o----------NOW POINTS TO 5------------>| key |o----->NULL
				+-----+-+    +-----+-+    +-----+-+                                     +-----+-+
		*/
		bool delete_at(const int index)
		{
			if (_length - 1 == index) return pop();
			if (_length - 1 < index) return false;
			if (index == 0) return pull();
			//else...
			auto count{ 0 };
			auto* prev{ _head };
			//searching index to delete
			while (count < index - 1) {
				prev = prev->next;
				++count;
			}//deleting traverse node
			auto* traverse = prev->next;
			prev->next = traverse->next;
			traverse->next = nullptr;
			//delete traverse pointing node
			delete traverse;
			traverse = nullptr;
			prev = nullptr;
			//decrease _length
			_length--;
			return true;
		}
		
		//empty list AND deletes all nodes
		bool empty() override	
		{
			if (_head == nullptr && _tail == nullptr) return false;
			if (_head == _tail) //addresses
			{
				delete _head;
				_head = nullptr;
				_tail = nullptr;
				_length = 0;
				return true;
			}
			//Node pop..... 1 by 1, if is empty break
			while (pull()) if (is_empty()) break;
			return true;
		}
		
		bool is_empty() const override
		{
			return _length == 0;
		}
		
		//getters
		int size() const override
		{
			return _length;
		}

		//get head key value
		const Data_type& get_head() const
		{
			return _head->key_;
		}
		
		Data_type& get_head()
		{
			return const_cast<Data_type&> (const_cast<const linked_list*> (this)->get_head());
		}

		//get tail key value
		const Data_type& get_tail() const\
		{
			return _tail->key_;
		}
		
		Data_type& get_tail()
		{
			return const_cast<Data_type&>(const_cast<const linked_list*> (this)->get_tail());
		}

		
		const Data_type& get_at(const int index) const
		{
			if (index == 0)
				return _head->key_;
			if (index == _length - 1)
				return _tail->key_;
			//else...count from zero to get to the node at index
			auto count{ 0 };
			auto* traverse{ _head };
			while (count < index)
			{
				traverse = traverse->next;
				count++;
			}
			return traverse->key_;
		}
		
		Data_type& get_at(const int index) override
		{
			return const_cast<Data_type&>(const_cast<const linked_list*> (this)->get_at(index));
		}

		//operator overloading
		Data_type& operator[](const int index)
		{
			return get_at(index);
		}

		//assignment operator overloading
		linked_list& operator=(const _LINKED_& list)
		{
			//self assignment detection
			if (&list == this) return *this;
			//delete current list
			if (_head != nullptr && _tail != nullptr) this->empty();
			const Data_type _head_temp = list._head->key_;
			//copy list.
			_length = list.size();
			_head = new _NODE_{ _head_temp };
			_NODE_* a{ list._head->next }, * b{ _head };
			//copy every node in the same order
			while (a != nullptr)
			{
				//T temp local
				const Data_type temp = a->key_;
				b->next = new _NODE_{ temp };
				a = a->next;
				b = b->next;
			}
			_tail = b;
			//pointer dangling
			a = nullptr;
			b = nullptr;
			//return statement
			return *this;
		}
		
		linked_list& operator=(_LINKED_&& r_value_list) noexcept
		{
			//delete this
			if (_head != nullptr && _tail != nullptr) this->empty();
			//switch ownership
			_head = r_value_list._head;
			_tail = r_value_list._tail;
			_length = r_value_list._length;
			//pointer dangling
			r_value_list._head = nullptr;
			r_value_list._tail = nullptr;
			//return statement
			return *this;

		}
		
		//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		//																					DESTRUCTOR
		//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		~linked_list()
		{
			//empty list,if it fails try again...
			while (empty());
		}
	};
}
