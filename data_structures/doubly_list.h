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
// ReSharper disable once CppUnusedIncludeDirective
#include "pch.h"
#include "lists.h"
#include "doubly_node.h"

namespace dt
{
	template <class Data_type> class doubly_list final : lists<Data_type>
	{
		using _NODE_ = doubly_node<Data_type>;
		using _DEQ_ = doubly_list<Data_type>;
		//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		//																				DATA MEMBERS
		//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		_NODE_ * head_, * tail_;
		int length_;
	
	//public methods
	public:
		
		//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		//																				CONSTRUCTORS
		//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		doubly_list() : head_{ nullptr }, tail_{ nullptr }, length_{ 0 }{}
		
		explicit doubly_list(Data_type&& r_ref) noexcept : length_{ 1 }
		{
			head_ = new _NODE_{ std::move(r_ref) };
			tail_ = head_;
		}
		
		explicit doubly_list(const Data_type& data) : head_{ new _NODE_{ data } },
											  tail_{ head_ }, length_{ 0 } {}
		//deep copy constructor
		explicit doubly_list(const _DEQ_& copy) : length_{ copy.size() }
		{
			const Data_type _head_temp = copy.head_->data_;
			//copy list
			head_ = new _NODE_{ _head_temp };
			_NODE_ a{ copy.head->right }, b{ head_ };
			//copy every node in order
			while (a != nullptr)
			{
				const Data_type temp = a->data_;
				b->right = new _NODE_{ temp };
				//b next left pointer to b
				b->right->left = b;
				a = a->right;
				b = b->right;
			}
			tail_ = b;
			//pointer dangling
			b = nullptr;
			a = nullptr;
		}

		//move constructor
		explicit doubly_list(const _DEQ_&& ref) noexcept : head_{ ref.head_ },
														   tail_{ ref.tail_ },
														   length_{ ref.size() }
		{
			//pointer dangling for deletion
			ref.head_ = nullptr;
			ref.tail_ = nullptr;
		}

		//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		//																			PUBLIC METHOD MEMBERS
		//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		//append: Add node at the end of the list, push: Add node at the beginning
		bool append(const Data_type& data) override
		{
			if (head_ == nullptr && tail_ == nullptr || length_ == 0)
			{
				head_ = new _NODE_{ data };
				//tail points to head too
				tail_ = head_;
				++length_;
				return true;
			}
			if (head_ == tail_)
			{
				tail_ = new _NODE_{ data };
				//head points to tail and tail to head (doubly linked list)
				head_->right = tail_;
				tail_->left = head_;
				length_++;
				return true;
			}
			auto* temp{ new _NODE_{ data } };
			//linking tail a new node
			tail_->right = temp;
			temp->left = tail_;
			//move tail
			tail_ = tail_->right;
			length_++;
			//pointer dangling
			temp = nullptr;
			return true;
		}
		
		bool append(Data_type&& r_ref) noexcept override
		{
			if (head_ == nullptr && tail_ == nullptr || length_ == 0)
			{
				head_ = new _NODE_{ std::move(r_ref) };
				//tail points to head too
				tail_ = head_;
				++length_;
				return true;
			}
			if (head_ == tail_)
			{
				tail_ = new _NODE_{ std::move(r_ref) };
				//head points to tail and tail to head (doubly linked list)
				head_->right = tail_;
				tail_->left = head_;
				length_++;
				return true;
			}
			auto* temp{ new _NODE_{ std::move(r_ref) } };
			//linking tail a new node
			tail_->right = temp;
			temp->left = tail_;
			//move tail
			tail_ = tail_->right;
			length_++;
			//pointer dangling
			temp = nullptr;
			return true;
		}
		
		bool append(Data_type* pointer) override
		{
			//copy data from pointer dereference and call append
			return append(*pointer);
		}

		//push: inserts a node at beginning of the list
		bool push(const Data_type& data) override
		{
			if (head_ == nullptr && tail_ == nullptr)
			{
				head_ = new _NODE_{ data };
				tail_ = head_;
				//increase and return
				length_++;
				return true;
			}
			if (head_ == tail_)	//addresses (*==*)
			{
				head_ = new _NODE_{ data };
				//connecting list
				head_->right = tail_;
				tail_->left = head_;
				//return and increment length
				length_++;
				return true;
			}
			auto* temp = head_;
			head_ = new _NODE_{ data };
			//connect new head node with the list
			head_->right = temp;
			temp->left = head_;
			//increase and return
			temp = nullptr;
			length_++;
			return true;
		}
		
		bool push(Data_type&& r_ref) noexcept override
		{
			if (head_ == nullptr && tail_ == nullptr)
			{
				head_ = new _NODE_{ std::move(r_ref) };
				tail_ = head_;
				//increase and return
				length_++;
				return true;
			}
			if (head_ == tail_)	//addresses (*==*)
			{
				head_ = new _NODE_{ std::move(r_ref) };
				//connecting list
				head_->right = tail_;
				tail_->left = head_;
				//return and increment length
				length_++;
				return true;
			}
			auto* temp = head_;
			head_ = new _NODE_{ std::move(r_ref) };
			//connect new head node with the list
			head_->right = temp;
			temp->left = head_;
			//increase and return
			temp = nullptr;
			length_++;
			return true;
		}
		
		bool push(Data_type* pointer) override
		{
			//copy data that pointer points and call push
			return push(*pointer);
		}

		//pop: Delete the last node, pull: Delete the first node
		bool pop() override
		{
			if (head_ == nullptr && tail_ == nullptr) return false;
			if (head_ == tail_) //addresses equality
			{
				delete head_;
				head_ = nullptr;
				tail_ = nullptr;
				//return statement
				length_--;
				return true;
			}
			//temp previous node to tail
			auto* temp{ tail_->left };
			//deletes tail, left and right nodes to nullptr, and disconnects temp from tail
			temp->right = nullptr;
			delete tail_;
			//update tail and length
			tail_ = temp;
			temp = nullptr;
			length_--;
			return true;
		}

		bool pull() override
		{
			if (head_ == nullptr && tail_ == nullptr) return false;
			if (head_ == tail_)
			{
				//right and left set to nullptr
				delete tail_;
				head_ = nullptr;
				tail_ = nullptr;
				--length_;
				return true;
			}
			auto* temp{ head_ };
			//move head forward, new head left pointer to NULL
			head_ = head_->right;
			head_->left = nullptr;
			delete temp;
			temp = nullptr;
			//update length
			--length_;
			return true;
		}

		//insert, delete.. node at index given
		bool insert_at(const Data_type& data, const int index)
		{
			if (index == 0) return push(data);
			if (index == length_) append(data);
			//OUT OF BOUNDS
			if (index > length_) throw 0;
			if (index <= ((length_ - 1) / 2))
			{
				auto* traverse{ head_ };
				size_t count{ 0 };
				//traverse list
				while (count < index - 1)
				{
					traverse = traverse->right;
					++count;
				}
				//set temp
				auto* temp{ traverse->right };
				auto to_insert{ new _NODE_{data} };
				//disconnect nodes and connect with new node
				traverse->right = to_insert;
				to_insert->left = traverse;
				//the other side
				temp->left = to_insert;
				to_insert->right = temp;
				//update length, pointer dangling and return statement
				++length_;
				traverse = nullptr;
				temp = nullptr;
				to_insert = nullptr;
				return true;
			}
			//else...
			auto* traverse{ tail_ };
			auto count{ length_ - 1 };
			//traverse list backwards
			while (count > index + 1)
			{
				traverse = traverse->left;
				--count;
			}
			//set temp
			auto* temp{ traverse->left };
			auto to_insert{ new _NODE_{data} };
			//disconnect nodes and connect with new node
			traverse->left = to_insert;
			to_insert->right = traverse;
			//the other side
			temp->right = to_insert;
			to_insert->left = temp;
			//update length, pointer dangling and return statement
			++length_;
			traverse = nullptr;
			temp = nullptr;
			to_insert = nullptr;
			return true;
		}
		
		bool insert_at(Data_type&& r_ref, const int index)
		{
			if (index == 0) return push(std::move(r_ref));
			if (index == length_) append(std::move(r_ref));
			//OUT OF BOUNDS
			if (index > length_) throw 0;
			if (index <= ((length_ - 1) / 2))
			{
				auto* traverse{ head_ };
				size_t count{ 0 };
				//traverse list
				while (count < index - 1)
				{
					traverse = traverse->right;
					++count;
				}
				//set temp
				auto* temp{ traverse->right };
				auto to_insert{ new _NODE_{ std::move(r_ref) } };
				//disconnect nodes and connect with new node
				traverse->right = to_insert;
				to_insert->left = traverse;
				//the other side
				temp->left = to_insert;
				to_insert->right = temp;
				//update length, pointer dangling and return statement
				++length_;
				traverse = nullptr;
				temp = nullptr;
				to_insert = nullptr;
				return true;
			}
			//else...
			auto* traverse{ tail_ };
			auto count{ length_ - 1 };
			//traverse list backwards
			while (count > index + 1)
			{
				traverse = traverse->left;
				--count;
			}
			//set temp
			auto* temp{ traverse->left };
			auto to_insert{ new _NODE_{ std::move(r_ref) } };
			//disconnect nodes and connect with new node
			traverse->left = to_insert;
			to_insert->right = traverse;
			//the other side
			temp->right = to_insert;
			to_insert->left = temp;
			//update length, pointer dangling and return statement
			++length_;
			traverse = nullptr;
			temp = nullptr;
			to_insert = nullptr;
			return true;
		}
		
		bool insert_at(Data_type* pointer, const int index)
		{
			//copy data pointed to and call insert at given index
			return insert_at(*pointer, index);
		}
		
		bool delete_at(const int index)
		{
			if (head_ == nullptr && tail_ == nullptr) return false;
			if (index == 0) return pull();
			if (index == length_ - 1) return pop();
			if (index > length_ - 1) throw 0;
			//no _head no tail
			if (index <= (length_ - 1) / 2)
			{
				auto* traverse{ head_ };
				size_t count{ 0 };
				while (count < index - 1)
				{
					traverse = traverse->right;
					++count;
				}
				auto* to_delete{ traverse->right };
				auto* next{ to_delete->right };
				//set left and right to connect traverse with next
				traverse->right = next;
				next->left = traverse;
				//delete node, right and left pointers of the to delete node --->NULL
				delete to_delete;
				--length_;
				//pointer dangling
				traverse = nullptr;
				to_delete = nullptr;
				next = nullptr;
				return true;
			}
			auto* traverse{ tail_ };
			auto count{ length_ - 1 };
			//traverse backwards
			while (count > index + 1)
			{
				traverse = traverse->left;
				--count;
			}
			auto* to_delete{ traverse->left };
			auto* previous{ to_delete->left };
			//set left and right to connect previous and traverse
			previous->right = traverse;
			traverse->left = previous;
			//delete node, left and right point to NULL and decrease length
			delete to_delete;
			--length_;
			//pointer dangling
			traverse = nullptr;
			previous = nullptr;
			to_delete = nullptr;
			return true;
		}
		
		//empty list and delete every node
		bool empty() override
		{
			if (head_ == nullptr && tail_ == nullptr) return false;
			if (head_ == tail_)
			{
				delete head_;
				tail_ = nullptr;
				head_ = nullptr;
				//update length
				length_ = 0;
				return true;
			}
			while (pop() && pull()) if (is_empty()) break;
			return true;
		}
		
		bool is_empty() const override
		{
			return length_ == 0;
		}
		
		//getters
		int size() const override
		{
			return length_;
		}

		//retrun head data
		const Data_type& get_head() const
		{
			return head_->data_;
		}

		Data_type& get_head()
		{
			return const_cast<Data_type&> (const_cast<const doubly_list*> (this)->get_head());
		}
		
		const Data_type& get_tail() const
		{
			return tail_->data_;
		}

		//get tail data
		Data_type& get_tail()
		{
			return const_cast<Data_type&> (const_cast<const doubly_list*> (this)->get_tail());
		}
		
		const Data_type& get_at(const int index) const
		{
			if (index == 0) return head_->data_;
			if (index == length_ - 1) return tail_->data_;
			if (index >= length_) throw 0;
			//when the index is less than the half of the list
			if (index <= (length_ - 1) / 2)
			{
				auto* temp{ head_ };
				size_t count{ 0 };
				//traverse forwards list
				while (count < index)
				{
					temp = temp->right;
					//increments count by 1
					++count;
				}
				return temp->data_;
			}
			//when the index is higher than the half of the list
			auto* temp{ tail_ };
			auto count{ length_ - 1 };
			//traverse backwards the list
			while (count > index)
			{
				temp = temp->left;
				--count;

			}
			return temp->data_;
		}

		//non const get_at version
		Data_type& get_at(const int index) override
		{
			return const_cast<Data_type&>(const_cast<const doubly_list*>(this)->get_at(index));
		}
		
		//operator overloading
		Data_type& operator[](const int index)
		{
			return get_at(index);
		}

		//copy assignment operator overload
		doubly_list& operator=(const _DEQ_& list)
		{
			if (&list == this) return *this;
			//delete current list
			if (head_ != nullptr && tail_ != nullptr) this->empty();
			const Data_type _head_temp = list.head_->data_;
			//copy list
			length_ = list.size();
			head_ = new _NODE_{ _head_temp };
			_NODE_ a{ list.head->right }, b{ head_ };
			//copy every node in order
			while (a != nullptr)
			{
				const Data_type temp = a->data_;
				b->right = new _NODE_{ temp };
				//b next left pointer to b
				b->right->left = b;
				a = a->right;
				b = b->right;
			}
			tail_ = b;
			//pointer dangling
			b = nullptr;
			a = nullptr;

			return *this;
		}
		
		//move assignment operator overload
		doubly_list& operator=(_DEQ_&& r_value_list) noexcept
		{
			//self assignment detection
			if (&r_value_list == this) return *this;
			//delete current list first
			if (head_ != nullptr && tail_ != nullptr) this->empty();
			//switch ownership
			head_ = r_value_list.head_;
			tail_ = r_value_list.tail_;
			//pointer dangling, assigned to null and then delete the R list
			r_value_list.head_ = nullptr;
			r_value_list.tail_ = nullptr;
			//return statement
			return *this;
		}
		
		//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		//																					DESTRUCTOR
		//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		~doubly_list()
		{
			//empty list
			while (empty()) if (is_empty()) break;
		}
	};

}
