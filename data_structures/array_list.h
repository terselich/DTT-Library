/*
------------------------------------------------------------------------------------------
							HEADER:       ARRAY_LIST.H
------------------------------------------------------------------------------------------
 Summary:		Sequence data structures that implements list interface

 Authors:		Mateo Terselich

 Started:		05 April 2018

 Collections:	1) ARRAY_LIST
*/
//defines
#pragma once

//includes...
#include "lists.h"
#include <utility>
#include <stdexcept>

namespace dt
{
	//constant dt global
	constexpr int default_array_cap = 10;

	template<class Data_type = int> class array_list final : lists<Data_type>
	{
		using _ARRAY_ = array_list<Data_type>;
		
		//-----------------------------------------------------------------------------------------
		//											DATA MEMBERS
		//-----------------------------------------------------------------------------------------

		int capacity_;
		int length_;
		int front_index;
		//pointer array
		Data_type* array_;
		
		//-----------------------------------------------------------------------------------------
		//										PRIVATE METHOD MEMBERS
		//-----------------------------------------------------------------------------------------

		bool resize(const int new_capacity)
		{
			auto* temp = new Data_type[new_capacity];
			//copy array to new array with new capacity
			for (auto i{ 0 }; i < length_; ++i)
			{
				//transfer ownership of every element
				temp[i] = array_[(front_index + i) % capacity_];
			}
			//free old array
			delete[] array_;
			//point to *temp
			capacity_ = new_capacity;
			//reset front index to 0
			front_index = 0;
			array_ = temp;
			temp = nullptr;		//pointer dangling
			//return statement
			return true;
		}

	//public members
	public:
		
		//-----------------------------------------------------------------------------------------
		//											CONSTRUCTOR
		//-----------------------------------------------------------------------------------------
		
		explicit array_list(Data_type&& r_ref) : capacity_{ default_array_cap }, length_{ 1 },
												 front_index{ 0 }
		{
			//allocate new memory type S times capacity of the array
			array_ = new Data_type[capacity_];
			//move r_ref to first position
			array_[0] = std::move(r_ref);
		}
		
		explicit array_list(const Data_type& data) : capacity_{ default_array_cap }, length_{ 1 }, front_index{ 0 }
		{
			//allocate new memory type S times capacity of the array
			array_ = new Data_type[capacity_];
			//set data to position[0]
			array_[0] = data;
		}
		
		explicit array_list(const Data_type&& fill_with, int&& times) : capacity_{ times },
																   length_{ std::move(times) },
																   front_index{ 0 },
																   array_{ new Data_type[times] }
		{
			//change ownership
			array_[0] = std::move(fill_with);
			//copy from index 0
			for (auto i{ 1 }; i < length_; ++i) array_[i] = array_[0];
		}

		//copy constructor
		array_list(const _ARRAY_& copy) : capacity_{ copy.capacity_ }, length_{ copy.length_ },
										  front_index{ 0 }
		{
			//create new array in the heap
			array_ = new Data_type[capacity_];
			//traverse copy array and copy data organizing array
			for (auto i{ 0 }; i < length_; ++i)
			{
				array_[i] = copy.array_[(copy.front_index + i) % copy.capacity_];
			}
		}
		//move constructor, casting r_list values to R references
		array_list(_ARRAY_&& r_list) noexcept : capacity_{ r_list.capacity_ },
												length_{ r_list.length_ },
												front_index{ r_list.front_index },
												array_{ r_list.array_ }
		{
			//pointer dangling
			r_list.array_ = nullptr;
			//fixing values
			r_list.front_index = 0;
			r_list.length_ = 0;
		}
		
		//-----------------------------------------------------------------------------------------
		//										PUBLIC METHOD MEMBERS
		//-----------------------------------------------------------------------------------------

		//add remove methods, add l value at the end of the list
		bool append(const Data_type& data) override
		{
			//if array_ is null, create a new array default size
			if (array_ == nullptr) array_ =  new Data_type{ default_array_cap };
			//resize case
			else if (length_ >= capacity_) resize(static_cast<int>(capacity_ * 1.5));
			//insert at length index module capacity
			array_[(front_index + length_) % capacity_] = data;
			//increase length
			++length_;
			return true;
		}

		//add r value at the end of the list
		bool append(Data_type&& r_ref) override
		{
			//if array_ is null, create a new array default size
			if (array_ == nullptr) array_ = new Data_type{ default_array_cap };
			//resize case
			else if (length_ >= capacity_) resize(static_cast<int>(capacity_ * 1.5));
			//add end index length 
			array_[(front_index + length_) % capacity_] = std::move(r_ref);
			//increase length
			++length_;
			return true;
		}

		//add copying pointer data at the end of the list
		bool append(Data_type* pointer) override
		{
			return append(*pointer);
		}

		//add l value at the beginning of the list
		bool push(const Data_type& data) override
		{
			//if array_ is null, create a new array default size
			if (array_ == nullptr) array_ = new Data_type{ default_array_cap };
			//resize case
			else if (length_ >= capacity_) resize(static_cast<int>(capacity_ * 1.5));
			//decrement front_index
			if (front_index == 0) front_index = capacity_ - 1;
			//decrement front index
			else --front_index;
			//increment length
			++length_;
			//insert new front value
			array_[front_index] = data;
			return true;
		}

		//add r value at the beginning of the list
		bool push(Data_type&& r_ref) override
		{
			//if array_ is null, create a new array default size
			if (array_ == nullptr) array_ = new Data_type{ default_array_cap };
			//resize case
			else if (length_ >= capacity_) resize(static_cast<int>(capacity_ * 1.5));
			//decrement front_index
			if (front_index == 0) front_index = capacity_ - 1;
			else --front_index;
			//increment length new value in the list
			++length_;
			//insert new front value
			array_[front_index] = std::move(r_ref);
			return true;
		}

		//add copying data from pointer at the beginning of the list
		bool push(Data_type* pointer) override
		{
			return push(*pointer);
		}

		//remove last element
		bool pop() override
		{
			if (length_ == 0) throw std::range_error("Array length_ is 0");
			if (length_ < (capacity_ / 5)) resize(capacity_ / 2);
			//else..
			--length_;
			return true;
		}

		//remove first element
		bool pull() override
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
		bool shrink()
		{
			return resize(length_);
		}

		//remove all elements
		bool empty() override
		{
			if (length_ == 0) return false;
			length_ = 0;
			front_index = 0;
			return true;
		}

		//check if is empty
		bool is_empty() const override
		{
			return length_ == 0;
		}
		
		//getters
		int size() const override
		{
			return length_;
		}
		
		int capacity() const
		{
			return capacity_;
		}
		
		Data_type& get_at(const int index) const
		{
			if (index >= length_) throw std::out_of_range("Out of bounds index");
			return array_[(front_index + index) % capacity_];
		}
		
		Data_type& get_at(const int index) override
		{
			return const_cast<Data_type&>(const_cast<const array_list*>(this)->get_at(index));
		}
		
		//operator overloading copy assignment operator
		auto operator=(const _ARRAY_& copy) ->array_list&
		{
			//self assignment avoidance, (by address)
			if (&copy == this) return *this;
			//if copy copy fits onto *this
			if (this->capacity_ >= copy.capacity_)
			{
				this->front_index = 0;
				//copy value
				for (auto i{ 0 }; i < copy.length_; ++i) this->array_[i] = copy.array_[(copy.front_index + i) % copy.capacity_];
				//update length
				this->length_ = copy.length_;
				return *this;
			}
			//else..
			delete[] array_;
			//allocate new size array
			array_ = new Data_type[copy.capacity_];
			this->capacity_ = copy.capacity_;
			//copy elements, and organize array
			this->front_index = 0;
			//copy value, organize them as regular array
			for (auto i{ 0 }; i < copy.length_; ++i) this->array_[i] = copy.array_[(copy.front_index + i) % copy.capacity_];
			//update length
			this->length_ = copy.length_;
			return *this;
		}
		
		auto operator=(_ARRAY_&& r_list) noexcept -> array_list&
		{
			//self assignment detection
			if (&r_list == this) return *this;
			delete[] array_;
			//create new array, copy front, length, array and capacity
			this->capacity_ = r_list.capacity_;
			this->length_ = r_list.length_;
			this->front_index = r_list.front_index;
			this->array_ = std::move(r_list.array_);
			//pointer dangling case, fixed r_list values
			r_list.array_ = nullptr;
			r_list.length_ = 0;
			r_list.front_index = 0;
			//return this
			return *this;
		}
		
		//[]
		Data_type& operator[](const int index)
		{
			if (index >= length_) throw std::out_of_range("Out of bounds index");
			//when is less than length(in bounds case)
			return array_[(front_index + index) % capacity_];
		}
		
		//-----------------------------------------------------------------------------------------
		//											DESTRUCTOR
		//-----------------------------------------------------------------------------------------
		
		~array_list()
		{
			delete[] array_;
			array_ = nullptr;
		}
	};
}

