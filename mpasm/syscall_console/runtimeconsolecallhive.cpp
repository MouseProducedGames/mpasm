/*
* Copyright 2018 Mouse-Produced Games.
* Distributed under the terms of the GNU Lesser General Public Liceense (Version 3, 29 June 2007)
*/

#include "stdafx.h"
#include "runtimeconsolecallhive.h"

#include <iostream>
#include <sstream>

#include "../runtime/parray_datacalls.h"
#include "../runtime/ptr_datacalls.h"
#include "../runtime/value_datacalls.h"
#include "../run_context.h"
#include "console_ops.h"
#include "parray.h"

template<typename T>
bool console_parray_operator(uint64_t subcall, context &ctx)
{
	switch ((console_op)subcall)
	{
	default: return false;
	case console_op::getkey:
	{
		std::wstringstream wsb;
		wchar_t wch;
		do
		{
			wch = _getwch();
			wsb << wch;
		} while ((char)wch != '\n' && (char)wch != '\0');
		std::wstring ws = wsb.str();
		parray<T> data(new T[ws.size()], ws.size());
		for (size_t i = 0; i < ws.size(); ++i)
		{
			data[i] = (T)ws[i];
		}
		parray_setdata<T>(ML::Stk, ctx, data);
		return true;
	}
	case console_op::readchar:
	{
		std::wstring ws;
		std::wcin >> ws;
		parray<T> data(new T[ws.size()], ws.size());
		for (size_t i = 0; i < ws.size(); ++i)
		{
			data[i] = (T)ws[i];
		}
		parray_setdata<T>(ML::Stk, ctx, data);
		return true;
	}
	case console_op::writechar:
	{
		parray<T> &data = parray_getdata_restack<T>(ML::Stk, ctx);
		for (size_t i = 0; i < data.length(); ++i)
		{
			wchar_t wc = (wchar_t)data[i];
			if (wc == '\0')
				break;
			wprintf_s(&wc);
		}
		return true;
	}
	case console_op::read:
	{
		std::string ws;
		std::stringstream wsb;
		std::vector<T> values;
		do
		{
			std::cin >> ws;
			if (ws.size() == 0)
			{
				break;
			}
			wsb << ws;
			T data;
			wsb >> data;
			wsb.clear();
			ws.clear();
			values.push_back(data);
		} while (true);
		parray<T> data(new T[values.size()], values.size());
		for (size_t i = 0; i < values.size(); ++i)
		{
			data[i] = values[i];
		}
		parray_setdata<T>(ML::Stk, ctx, data);
		return true;
	}
	case console_op::write:
	{
		parray<T> data = parray_getdata_restack<T>(ML::Stk, ctx);
		std::cout << typeid(data).name() << ':' << (psize)data.ptr() << '[' << data.length() << ']';
		return true;
	}
	}
}

template<typename T>
bool console_ptr_operator(uint64_t subcall, context &ctx)
{
	switch ((console_op)subcall)
	{
	default: return false;
	case console_op::getkey:
	{
		T data = (T)_getwch();
		ptr_setdata<T>(ML::Stk, ctx, new T(data));
		return true;
	}
	case console_op::readchar:
	{
		wchar_t input;
		std::wcin >> input;
		ptr_setdata<T>(ML::Stk, ctx, new T((T)input));
		return true;
	}
	case console_op::writechar:
	{
		wchar_t ch = (wchar_t)(*ptr_getdata_restack<T>(ML::Stk, ctx));
		wprintf_s(&ch);
		return true;
	}
	case console_op::read:
	{
		T input;
		std::cin >> input;
		ptr_setdata<T>(ML::Stk, ctx, new T(input));
		return true;
	}
	case console_op::write:
	{
		std::cout << *ptr_getdata_restack<T>(ML::Stk, ctx);
		return true;
	}
	}
}

template<typename T>
bool console_value_operator(uint64_t subcall, context &ctx)
{
	switch ((console_op)subcall)
	{
	default: return false;
	case console_op::getkey:
	{
		T data = (T)_getwch();
		value_setdata<T>(ML::Stk, ctx, data);
		return true;
	}
	case console_op::readchar:
	{
		wchar_t input;
		std::wcin >> input;
		T data = (T)input;
		value_setdata<T>(ML::Stk, ctx, data);
		return true;
	}
	case console_op::writechar:
	{
		wchar_t ch = (wchar_t)value_getdata_restack<T>(ML::Stk, ctx);
		wprintf_s(&ch);
		return true;
	}
	case console_op::read:
	{
		T input;
		std::cin >> input;
		value_setdata<T>(ML::Stk, ctx, input);
		return true;
	}
	case console_op::write:
	{
		std::cout << value_getdata_restack<T>(ML::Stk, ctx);
		return true;
	}
	}
}

bool runtimeconsolecallhive<parray<float32_t>>::operator()(uint64_t subcall, context &ctx) const { return console_parray_operator<float32_t>(subcall, ctx); }
bool runtimeconsolecallhive<parray<float64_t>>::operator()(uint64_t subcall, context &ctx) const { return console_parray_operator<float64_t>(subcall, ctx); }
bool runtimeconsolecallhive<parray<int8_t>>::operator()(uint64_t subcall, context &ctx) const { return console_parray_operator<int8_t>(subcall, ctx); }
bool runtimeconsolecallhive<parray<int16_t>>::operator()(uint64_t subcall, context &ctx) const { return console_parray_operator<int16_t>(subcall, ctx); }
bool runtimeconsolecallhive<parray<int32_t>>::operator()(uint64_t subcall, context &ctx) const { return console_parray_operator<int32_t>(subcall, ctx); }
bool runtimeconsolecallhive<parray<int64_t>>::operator()(uint64_t subcall, context &ctx) const { return console_parray_operator<int64_t>(subcall, ctx); }
bool runtimeconsolecallhive<parray<uint8_t>>::operator()(uint64_t subcall, context &ctx) const { return console_parray_operator<uint8_t>(subcall, ctx); }
bool runtimeconsolecallhive<parray<uint16_t>>::operator()(uint64_t subcall, context &ctx) const { return console_parray_operator<uint16_t>(subcall, ctx); }
bool runtimeconsolecallhive<parray<uint32_t>>::operator()(uint64_t subcall, context &ctx) const { return console_parray_operator<uint32_t>(subcall, ctx); }
bool runtimeconsolecallhive<parray<uint64_t>>::operator()(uint64_t subcall, context &ctx) const { return console_parray_operator<uint64_t>(subcall, ctx); }

bool runtimeconsolecallhive<float32_t*>::operator()(uint64_t subcall, context &ctx) const { return console_ptr_operator<float32_t>(subcall, ctx); }
bool runtimeconsolecallhive<float64_t*>::operator()(uint64_t subcall, context &ctx) const { return console_ptr_operator<float64_t>(subcall, ctx); }
bool runtimeconsolecallhive<int8_t*>::operator()(uint64_t subcall, context &ctx) const { return console_ptr_operator<int8_t>(subcall, ctx); }
bool runtimeconsolecallhive<int16_t*>::operator()(uint64_t subcall, context &ctx) const { return console_ptr_operator<int16_t>(subcall, ctx); }
bool runtimeconsolecallhive<int32_t*>::operator()(uint64_t subcall, context &ctx) const { return console_ptr_operator<int32_t>(subcall, ctx); }
bool runtimeconsolecallhive<int64_t*>::operator()(uint64_t subcall, context &ctx) const { return console_ptr_operator<int64_t>(subcall, ctx); }
bool runtimeconsolecallhive<uint8_t*>::operator()(uint64_t subcall, context &ctx) const { return console_ptr_operator<uint8_t>(subcall, ctx); }
bool runtimeconsolecallhive<uint16_t*>::operator()(uint64_t subcall, context &ctx) const { return console_ptr_operator<uint16_t>(subcall, ctx); }
bool runtimeconsolecallhive<uint32_t*>::operator()(uint64_t subcall, context &ctx) const { return console_ptr_operator<uint32_t>(subcall, ctx); }
bool runtimeconsolecallhive<uint64_t*>::operator()(uint64_t subcall, context &ctx) const { return console_ptr_operator<uint64_t>(subcall, ctx); }

bool runtimeconsolecallhive<float32_t>::operator()(uint64_t subcall, context &ctx) const { return console_value_operator<float32_t>(subcall, ctx); }
bool runtimeconsolecallhive<float64_t>::operator()(uint64_t subcall, context &ctx) const { return console_value_operator<float64_t>(subcall, ctx); }
bool runtimeconsolecallhive<int8_t>::operator()(uint64_t subcall, context &ctx) const { return console_value_operator<int8_t>(subcall, ctx); }
bool runtimeconsolecallhive<int16_t>::operator()(uint64_t subcall, context &ctx) const { return console_value_operator<int16_t>(subcall, ctx); }
bool runtimeconsolecallhive<int32_t>::operator()(uint64_t subcall, context &ctx) const { return console_value_operator<int32_t>(subcall, ctx); }
bool runtimeconsolecallhive<int64_t>::operator()(uint64_t subcall, context &ctx) const { return console_value_operator<int64_t>(subcall, ctx); }
bool runtimeconsolecallhive<uint8_t>::operator()(uint64_t subcall, context &ctx) const { return console_value_operator<uint8_t>(subcall, ctx); }
bool runtimeconsolecallhive<uint16_t>::operator()(uint64_t subcall, context &ctx) const { return console_value_operator<uint16_t>(subcall, ctx); }
bool runtimeconsolecallhive<uint32_t>::operator()(uint64_t subcall, context &ctx) const { return console_value_operator<uint32_t>(subcall, ctx); }
bool runtimeconsolecallhive<uint64_t>::operator()(uint64_t subcall, context &ctx) const { return console_value_operator<uint64_t>(subcall, ctx); }
