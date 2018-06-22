#ifndef MPASM_MPASM_SYSCALLS_SYSCALLID_H
#define MPASM_MPASM_SYSCALLS_SYSCALLID_H

#include "stdafx.h"

enum class syscallid : uint64_t
{
	// Environment = 0,
	Console = 1,
	Memory = 2,
	// Window = 3,
	// Graphics2D = 4,
	// Graphics3D = 5,
	// Audio = 6,
	// InputDevice = 7,
	/*
	UNDEFINED = 8,
	UNDEFINED = 9,
	UNDEFINED = 10,
	UNDEFINED = 11,
	UNDEFINED = 12,
	UNDEFINED = 13,
	UNDEFINED = 14,
	UNDEFINED = 15,
	UNDEFINED = 16,
	UNDEFINED = 17,
	UNDEFINED = 18,
	UNDEFINED = 19,
	UNDEFINED = 20,
	UNDEFINED = 21,
	UNDEFINED = 22,
	UNDEFINED = 23,
	UNDEFINED = 24,
	UNDEFINED = 25,
	UNDEFINED = 26,
	UNDEFINED = 27,
	UNDEFINED = 28,
	UNDEFINED = 29,
	UNDEFINED = 30,
	UNDEFINED = 31,
	UNDEFINED = 32,
	UNDEFINED = 33,
	UNDEFINED = 34,
	UNDEFINED = 35,
	UNDEFINED = 36,
	UNDEFINED = 37,
	UNDEFINED = 38,
	UNDEFINED = 39,
	UNDEFINED = 40,
	UNDEFINED = 41,
	UNDEFINED = 42,
	UNDEFINED = 43,
	UNDEFINED = 44,
	UNDEFINED = 45,
	UNDEFINED = 46,
	UNDEFINED = 47,
	UNDEFINED = 48,
	UNDEFINED = 49,
	UNDEFINED = 50,
	UNDEFINED = 51,
	UNDEFINED = 52,
	UNDEFINED = 53,
	UNDEFINED = 54,
	UNDEFINED = 55,
	UNDEFINED = 56,
	UNDEFINED = 57,
	UNDEFINED = 58,
	UNDEFINED = 59,
	UNDEFINED = 60,
	UNDEFINED = 61,
	UNDEFINED = 62,
	UNDEFINED = 63,
	UNDEFINED = 64,
	UNDEFINED = 65,
	UNDEFINED = 66,
	UNDEFINED = 67,
	UNDEFINED = 68,
	UNDEFINED = 69,
	UNDEFINED = 70,
	UNDEFINED = 71,
	UNDEFINED = 72,
	UNDEFINED = 73,
	UNDEFINED = 74,
	UNDEFINED = 75,
	UNDEFINED = 76,
	UNDEFINED = 77,
	UNDEFINED = 78,
	UNDEFINED = 79,
	UNDEFINED = 80,
	UNDEFINED = 81,
	UNDEFINED = 82,
	UNDEFINED = 83,
	UNDEFINED = 84,
	UNDEFINED = 85,
	UNDEFINED = 86,
	UNDEFINED = 87,
	UNDEFINED = 88,
	UNDEFINED = 89,
	UNDEFINED = 90,
	UNDEFINED = 91,
	UNDEFINED = 92,
	UNDEFINED = 93,
	UNDEFINED = 94,
	UNDEFINED = 95,
	UNDEFINED = 96,
	UNDEFINED = 97,
	UNDEFINED = 98,
	UNDEFINED = 99,
	UNDEFINED = 100,
	UNDEFINED = 101,
	UNDEFINED = 102,
	UNDEFINED = 103,
	UNDEFINED = 104,
	UNDEFINED = 105,
	UNDEFINED = 106,
	UNDEFINED = 107,
	UNDEFINED = 108,
	UNDEFINED = 109,
	UNDEFINED = 110,
	UNDEFINED = 111,
	UNDEFINED = 112,
	UNDEFINED = 113,
	UNDEFINED = 114,
	UNDEFINED = 115,
	UNDEFINED = 116,
	UNDEFINED = 117,
	UNDEFINED = 118,
	UNDEFINED = 119,
	UNDEFINED = 120,
	UNDEFINED = 121,
	UNDEFINED = 122,
	UNDEFINED = 123,
	UNDEFINED = 124,
	UNDEFINED = 125,
	UNDEFINED = 126,
	UNDEFINED = 127,
	UNDEFINED = 128,
	UNDEFINED = 129,
	UNDEFINED = 130,
	UNDEFINED = 131,
	UNDEFINED = 132,
	UNDEFINED = 133,
	UNDEFINED = 134,
	UNDEFINED = 135,
	UNDEFINED = 136,
	UNDEFINED = 137,
	UNDEFINED = 138,
	UNDEFINED = 139,
	UNDEFINED = 140,
	UNDEFINED = 141,
	UNDEFINED = 142,
	UNDEFINED = 143,
	UNDEFINED = 144,
	UNDEFINED = 145,
	UNDEFINED = 146,
	UNDEFINED = 147,
	UNDEFINED = 148,
	UNDEFINED = 149,
	UNDEFINED = 150,
	UNDEFINED = 151,
	UNDEFINED = 152,
	UNDEFINED = 153,
	UNDEFINED = 154,
	UNDEFINED = 155,
	UNDEFINED = 156,
	UNDEFINED = 157,
	UNDEFINED = 158,
	UNDEFINED = 159,
	UNDEFINED = 160,
	UNDEFINED = 161,
	UNDEFINED = 162,
	UNDEFINED = 163,
	UNDEFINED = 164,
	UNDEFINED = 165,
	UNDEFINED = 166,
	UNDEFINED = 167,
	UNDEFINED = 168,
	UNDEFINED = 169,
	UNDEFINED = 170,
	UNDEFINED = 171,
	UNDEFINED = 172,
	UNDEFINED = 173,
	UNDEFINED = 174,
	UNDEFINED = 175,
	UNDEFINED = 176,
	UNDEFINED = 177,
	UNDEFINED = 178,
	UNDEFINED = 179,
	UNDEFINED = 180,
	UNDEFINED = 181,
	UNDEFINED = 182,
	UNDEFINED = 183,
	UNDEFINED = 184,
	UNDEFINED = 185,
	UNDEFINED = 186,
	UNDEFINED = 187,
	UNDEFINED = 188,
	UNDEFINED = 189,
	UNDEFINED = 190,
	UNDEFINED = 191,
	UNDEFINED = 192,
	UNDEFINED = 193,
	UNDEFINED = 194,
	UNDEFINED = 195,
	UNDEFINED = 196,
	UNDEFINED = 197,
	UNDEFINED = 198,
	UNDEFINED = 199,
	UNDEFINED = 200,
	UNDEFINED = 201,
	UNDEFINED = 202,
	UNDEFINED = 203,
	UNDEFINED = 204,
	UNDEFINED = 205,
	UNDEFINED = 206,
	UNDEFINED = 207,
	UNDEFINED = 208,
	UNDEFINED = 209,
	UNDEFINED = 210,
	UNDEFINED = 211,
	UNDEFINED = 212,
	UNDEFINED = 213,
	UNDEFINED = 214,
	UNDEFINED = 215,
	UNDEFINED = 216,
	UNDEFINED = 217,
	UNDEFINED = 218,
	UNDEFINED = 219,
	UNDEFINED = 220,
	UNDEFINED = 221,
	UNDEFINED = 222,
	UNDEFINED = 223,
	UNDEFINED = 224,
	UNDEFINED = 225,
	UNDEFINED = 226,
	UNDEFINED = 227,
	UNDEFINED = 228,
	UNDEFINED = 229,
	UNDEFINED = 230,
	UNDEFINED = 231,
	UNDEFINED = 232,
	UNDEFINED = 233,
	UNDEFINED = 234,
	UNDEFINED = 235,
	UNDEFINED = 236,
	UNDEFINED = 237,
	UNDEFINED = 238,
	UNDEFINED = 239,
	UNDEFINED = 240,
	UNDEFINED = 241,
	UNDEFINED = 242,
	UNDEFINED = 243,
	UNDEFINED = 244,
	UNDEFINED = 245,
	UNDEFINED = 246,
	UNDEFINED = 247,
	UNDEFINED = 248,
	UNDEFINED = 249,
	UNDEFINED = 250,
	UNDEFINED = 251,
	UNDEFINED = 252,
	UNDEFINED = 253,
	UNDEFINED = 254,
	UNDEFINED = 255,
	*/
};

#endif // !MPASM_MPASM_SYSCALLS_SYSCALLID_H