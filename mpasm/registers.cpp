/*
* Copyright 2018 Mouse-Produced Games.
* Distributed under the terms of the GNU Lesser General Public Liceense (Version 3, 29 June 2007)
*/

#include "stdafx.h"
#include "registers.h"

#include "parray.h"

template<> float32_t reg<float32_t>[255];
template<> float64_t reg<float64_t>[255];

template<> int8_t reg<int8_t>[255];
template<> int16_t reg<int16_t>[255];
template<> int32_t reg<int32_t>[255];
template<> int64_t reg<int64_t>[255];

template<> uint8_t reg<uint8_t>[255];
template<> uint16_t reg<uint16_t>[255];
template<> uint32_t reg<uint32_t>[255];
template<> uint64_t reg<uint64_t>[255];

template<> parray<float32_t> reg<parray<float32_t>>[255];
template<> parray<float64_t> reg<parray<float64_t>>[255];

template<> parray<int8_t> reg<parray<int8_t>>[255];
template<> parray<int16_t> reg<parray<int16_t>>[255];
template<> parray<int32_t> reg<parray<int32_t>>[255];
template<> parray<int64_t> reg<parray<int64_t>>[255];

template<> parray<uint8_t> reg<parray<uint8_t>>[255];
template<> parray<uint16_t> reg<parray<uint16_t>>[255];
template<> parray<uint32_t> reg<parray<uint32_t>>[255];
template<> parray<uint64_t> reg<parray<uint64_t>>[255];