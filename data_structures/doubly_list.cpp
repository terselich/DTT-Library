#include "pch.h"
#include "doubly_list.h"

namespace dt
{
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//																				CONSTRUCTORS
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	template <class S> doubly_list<S>::doubly_list() : head_{ nullptr }, tail_{ nullptr }, length_{ 0 }{}
	template<class S> doubly_list<S>::doubly_list(S&& r_ref) noexcept : length_{ 1 }
	{
		head_ = new doubly_node<S>{ std::move(r_ref) };
		tail_ = head_;
	}
	template <class S> doubly_list<S>::doubly_list(const S& data) : head_{ new doubly_node<S>{ data } }, tail_{ head_ }, length_{ 0 } {}
	//deep copy
	template <class S> doubly_list<S>::doubly_list(const doubly_list<S>& copy) : length_{ copy.size() }
	{
		const S _head_temp = copy.head_->data_;
		//copy list
		head_ = new doubly_node<S>{ _head_temp };
		doubly_node<S> a{ copy.head->right }, b{ head_ };
		//copy every node in order
		while (a != nullptr)
		{
			const S temp = a->data_;
			b->right = new doubly_node<S>{ temp };
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
	template <class S> doubly_list<S>::doubly_list(const doubly_list<S>&& ref) noexcept : head_{ ref.head_ }, tail_{ ref.tail_ }, length_{ ref.size() }
	{
		//pointer dangling for deletion
		ref.head_ = nullptr;
		ref.tail_ = nullptr;
	}
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//																			PUBLIC METHOD MEMBERS
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//append: Add node at the end of the list, push: Add node at the beginning
	template<class S> bool doubly_list<S>::append(const S& data)
	{
		if (head_ == nullptr && tail_ == nullptr || length_ == 0)
		{
			head_ = new doubly_node<S>{ data };
			//tail points to head too
			tail_ = head_;
			++length_;
			return true;
		}
		if (head_ == tail_)
		{
			tail_ = new doubly_node<S>{ data };
			//head points to tail and tail to head (doubly linked list)
			head_->right = tail_;
			tail_->left = head_;
			length_++;
			return true;
		}
		auto* temp{ new doubly_node<S>{ data } };
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
	template<class S> bool doubly_list<S>::append(S&& r_ref) noexcept
	{
		if (head_ == nullptr && tail_ == nullptr || length_ == 0)
		{
			head_ = new doubly_node<S>{ std::move(r_ref) };
			//tail points to head too
			tail_ = head_;
			++length_;
			return true;
		}
		if (head_ == tail_)
		{
			tail_ = new doubly_node<S>{ std::move(r_ref) };
			//head points to tail and tail to head (doubly linked list)
			head_->right = tail_;
			tail_->left = head_;
			length_++;
			return true;
		}
		auto* temp{ new doubly_node<S>{ std::move(r_ref) } };
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
	template<class S> bool doubly_list<S>::append(S* pointer)
	{
		//copy data from pointer dereference and call append
		return append(*pointer);
	}
	template<class S> bool doubly_list<S>::push(const S& data)
	{
		if (head_ == nullptr && tail_ == nullptr)
		{
			head_ = new doubly_node<S>{ data };
			tail_ = head_;
			//increase and return
			length_++;
			return true;
		}
		if (head_ == tail_)	//addresses (*==*)
		{
			head_ = new doubly_node<S>{ data };
			//connecting list
			head_->right = tail_;
			tail_->left = head_;
			//return and increment length
			length_++;
			return true;
		}
		auto* temp = head_;
		head_ = new doubly_node<S>{ data };
		//connect new head node with the list
		head_->right = temp;
		temp->left = head_;
		//increase and return
		temp = nullptr;
		length_++;
		return true;
	}
	template<class S> bool doubly_list<S>::push(S&& r_ref) noexcept
	{
		if (head_ == nullptr && tail_ == nullptr)
		{
			head_ = new doubly_node<S>{ std::move(r_ref) };
			tail_ = head_;
			//increase and return
			length_++;
			return true;
		}
		if (head_ == tail_)	//addresses (*==*)
		{
			head_ = new doubly_node<S>{ std::move(r_ref) };
			//connecting list
			head_->right = tail_;
			tail_->left = head_;
			//return and increment length
			length_++;
			return true;
		}
		auto* temp = head_;
		head_ = new doubly_node<S>{ std::move(r_ref) };
		//connect new head node with the list
		head_->right = temp;
		temp->left = head_;
		//increase and return
		temp = nullptr;
		length_++;
		return true;
	}
	template<class S> bool doubly_list<S>::push(S* pointer)
	{
		//copy data that pointer points and call push
		return push(*pointer);
	}
	//pop: Delete the last node, pull: Delete the first node
	template<class S> bool doubly_list<S>::pop()
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
	template<class S> bool doubly_list<S>::pull()
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
	template<class S> bool doubly_list<S>::is_empty() const
	{
		return length_ == 0;
	}
	//empty list
	template<class S> bool doubly_list<S>::empty()
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
	//getters
	template<class S> size_t doubly_list<S>::size() const
	{
		return length_;
	}
	template<class S> const S& doubly_list<S>::get_head() const
	{
		return head_->data_;
	}
	template<class S> S& doubly_list<S>::get_head()
	{
		return const_cast<S&> (const_cast<const doubly_list*> (this)->get_head());
	}
	template<class S> const S& doubly_list<S>::get_tail() const
	{
		return tail_->data_;
	}
	template<class S> S& doubly_list<S>::get_tail()
	{
		return const_cast<S&> (const_cast<const doubly_list*> (this)->get_tail());
	}
	//get at index given
	template<class S> const S& doubly_list<S>::get_at(const size_t index) const
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
			return *temp;
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
		return *temp;
	}
	//non const version
	template<class S> S& doubly_list<S>::get_at(const size_t index)
	{
		return const_cast<S&>(const_cast<const doubly_list*>(this)->get_at(index));
	}
	template<class S> S& doubly_list<S>::operator[](const size_t index)
	{
		return get_at(index);
	}
	//insert at delete at...
	template<class S> bool doubly_list<S>::insert_at(const S& data, const size_t index)
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
			auto to_insert{ new doubly_node<S>{data} };
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
		auto to_insert{ new doubly_node<S>{data} };
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
	template<class S> bool doubly_list<S>::insert_at(S&& r_ref, const size_t index)
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
			auto to_insert{ new doubly_node<S>{ std::move(r_ref) } };
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
		auto to_insert{ new doubly_node<S>{ std::move(r_ref) } };
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
	template<class S> bool doubly_list<S>::insert_at(S* pointer, size_t index)
	{
		//copy data pointed to and call insert at given index
		return insert_at(*pointer, index);
	}
	template<class S> bool doubly_list<S>::delete_at(const size_t index)
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
	template<class S> doubly_list<S>& doubly_list<S>::operator=(const doubly_list<S>& list)
	{
		if (&list == this) return *this;
		//delete current list
		if (head_ != nullptr && tail_ != nullptr) this->empty();
		const S _head_temp = list.head_->data_;
		//copy list
		length_ = list.size();
		head_ = new doubly_node<S>{ _head_temp };
		doubly_node<S> a{ list.head->right }, b{ head_ };
		//copy every node in order
		while (a != nullptr)
		{
			const S temp = a->data_;
			b->right = new doubly_node<S>{ temp };
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
	template<class S> doubly_list<S>& doubly_list<S>::operator=(doubly_list<S>&& r_value_list) noexcept
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
	template<class S> doubly_list<S>& doubly_list<S>::operator=(S&& r_value) noexcept
	{
		//empty current list
		if (head_ != nullptr && tail_ != nullptr) this->empty();
		//switch ownership
		head_ = new doubly_node<S>{ std::move(r_value) };
		tail_ = head_;
		length_ = 1;
		//return statement
		return *this;
	}
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//																					DESTRUCTOR
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	template<class S> doubly_list<S>::~doubly_list()
	{
		//empty list
		while (empty()) if (is_empty()) break;
	}
}
