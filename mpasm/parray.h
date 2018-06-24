/*
* Copyright 2018 Mouse-Produced Games.
* Distributed under the terms of the GNU Lesser General Public Liceense (Version 3, 29 June 2007)
*/

#ifndef MPASM_MPASM_MPARRAY_H
#define MPASM_MPASM_MPARRAY_H

#include "stdafx.h"

template<typename T>
class parray
{
private:
	T * _values;
	psize _length;

public:
	parray()
		: _values(nullptr), _length(0) {}
	parray(T * values, psize length)
		: _values(values), _length(length) {}

	psize &length()
	{
		return _length;
	}

	psize length() const
	{
		return _length;
	}

	T*& ptr()
	{
		return _values;
	}

	T & operator[](psize index)
	{
		return _values[index];
	}

	const T & operator[](psize index) const
	{
		return _values[index];
	}

	static void operator delete[](void *ptr)
	{
		parray<T> * parray = ((parray<T>*)(ptr));
		delete[] parray->_values;
		parray->_values = nullptr;
		parray->_length = 0;
	}
};

#endif // !MPASM_MPASM_MPARRAY_H
