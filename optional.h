#pragma once
#include <cstdio>

template <typename T>
struct optional {
	optional() {};
	optional(T const& arg)
	{
		data = new T(arg);
	}
	optional(optional const& arg) 
	{
		if (arg.data == nullptr) {
			data = nullptr;
			return;
		}
		data = new T(*arg.data);
	}
	optional& operator= (optional const& arg) 
	{
		free_data();
		if (arg.data != nullptr) {
			data = new T(*arg.data);
		}
		return *this;
	}
	void clear()
	{
		free_data();
	}
	explicit operator bool() const
	{
		return !(data == nullptr);
	}

	T& operator*()
	{
		return *data;
	}
	T const& operator*() const
	{
		return *data;
	}
	T* operator->()
	{
		return data;
	}
	T const* operator->() const
	{
		return data;
	}

	friend bool operator<(optional const& arg2, optional const& arg)
	{
		if (arg2.data == nullptr) {
			return !(arg.data == nullptr);
		}
		else {
			if (arg.data == nullptr) {
				return false;
			}
			return (*arg2.data) < (*arg.data);
		}
	}
	friend bool operator<=(optional const& arg2, optional const& arg)
	{
		if (arg2.data == nullptr) {
			return true;
		}
		else {
			if (arg.data == nullptr) {
				return false;
			}
			return (*arg2.data) <= (*arg.data);
		}
	}
	friend bool operator==(optional const& arg2, optional const& arg)
	{
		if (arg2.data == nullptr) {
			return (arg.data == nullptr);
		}
		else {
			if (arg.data == nullptr) {
				return false;
			}
			return (*arg2.data) == (*arg.data);
		}
	}
	friend bool operator!=(optional const& arg2, optional const& arg)
	{
		if (arg2.data == nullptr) {
			return !(arg.data == nullptr);
		}
		else {
			if (arg.data == nullptr) {
				return true;
			}
			return (*arg2.data) != (*arg.data);
		}
	}
	friend bool operator>(optional const& arg2, optional const& arg)
	{
		if (arg2.data == nullptr) {
			return false;
		}
		else {
			if (arg.data == nullptr) {
				return true;
			}
			return (*arg2.data) > (*arg.data);
		}
	}
	friend bool operator>=(optional const& arg2, optional const& arg)
	{
		if (arg2.data == nullptr) {
			return (arg.data == nullptr);
		}
		else {
			if (arg.data == nullptr) {
				return true;
			}
			return (*arg2.data) >= (*arg.data);
		}
	}

	friend void swap(optional& a, optional& b)
	{
		std::swap(a.data, b.data);
	}

private:
	T* data = nullptr;
	void free_data()
	{
		if (data != nullptr) {
			delete data;
			data = nullptr;
		}
	}
};
