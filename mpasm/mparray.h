#ifndef MPASM_MPASM_MPARRAY_H
#define MPASM_MPASM_MPARRAY_H

#include "stdafx.h"

template<typename T>
class mparray
{
private:
	T * _values;
	size_t _length;

public:
	mparray()
		: _values(nullptr), _length(0) {}
	mparray(T * values, size_t length)
		: _values(values), _length(length) {}

	size_t &length()
	{
		return _length;
	}

	size_t length() const
	{
		return _length;
	}

	T*& ptr()
	{
		return _values;
	}

	T & operator[](size_t index)
	{
		return _values[index];
	}

	const T & operator[](size_t index) const
	{
		return _values[index];
	}

	static void operator delete[](void *ptr)
	{
		mparray<T> * parray = ((mparray<T>*)(ptr));
		delete[] parray->_values;
		parray->_values = nullptr;
		parray->_length = 0;
	}
};

#endif // !MPASM_MPASM_MPARRAY_H
