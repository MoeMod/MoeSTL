#pragma once

/*
	list (doubly-linked list)

	TODO:
	* full exceptions support
	* insert & remove funcs
*/

#include <initializer_list>
using std::initializer_list;
#include <memory>
using std::allocator;
using std::allocator_traits;

#include "extra/allocator_base.h"

namespace MoeSTL {

	namespace list_internal
	{
		template<class T>
		struct list_node
		{
			list_node *next;
			list_node *prev;
		};

		template<class T>
		struct list_node_with_data : list_node<T>
		{
			T data;
		};

		template<class T>
		struct list_members : list_node<T>
		{
			list_members() : list_node{nullptr, nullptr }, m_iSize(0) {}
			list_node *&head() { return next; }
			list_node *&tail() { return prev; }
			size_t m_iSize;
		};

		template<class T>
		class const_list_iterator
		{
		public:
			using iterator_category = std::bidirectional_iterator_tag;
			using value_type = const T;
			using difference_type = ptrdiff_t;
			using pointer = value_type * ;
			using reference = value_type & ;

			explicit const_list_iterator(list_node<value_type> *p) : ptr(p) {}
			const_list_iterator& operator++() { return ptr = ptr->next, *this; }
			const_list_iterator operator++(int) { auto ret = *this; ptr = ptr->next; return ret; }
			const_list_iterator& operator--() { return ptr = ptr->prev, *this; }
			const_list_iterator operator--(int) { auto ret = *this; ptr = ptr->prev; return ret; }

			bool operator==(const_list_iterator other) const { return ptr == other.ptr; }
			bool operator!=(const_list_iterator other) const { return !(*this == other); }
			bool operator<(const_list_iterator other) const { return ptr < other.ptr; }
			bool operator<=(const_list_iterator other) const { return ptr <= other.ptr; }
			bool operator>(const_list_iterator other) const { return ptr > other.ptr; }
			bool operator>=(const_list_iterator other) const { return ptr >= other.ptr; }

			reference operator*() { return static_cast<list_node_with_data<value_type> *>(ptr)->data; }
			pointer operator->() { return &(static_cast<list_node_with_data<value_type> *>(ptr)->data); }
		private:
			list_node<value_type> *ptr;
		};

		template<class T>
		class list_iterator
		{
		public:
			using iterator_category = std::bidirectional_iterator_tag;
			using value_type = T;
			using difference_type = ptrdiff_t;
			using pointer = value_type * ;
			using reference = value_type & ;

			explicit list_iterator(list_node<value_type> *p) : ptr(p) {}
			list_iterator& operator++() { return ptr = ptr->next, *this; }
			list_iterator operator++(int) { auto ret = *this; ptr = ptr->next; return ret; }
			list_iterator& operator--() { return ptr = ptr->prev, *this; }
			list_iterator operator--(int) { auto ret = *this; ptr = ptr->prev; return ret; }

			bool operator==(list_iterator other) const { return ptr == other.ptr; }
			bool operator!=(list_iterator other) const { return !(*this == other); }
			bool operator<(list_iterator other) const { return ptr < other.ptr; }
			bool operator<=(list_iterator other) const { return ptr <= other.ptr; }
			bool operator>(list_iterator other) const { return ptr > other.ptr; }
			bool operator>=(list_iterator other) const { return ptr >= other.ptr; }

			reference operator*() { return static_cast<list_node_with_data<value_type> *>(ptr)->data; }
			pointer operator->() { return &(static_cast<list_node_with_data<value_type> *>(ptr)->data); }

			operator const_list_iterator<T>() { return const_list_iterator<T>(ptr); }
		private:
			list_node<value_type> *ptr;
		};
	}

template<
	class T,
	class Allocator = std::allocator<T>
> class list : private list_internal::list_members<T>, public allocator_base<Allocator>
{
public:
	using value_type = T;
	using allocator_type = Allocator;
	using size_type = size_t;
	using difference_type = ptrdiff_t;
	using reference = T & ;
	using const_reference = const T &;
	using pointer = typename std::allocator_traits<Allocator>::pointer;
	using const_pointer = typename std::allocator_traits<Allocator>::const_pointer;


	using iterator = list_internal::list_iterator<T>;
	using const_iterator = list_internal::const_list_iterator<T>;
	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;

private:
	using node_t = list_internal::list_node<T>;
	using node_with_data_t = list_internal::list_node_with_data<T>;

	using rebind_alloc = typename std::allocator_traits<Allocator>::template rebind_alloc<node_with_data_t>;
	using rebind_traits = typename std::allocator_traits<rebind_alloc>;
	
	rebind_alloc get_rebind()
	{
		return get_allocator();
	}

public:
	~list() { clear(); }

	list()
		: allocator_base({}) {}
	explicit list(const Allocator& alloc)
		: allocator_base(alloc) {}

	reference front()
	{
		return *static_cast<node_with_data_t *>(head())->data;
	}
	const_reference front() const
	{
		return *static_cast<node_with_data_t *>(head())->data;
	}
	reference back()
	{
		return *static_cast<node_with_data_t *>(tail())->data;
	}
	const_reference back() const
	{
		return *static_cast<node_with_data_t *>(tail())->data;
	}

	iterator begin() noexcept
	{
		return iterator(head());
	}
	iterator end() noexcept
	{
		return iterator(static_cast<node_t *>(this)); // prev=tail(), next=head(), no extra memory needed
	}
	const_iterator begin() const noexcept
	{
		return cbegin();
	}
	const_iterator end() const noexcept
	{
		return cend();
	}
	const_iterator cbegin() const noexcept
	{
		return const_iterator(head());
	}
	const_iterator cend() const noexcept
	{
		return const_iterator(static_cast<node_t *>(this));
	}

	reverse_iterator rbegin()
	{
		return reverse_iterator(end());
	}
	reverse_iterator rend() noexcept
	{
		return reverse_iterator(begin());
	}
	const_reverse_iterator rbegin() const noexcept
	{
		return crbegin();
	}
	const_reverse_iterator rend() const noexcept
	{
		return crend();
	}
	const_reverse_iterator crbegin() const noexcept
	{
		return reverse_iterator(cend());
	}
	const_reverse_iterator crend() const noexcept
	{
		return reverse_iterator(cbegin());
	}

	bool empty() const noexcept
	{
		return m_iSize == 0;
	}
	size_type size() const noexcept
	{
		return m_iSize;
	}
	size_type max_size() const noexcept
	{
		return -1;
	}

	void clear() noexcept
	{
		node_t *p = tail();
		while (p && p != this) // 'this' is a placeholder for post-end() and pre-begin()
		{
			node_with_data_t *cur = static_cast<node_with_data_t *>(p);
			p = p->prev;

			cur->data.~T(); // deconstruct
			get_rebind().deallocate(cur, 1); // free memory
		}

		tail() = head() = nullptr;
		m_iSize = 0;
	}

	void push_back(const T& value)
	{
		node_with_data_t *p = get_rebind().allocate(1);

		try
		{
			new(&p->data) T(value);
		}
		catch (...)
		{
			get_rebind().deallocate(p, 1);
			throw;
		}

		if (!head())
			head() = p;
		if (!tail())
		{
			p->prev = this;
		}
		else
		{
			tail()->next = p;
			p->prev = tail();
		}
		this->prev = p;
		p->next = this;

		++m_iSize;
	}

	void push_back(T&& value)
	{
		node_with_data_t *p = get_rebind().allocate(1);

		try
		{
			new(&p->data) T(std::move(value));
		}
		catch (...)
		{
			get_rebind().deallocate(p, 1);
			throw;
		}

		if (!head())
			head() = p;
		if (!tail())
		{
			p->prev = this;
		}
		else
		{
			tail()->next = p;
			p->prev = tail();
		}
		this->prev = p;
		p->next = this;

		++m_iSize;
	}

	template< class... Args >
	void emplace_back(Args&&... args)
	{
		node_with_data_t *p = get_rebind().allocate(1);

		try
		{
			new(&p->data) T(std::forward<Args>(args)...);
		}
		catch (...)
		{
			get_rebind().deallocate(p, 1);
			throw;
		}

		if (!head())
			head() = p;
		if (!tail())
		{
			p->prev = this;
		}
		else
		{
			tail()->next = p;
			p->prev = tail();
		}
		this->prev = p;
		p->next = this;

		++m_iSize;
	}
	void pop_back()
	{
		node_with_data_t *p = static_cast<node_with_data_t *>(tail());
		tail() = p->prev;
		tail()->next = this;

		p->data.~T();
		get_rebind().deallocate(p, 1);
	}

};

}