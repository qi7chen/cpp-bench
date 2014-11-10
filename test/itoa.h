#pragma once

#include <stdint.h>
#include <stdio.h>
#ifdef _MSC_VER
#include <intrin.h>
#endif

inline unsigned CountDecimalDigit32(uint32_t n) 
{
#if defined(_MSC_VER) || defined(__GNUC__)
    static const uint32_t powers_of_10[] = 
    {
        0,
        10,
        100,
        1000,
        10000,
        100000,
        1000000,
        10000000,
        100000000,
        1000000000
    };

#ifdef _MSC_VER
    unsigned long i = 0;
    _BitScanReverse(&i, n | 1);
    uint32_t t = (i + 1) * 1233 >> 12;
#elif __GNUC__
    uint32_t t = (32 - __builtin_clz(n | 1)) * 1233 >> 12;
#endif
    return t - (n < powers_of_10[t]) + 1;
#else
    // Simple pure C++ implementation
    if (n < 10) return 1;
    if (n < 100) return 2;
    if (n < 1000) return 3;
    if (n < 10000) return 4;
    if (n < 100000) return 5;
    if (n < 1000000) return 6;
    if (n < 10000000) return 7;
    if (n < 100000000) return 8;
    if (n < 1000000000) return 9;
    return 10;
#endif
}

inline unsigned CountDecimalDigit64(uint64_t n) 
{
#if defined(_MSC_VER) || defined(__GNUC__)
    static const uint64_t powers_of_10[] = 
    {
        0,
        10,
        100,
        1000,
        10000,
        100000,
        1000000,
        10000000,
        100000000,
        1000000000,
        10000000000ULL,
        100000000000ULL,
        1000000000000ULL,
        10000000000000ULL,
        100000000000000ULL,
        1000000000000000ULL,
        10000000000000000ULL,
        100000000000000000ULL,
        1000000000000000000ULL,
        10000000000000000000ULL,
    };

#if _M_IX86
    unsigned long i = 0;
    uint64_t m = n | 1;
    if (_BitScanReverse(&i, m >> 32))
        i += 32;
    else
        _BitScanReverse(&i, m & 0xFFFFFFFF);
    uint32_t t = (i + 1) * 1233 >> 12;
#elif _M_X64
    unsigned long i = 0;
    _BitScanReverse64(&i, n | 1);
    uint32_t t = (i + 1) * 1233 >> 12;
#elif __GNUC__
    uint32_t t = (64 - __builtin_clzll(n | 1)) * 1233 >> 12;
#endif
    return t - (n < powers_of_10[t]) + 1;
#else
    // Simple pure C++ implementation
    if (n < 10) return 1;
    if (n < 100) return 2;
    if (n < 1000) return 3;
    if (n < 10000) return 4;
    if (n < 100000) return 5;
    if (n < 1000000) return 6;
    if (n < 10000000) return 7;
    if (n < 100000000) return 8;
    if (n < 1000000000) return 9;
    if (n < 10000000000) return 10;
    if (n < 100000000000) return 11;
    if (n < 1000000000000) return 12;
    if (n < 10000000000000) return 13;
    if (n < 100000000000000) return 14;
    if (n < 1000000000000000) return 15;
    if (n < 10000000000000000) return 16;
    if (n < 100000000000000000) return 17;
    if (n < 1000000000000000000) return 18;
    if (n < 10000000000000000000) return 19;
    return 20;
#endif
}


const char gDigitsLut[200] = 
{
    '0', '0', '0', '1', '0', '2', '0', '3', '0', '4', '0', '5', '0', '6', '0', '7', '0', '8', '0', '9',
    '1', '0', '1', '1', '1', '2', '1', '3', '1', '4', '1', '5', '1', '6', '1', '7', '1', '8', '1', '9',
    '2', '0', '2', '1', '2', '2', '2', '3', '2', '4', '2', '5', '2', '6', '2', '7', '2', '8', '2', '9',
    '3', '0', '3', '1', '3', '2', '3', '3', '3', '4', '3', '5', '3', '6', '3', '7', '3', '8', '3', '9',
    '4', '0', '4', '1', '4', '2', '4', '3', '4', '4', '4', '5', '4', '6', '4', '7', '4', '8', '4', '9',
    '5', '0', '5', '1', '5', '2', '5', '3', '5', '4', '5', '5', '5', '6', '5', '7', '5', '8', '5', '9',
    '6', '0', '6', '1', '6', '2', '6', '3', '6', '4', '6', '5', '6', '6', '6', '7', '6', '8', '6', '9',
    '7', '0', '7', '1', '7', '2', '7', '3', '7', '4', '7', '5', '7', '6', '7', '7', '7', '8', '7', '9',
    '8', '0', '8', '1', '8', '2', '8', '3', '8', '4', '8', '5', '8', '6', '8', '7', '8', '8', '8', '9',
    '9', '0', '9', '1', '9', '2', '9', '3', '9', '4', '9', '5', '9', '6', '9', '7', '9', '8', '9', '9'
};


inline void u32toa_count(uint32_t value, char* buffer) 
{
    unsigned digit = CountDecimalDigit32(value);
    buffer += digit;
    *buffer = '\0';

    do 
    {
        *--buffer = char(value % 10) + '0';
        value /= 10;
    } while (value > 0);
}


void u32toa_lut(uint32_t value, char* buffer) 
{
    char temp[10];
    char* p = temp;

    while (value >= 100) 
    {
        const unsigned i = (value % 100) << 1;
        value /= 100;
        *p++ = gDigitsLut[i + 1];
        *p++ = gDigitsLut[i];
    }

    if (value < 10)
        *p++ = char(value) + '0';
    else 
    {
        const unsigned i = value << 1;
        *p++ = gDigitsLut[i + 1];
        *p++ = gDigitsLut[i];
    }

    do 
    {
        *buffer++ = *--p;
    } while (p != temp);

    *buffer = '\0';
}

static const char digits[] = "9876543210123456789";
static const char* zero = digits + 9;

// Efficient Integer to String Conversions, by Matthew Wilson.
template<typename T>
inline size_t u32toa_mwilson(char buf[], T value)
{
    T i = value;
    char* p = buf;

    do 
    {
        int lsd = static_cast<int>(i % 10);
        i /= 10;
        *p++ = zero[lsd];
    } while (i != 0);

    if (value < 0) 
    {
        *p++ = '-';
    }
    *p = '\0';
    std::reverse(buf, p);

    return p - buf;
}

inline void u32toa_naive(uint32_t value, char* buffer)
{
    char temp[10];
    char *p = temp;
    do 
    {
        *p++ = char(value % 10) + '0';
        value /= 10;
    } while (value > 0);

    do 
    {
        *buffer++ = *--p;
    } while (p != temp);

    *buffer = '\0';
}

inline int u32toa_sprintf(uint32_t value, char* buffer)
{
    return sprintf(buffer, "%u", value);
}
