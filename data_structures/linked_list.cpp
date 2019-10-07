#include "pch.h"
#include "linked_list.h"

namespace dt
{
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//																				CONSTRUCTORS
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	template <class T> linked_list<T>::linked_list() :_head{ nullptr }, _tail{ nullptr }, _length{ 0 } {}
	template<class T> linked_list<T>::linked_list(T&& r_ref) noexcept : _length{ 1 }
	{
		_head = new node<T>{ std::move(r_ref) };
		_tail = _head;
	}
	/*
		_head and _tail
		  +-----+-+
		  | key |o------>NULL
		  +-----+-+
	*/
	template <class T> linked_list<T>::linked_list(const T& data) : _length{ 1 }
	{
		//_head and _tail points to the same unique T in the list
		_head = new node<T>{ data };
		_tail = _head;
	}
	//copy constructor
	template<class T>linked_list<T>::linked_list(const linked_list<T>& source) : _length{ source.size() }
	{
		//temp _head
		const T _head_temp = source._head->key_;
		//copy list.
		_head = new node<T>{ _head_temp };
		node<T>* a{ source._head->next }, * b{ _head };
		//copy every node in the same order
		while (a != nullptr)
		{
			//T temp local
			const T temp = a->key_;
			b->next = new node<T>{ temp };
			a = a->next;
			b = b->next;
		}
		_tail = b;
		//pointer dangling
		b = nullptr;
		a = nullptr;
	}
	template<class T> linked_list<T>::linked_list(linked_list<T>&& data) noexcept : _head{ data._head }, _tail{ data._tail }, _length{ data.size() }
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
	template <class T> bool linked_list<T>::append(const T& data)
	{
		//when the list is empty
		if (_length == 0)
		{
			_head = new node<T>{ data };
			_tail = _head;
			//_length increments by one
			_length = 1;
			return true;
		}
		//else...
		auto* temp{ new node<T>{ data } };
		_tail->next = temp;
		_tail = temp;
		//_length increments by one, pointer dangling
		temp = nullptr;
		_length++;
		return true;
	}
	template<class T> bool linked_list<T>::append(T&& r_ref) noexcept
	{
		if (_length == 0)
		{
			_head = new node<T>{ std::move(r_ref) };
			_tail = _head;
			//_length increments by one
			_length = 1;
			return true;
		}
		//else
		auto* temp{ new node<T>{ std::move(r_ref) } };
		_tail->next = temp;
		_tail = temp;
		//_length increments by one, pointer dangling
		temp = nullptr;
		_length++;
		return true;
	}
	template<class T> bool linked_list<T>::append(T* pointer)
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
	template <class T> bool linked_list<T>::push(const T& data)
	{
		//when the list is empty
		if (_length == 0)
		{
			_head = new node<T>{ data };
			_tail = _head;
			//_length increments by one
			_length = 1;
			return true;
		}
		//else..
		auto* temp{ new node<T>{ data } };
		temp->next = _head;
		_head = temp;
		//pointer dangling
		temp = nullptr;
		_length++;
		return true;
	}
	template<class T> bool linked_list<T>::push(T&& r_ref) noexcept
	{
		//when the list is empty
		if (_length == 0)
		{
			_head = new node<T>{ std::move(r_ref) };
			_tail = _head;
			//_length increments by one
			_length = 1;
			return true;
		}
		//else..
		auto* temp{ new node<T>{ std::move(r_ref) } };
		temp->next = _head;
		_head = temp;
		//pointer dangling
		temp = nullptr;
		_length++;
		return true;
	}
	template<class T> bool linked_list<T>::push(T* pointer)
	{
		//copy value to an r value ----> from the pointer data calling push
		return push(*pointer);
	}
	//deletes last node of the list
	template <class T> bool linked_list<T>::pop()
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
	template<class T> bool linked_list<T>::pull()
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
		// ReSharper disable once CppEntityAssignedButNoRead temp equals head
		auto* temp = _head;
		//head moves one forward, check if head is not null
		_head = _head->next;
		//delete temp, next nullptr ~node destructor
		delete temp;
		//decrease _length by 1
		--_length;
		//temp dangling case
		temp = nullptr;
		return true;
	}
	//deletes all nodes
	template<class T> bool linked_list<T>::empty()
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
	//check if it is empty
	template<class T> bool linked_list<T>::is_empty() const
	{
		return _length == 0;
	}
	//returns the _length of the linked list
	template <class T> size_t linked_list<T>::size() const
	{
		return _length;
	}
	template<class T>
	const T& linked_list<T>::get_head() const
	{
		return _head->key_;
	}
	template<class T>
	T& linked_list<T>::get_head()
	{
		return const_cast<T&> (const_cast<const linked_list*> (this)->get_head());
	}
	template<class T>
	const T& linked_list<T>::get_tail() const
	{
		return _tail->key_;
	}
	template<class T>
	T& linked_list<T>::get_tail()
	{
		return const_cast<T&>(const_cast<const linked_list*> (this)->get_tail());
	}
	/*							INSERT INDEX AT
							NODE INSERT AT 3
			_head		Node		.Node		  +-----+-+              _tail
		+-----+-+    +-----+-+    +-----+-+    -->| key |o---�         +-----+-+
		| key |o---->| key |o---->| key |o----/   +-----+-+  |-------->| key |o----->NULL
		+-----+-+    +-----+-+    +-----+-+                            +-----+-+
	*/
	template <class T> bool linked_list<T>::insert_at(const T& data, const size_t index)
	{
		//when the index given is the same than the _length of the list
		if (_length == index) return append(data);
		//when index is 0
		if (index == 0) return push(data);
		//else...for other values traverse pointer
		auto* traverse{ _head };
		size_t count = 0;
		//goes before the index to insert at
		while (count < index - 1) {
			traverse = traverse->next;
			count++;
		}
		//connecting the node first to the list
		auto* temp{ new node<T>{data} };
		temp->next = traverse->next;
		traverse->next = temp;
		_length++;
		//pointer dangling
		traverse = nullptr;
		temp = nullptr;
		return true;
	}
	template<class T>
	bool linked_list<T>::insert_at(T&& r_ref, const size_t index)
	{
		//when the index given is the same than the _length of the list
		if (_length == index) return append(std::move(r_ref));
		//when index is 0
		if (index == 0) return push(std::move(r_ref));
		//else...for other values traverse pointer
		auto* traverse{ _head };
		size_t count = 0;
		//goes before the index to insert at
		while (count < index - 1) {
			traverse = traverse->next;
			count++;
		}
		//connecting the node first to the list
		auto* temp{ new node<T>{ std::move(r_ref) } };
		temp->next = traverse->next;
		traverse->next = temp;
		_length++;
		//pointer dangling
		traverse = nullptr;
		temp = nullptr;
		return true;
	}
	template<class T>
	bool linked_list<T>::insert_at(T* pointer, const size_t index)
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
	template <class T> bool linked_list<T>::delete_at(const size_t index)
	{
		if (_length - 1 == index) return pop();
		if (_length - 1 < index) return false;
		if (index == 0) return pull();
		//else...
		size_t count = 0;
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
	//returns node at index given
	template<class T> const T& linked_list<T>::get_at(const size_t index) const
	{
		if (index == 0)
			return _head->key_;
		if (index == _length - 1)
			return _tail->key_;
		//else...count from zero to get to the node at index
		size_t count{ 0 };
		auto* traverse{ _head };
		while (count < index)
		{
			traverse = traverse->next;
			count++;
		}
		return traverse->key_;
	}
	template<class T> T& linked_list<T>::get_at(const size_t index)
	{
		return const_cast<T&>(const_cast<const linked_list*> (this)->get_at(index));
	}
	//indexing
	template<class T> T& linked_list<T>::operator[](const size_t index)
	{
		return get_at(index);
	}
	template<class T> linked_list<T>& linked_list<T>::operator=(const linked_list<T>& list)
	{
		//self assignment detection
		if (&list == this) return *this;
		//delete current list
		if (_head != nullptr && _tail != nullptr) this->empty();
		const T _head_temp = list._head->key_;
		//copy list.
		_length = list.size();
		_head = new node<T>{ _head_temp };
		node<T>* a{ list._head->next }, * b{ _head };
		//copy every node in the same order
		while (a != nullptr)
		{
			//T temp local
			const T temp = a->key_;
			b->next = new node<T>{ temp };
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
	template<class T> linked_list<T>& linked_list<T>::operator=(linked_list<T>&& r_value_list) noexcept
	{
		//self assignment detection
		if (&r_value_list == this) return *this;
		//delete current list
		if (_head != nullptr && _tail != nullptr) this->empty();
		//transfer ownership
		_head = r_value_list._head;
		_tail = r_value_list._tail;
		//pointer dangling for deletion
		r_value_list._head = nullptr;
		r_value_list._tail = nullptr;
		return *this;
	}
	template<class T> linked_list<T>& linked_list<T>::operator=(T&& r_value) noexcept
	{
		//delete this
		if (_head != nullptr && _tail != nullptr) this->empty();
		//switch ownership
		_head = new node<T>{ std::move(r_value) };
		_tail = _head;
		_length = 1;
		//return statement
		return *this;

	}
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//																					DESTRUCTOR
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	template <class T> linked_list<T>::~linked_list()
	{
		//empty list,if it fails try again...
		while (empty());
	}
}
