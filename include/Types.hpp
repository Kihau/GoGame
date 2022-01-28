#ifndef TYPES_H
#define TYPES_H

#include "stdint.h"

using i8   = __int8_t;
using i16  = __int16_t;
using i32  = __int32_t;
using i64  = __int64_t;
using i128 = __int128_t;

using u8   = __uint8_t;
using u16  = __uint16_t;
using u32  = __uint32_t; 
using u64  = __uint64_t;
using u128 = __uint128_t;

using f32  = _Float32;
using f64  = _Float64;
using f128 = _Float128;
// joke alias - remove it later
using f80  = __float80;

// #define I8MIN   -127
// #define I16MIN  -32767
// #define I32MIN  -2147483647
// #define I64MIN  -9223372036854776000
// #define I128MIN "very small"

#define I8MIN   -0x7F
#define I16MIN  -0x7FFF
#define I32MIN  -0x7FFFFFFF
#define I64MIN  -0x7FFFFFFFFFFFFFFF
#define I128MIN -0x7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF


// #define I8MAX   127
// #define I16MAX  32767
// #define I32MAX  2147483647
// #define I64MAX  9223372036854776000
// #define I128MAX "very big"

#define I8MAX   0x7F
#define I16MAX  0x7FFF
#define I32MAX  0x7FFFFFFF
#define I64MAX  0x7FFFFFFFFFFFFFFF
#define I128MAX 0x7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF


#define U8MIN   0x0
#define U16MIN  0x0
#define U32MIN  0x0
#define U64MIN  0x0
#define U128MIN 0x0


// #define U8MAX   255
// #define U16MAX  65535
// #define U32MAX  4294967295
// #define U64MAX  18446744073709552000

#define U8MAX   0xFF
#define U16MAX  0xFFFF
#define U32MAX  0xFFFFFFFF
#define U64MAX  0xFFFFFFFFFFFFFFFF
#define U128MAX 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF



// using i8  = int8_t;
// using i16 = int16_t;
// using i32 = int32_t;
// using i64 = int64_t;

// using u8  = uint8_t;
// using u16 = uint16_t;
// using u32 = uint32_t;
// using u64 = uint64_t;

// using f32  = _Float32;
// using f64  = _Float64;
// using f128 = _Float128;
// using f80  = __float80;

#endif