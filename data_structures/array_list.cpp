#include "pch.h"
#include "array_list.h"

namespace dt
{
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//																			PRIVATE METHOD MEMBERS
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	template<class S> bool array_list<S>::resize(const size_t new_capacity)
	{
		auto* temp = new S[new_capacity];
		//copy array to new array with new capacity
		for (size_t i{ 0 }; i < length_; ++i)
		{
			//transfer ownership of every element
			temp[i] = std::move(array_[(front_index + i) % capacity_]);
		}
		//free old array
		delete[] array_;
		//point to *temp
		capacity_ = new_capacity;
		array_ = temp;
		temp = nullptr;		//pointer dangling
		//return statement
		return true;
	}
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//																				CONSTRUCTORS
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	template<class S> array_list<S>::array_list(size_t&& capacity) : capacity_{ std::move(capacity) }, length_{ 0 }, front_index{ 0 }, array_{ new S[capacity_] } {}
	//constructor r value
	template<class S> array_list<S>::array_list(S&& r_ref) : capacity_{ 10 }, length_{ 1 }, front_index{ 0 }
	{
		//allocate new memory type S times capacity of the array
		array_ = new S[capacity_];
		//move r_ref to first position
		array_[0] = std::move(r_ref);
	}
	//constructor l value reference
	template<class S> array_list<S>::array_list(const S& data) : capacity_{ 10 }, length_{ 1 }, front_index{ 0 }
	{
		//allocate new memory type S times capacity of the array
		array_ = new S[capacity_];
		//set data to position[0]
		array_[0] = data;
	}
	//special constructor
	template<class S> array_list<S>::array_list(const S&& fill_with, const size_t times) : capacity_{ times }, length_{ times }, front_index{ 0 }, array_{ new S[times] }
	{
		//change ownership
		array_[0] = std::move(fill_with);
		//copy from index 0
		for (size_t i{ 1 }; i < times; ++i) array_[i] = array_[0];
	}
	//copy constructor
	template<class S> array_list<S>::array_list(const array_list<S>& copy) : capacity_{ copy.capacity_ }, length_{ copy.length_ }, front_index{ 0 }
	{
		//create new array in the heap
		array_ = new S[capacity_];
		//traverse copy array and copy data organizing array
		for (size_t i{ 0 }; i < length_; ++i)
		{
			array_[i] = copy.array_[(copy.front_index + i) % copy.capacity_];
		}
	}
	//move constructor
	template<class S> array_list<S>::array_list(array_list<S>&& r_list) noexcept : capacity_{ r_list.capacity_ }, length_{ r_list.length_ }, front_index{ r_list.front_index }, array_{ r_list.array_ }
	{
		//pointer dangling
		r_list.array_ = nullptr;
	}
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//																			PUBLIC METHOD MEMBERS
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//add l value at the end of the list
	template<class S> bool array_list<S>::append(const S& data)
	{
		//resize case
		if (length_ >= capacity_) resize(static_cast<size_t>(capacity_ * 1.5));
		//insert at length index module capacity
		array_[(front_index + length_) % capacity_] = data;
		//increase length
		++length_;
		return true;
	}
	//add r value at the end of the list
	template<class S> bool array_list<S>::append(S&& r_ref)
	{
		//resize case
		if (length_ >= capacity_) resize(static_cast<size_t>(capacity_ * 1.5));
		//add end index length 
		array_[(front_index + length_) % capacity_] = std::move(r_ref);
		//increase length
		++length_;
		return true;
	}
	//add copying pointer data at the end of the list
	template<class S> bool array_list<S>::append(S* pointer)
	{
		return append(*pointer);
	}
	//add l value at the beginning of the list
	template<class S> bool array_list<S>::push(const S& data)
	{
		//resize case
		if (length_ >= capacity_) resize(static_cast<size_t>(capacity_ * 1.5));
		//decrement front_index
		if (front_index == 0) front_index = capacity_ - 1;
		else --front_index;
		//insert new front value
		array_[front_index] = data;
		return true;
	}
	//add r value at the beginning of the list
	template<class S> bool array_list<S>::push(S&& r_ref)
	{
		//resize case
		if (length_ >= capacity_) resize(static_cast<size_t>(capacity_ * 1.5));
		//decrement front_index
		if (front_index == 0) front_index = capacity_ - 1;
		else --front_index;
		//insert new front value
		array_[front_index] = std::move(r_ref);
		return true;
	}
	//add copying data from pointer at the beginning of the list
	template<class S> bool array_list<S>::push(S* pointer)
	{
		return push(*pointer);
	}
	//remove last element
	template<class S> bool array_list<S>::pop()
	{
		if (length_ == 0) throw std::range_error("Array length_ is 0");
		if (length_ < (capacity_ / 5)) resize(capacity_ / 2);
		//else..
		--length_;
		return true;
	}
	//remove first element
	template<class S> bool array_list<S>::pull()
	{
		if (length_ == 0) throw std::range_error("Array length_ is 0");
		//else..., pre increment statement module capacity
		if (length_ < (capacity_ / 5)) resize(capacity_ / 2);
		front_index = ++front_index % capacity_;
		//decrease length
		--length_;
		return true;
	}
	//shrink to fit list
	template<class S> bool array_list<S>::shrink()
	{
		return resize(length_);
	}
	//remove all elements
	template<class S> bool array_list<S>::empty()
	{
		if (length_ == 0) return false;
		length_ = 0;
		front_index = 0;
		return true;
	}
	//check if is empty
	template<class S> bool array_list<S>::is_empty() const
	{
		return length_ == 0;
	}
	//return length_
	template<class S> size_t array_list<S>::size() const
	{
		return length_;
	}
	//return capacity_
	template<class S> size_t array_list<S>::capacity() const
	{
		return capacity_;
	}
	//get at index given
	template<class S> S& array_list<S>::get_at(const size_t index) const
	{
		if (index >= length_) throw std::out_of_range("Out of bounds index");
		return array_[(front_index + index) % capacity_];
	}
	template<class S> S& array_list<S>::get_at(const size_t index)
	{
		if (index >= length_) throw std::out_of_range("Out of bounds index");
		return const_cast<S&>(const_cast<const array_list>(this)->get_at(index));
	}
	//copy assignment operator
	template<class S> array_list<S>& array_list<S>::operator=(const array_list& copy)
	{
		//self assignment avoidance, (by address)
		if (&copy == this) return *this;
		//if copy copy fits onto *this
		if (this->capacity_ >= copy.capacity_)
		{
			this->front_index = 0;
			//copy value
			for (size_t i{ 0 }; i < copy.length_; ++i) this->array_[i] = copy.array_[(copy.front_index + i) % copy.capacity_];
			//update length
			this->length_ = copy.length_;
			return *this;
		}
		//else..
		delete[] array_;
		//allocate new size array
		array_ = new S[copy.capacity_];
		this->capacity_ = copy.capacity_;
		//copy elements, and organize array
		this->front_index = 0;
		//copy value, organize them as regular array
		for (size_t i{ 0 }; i < copy.length_; ++i) this->array_[i] = copy.array_[(copy.front_index + i) % copy.capacity_];
		//update length
		this->length_ = copy.length_;
		return *this;
	}
	//move assignment operator
	template<class S> array_list<S>& array_list<S>::operator=(array_list&& r_list) noexcept
	{
		delete[] array_;
		//create new array
		this->capacity_ = std::move(r_list.capacity_);
		this->length_ = std::move(r_list.length_);
		this->front_index = std::move(r_list.front_index);
		this->array_ = new S[capacity_];
		//copy
		for (auto i{ 0 }; i < this->length_; ++i) this->array_[(front_index + i) % capacity_] = std::move(r_list.array_[(front_index + i) % capacity_]);
		return *this;
	}
	//indexing operator overloading
	template<class S> S& array_list<S>::operator[](const size_t index)
	{
		if (index >= length_) throw std::out_of_range("Out of bounds index");
		//when is less than length(in bounds case)
		return array_[(front_index + index) % capacity_];
	}
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//																					DESTRUCTOR
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	template<class S> array_list<S>::~array_list()
	{
		delete[] array_;
		array_ = nullptr;
	}
}
