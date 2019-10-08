/*
------------------------------------------------------------------------------------------
							HEADER:       RB_NODE.H
------------------------------------------------------------------------------------------
 Summary:		Helper to build tree map, bool check if the node is black or red

 Authors:		Mateo Terselich

 Started:		7 September 2019

 Collections:	1) ENUM COLOR
				2) RB_NODE
*/
//definitions
#pragma once
//includes
#include "doubly_node.h"

namespace dt
{
	//enum red/black
	enum COLOR { _RED_, _BLACK_ };
										//private inheritance
	template <class Pair> class rb_node : doubly_node<Pair>
	{
		template<class Hashed, class Value> friend class tree_map;
		//----------------------------------
		//			DATA MEMBERS
		//----------------------------------
		/*
									NODE
							+-+------ -------+-+
					NULL<----o| key  | color |o---->NULL
							+-+------|-------+-+
									 |
									 V
								   PARENT
		*/
		bool color_;
		doubly_node<Pair> * parent_;
		//----------------------------------
		//				CONSTRUCTORS
		//----------------------------------
		//private constructors only friend classes can instantiate it
		explicit rb_node( Pair&& r_ref) noexcept : doubly_node<Pair>{ std::move(r_ref) }, color_{ _RED_ }, parent_{ nullptr } {}
		explicit rb_node(const Pair& data) : doubly_node<Pair>{ data }, color_{ _RED_ }, parent_{ nullptr } {}
		//----------------------------------
		//		PRIVATE METHOD MEMBERS
		//----------------------------------
		//getter and setter
		const Pair& get_key() const
		{
			return this->key_;
		}
		//casting conversion
		Pair& get_key()
		{
			return const_cast<Pair&>(const_cast<const rb_node*>(this)->get_key());
		}
		void set_key(const Pair& data)
		{
			this->key_ = data;
		}
	public:
		//copy constructor
		rb_node(const rb_node<Pair>& copy) : doubly_node<Pair>{ copy }, color_{ copy.color_ }, parent_{ nullptr } {}
		//move constructor
		rb_node(rb_node<Pair>&& r_ref) noexcept : doubly_node<Pair>{ r_ref }, color_{ r_ref.color_ }, parent_{ nullptr } {}
		//----------------------------------
		//		PRIVATE METHOD MEMBERS
		//----------------------------------
		rb_node<Pair>& operator=(const rb_node<Pair>& copy)
		{
			//compare addresses
			if (&copy == this) return *this;
			//else copy values
			this->key_ = copy.key_;
			this->color_ = copy.color_;
			parent_ = nullptr;
			//return this...
			return *this;
		}
		rb_node<Pair>& operator=(rb_node<Pair>&& r_ref) noexcept
		{
			this->key_ = r_ref.key_;
			this->color_ = r_ref.color_;
			parent_ = nullptr;
			return *this;
		}
		//type node fast assignment
		rb_node<Pair>& operator=(Pair&& r_ref)
		{
			this->key_ = r_ref;
			//return this instance
			return *this;
		}
		//----------------------------------
		//				DESTRUCTOR
		//----------------------------------
		~rb_node()
		{
			parent_ = nullptr;
		}
		
		
	};

}