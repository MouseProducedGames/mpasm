#include "stdafx.h"
#include "registers.h"

#include "mparray.h"

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

template<> mparray<float32_t> reg<mparray<float32_t>>[255];
template<> mparray<float64_t> reg<mparray<float64_t>>[255];

template<> mparray<int8_t> reg<mparray<int8_t>>[255];
template<> mparray<int16_t> reg<mparray<int16_t>>[255];
template<> mparray<int32_t> reg<mparray<int32_t>>[255];
template<> mparray<int64_t> reg<mparray<int64_t>>[255];

template<> mparray<uint8_t> reg<mparray<uint8_t>>[255];
template<> mparray<uint16_t> reg<mparray<uint16_t>>[255];
template<> mparray<uint32_t> reg<mparray<uint32_t>>[255];
template<> mparray<uint64_t> reg<mparray<uint64_t>>[255];