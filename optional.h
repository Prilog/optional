#pragma once
#include <utility>

template <typename T>
struct optional {
	optional() {}
	optional(T const& arg)
	{
		empty = false;
		new (&data) T(arg);
	}
	optional(optional const& arg) 
	{
		empty = arg.empty;
		if (!empty) {
			new (&data) T(*arg);
		}
	}
	~optional() {
		free_data();
	}
	optional& operator= (optional const& arg) 
	{
		if (this == &arg) {
			return *this;
		}
		if (!empty) {
			if (!arg.empty) {
				data = arg.data;
				empty = false;
			}
			else {
				free_data();
			}
		}
		else {
			if (!arg.empty) {
				data = arg.data;
				empty = false;
			}
		}
		return *this;
	}
	void clear()
	{
		free_data();
	}
	explicit operator bool() const
	{
		return !empty;
	}

	T& operator*()
	{
		return *reinterpret_cast<T*> (&data);
	}
	T const& operator*() const
	{
		return *reinterpret_cast<const T *>(&data);
	}
	T* operator->()
	{
		return reinterpret_cast<T*>(&data);
	}
	T const* operator->() const
	{
		return reinterpret_cast<T const*>(&data);
	}

	friend bool operator<(optional const& arg2, optional const& arg)
	{
		if (arg2.empty) {
			return !(arg.empty);
		}
		else {
			if (arg.empty) {
				return false;
			}
			return (*arg2) < (*arg);
		}
	}
	friend bool operator<=(optional const& arg2, optional const& arg)
	{
		if (arg2.empty) {
			return true;
		}
		else {
			if (arg.empty) {
				return false;
			}
			return (*arg2) <= (*arg);
		}
	}
	friend bool operator==(optional const& arg2, optional const& arg)
	{
		if (arg2.empty) {
			return (arg.empty);
		}
		else {
			if (arg.empty) {
				return false;
			}
			return (*arg2) == (*arg);
		}
	}
	friend bool operator!=(optional const& arg2, optional const& arg)
	{
		if (arg2.empty) {
			return !(arg.empty);
		}
		else {
			if (arg.empty) {
				return true;
			}
			return (*arg2) != (*arg);
		}
	}
	friend bool operator>(optional const& arg2, optional const& arg)
	{
		if (arg2.empty) {
			return false;
		}
		else {
			if (arg.empty) {
				return true;
			}
			return (*arg2) > (*arg);
		}
	}
	friend bool operator>=(optional const& arg2, optional const& arg)
	{
		if (arg2.empty) {
			return (arg.empty);
		}
		else {
			if (arg.empty) {
				return true;
			}
			return (*arg2) >= (*arg);
		}
	}

	friend void swap(optional& a, optional& b)
	{
		if (a.empty && b.empty) {
			return;
		}
		if (a.empty) {
			a.create_data(b.data);
			b.free_data();
			a.empty = false;
		}
		else if (b.empty) {
			b.create_data(a.data);
			a.free_data();
			b.empty = false;
		}
		else {
			T* x = reinterpret_cast<T*>(&a.data);
			T* y = reinterpret_cast<T*>(&b.data);
			std::swap(*x, *y);
		}
	}

private:
	typename std::aligned_storage<sizeof(T), alignof(T)>::type data;
	bool empty = true;

	void create_data(typename std::aligned_storage<sizeof(T), alignof(T)>::type const& arg) {
		new (&data) T(*reinterpret_cast<T const *>(&arg));
	}

	void free_data()
	{
		if (!empty) {
			empty = true;
			reinterpret_cast<T&>(data).~T();
		}
	}
};
