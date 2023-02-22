#pragma once

#include "codec.h"

#include <cmath>

/*
 * Fields
 *  Account : Text(16)
 *  Capacity : Alpha(1)
 *  ClOrdID : Text(20)
 *  MaxFloor : Binary(4)
 *  OrderQty : Binary(4)
 *  OrdType : Alphanum(1)
 *  Price : BinaryPrice(8)
 *  Side : Alphanum(1)
 *  Symbol : Alphanum(8)
 *  TimeInForce : Alphanum(1)
 */

inline unsigned char * encode_text(unsigned char * start, const std::string & str, const size_t field_size)
{
    return encode(start, str, field_size);
}

inline unsigned char * encode_char(unsigned char * start, const char ch)
{
    return encode(start, static_cast<uint8_t>(ch));
}

inline unsigned char * encode_binary4(unsigned char * start, const uint32_t value)
{
    return encode(start, value);
}

inline unsigned char * encode_price(unsigned char * start, const double value)
{
    const double order = 10000;
    const double epsilon = 1e-5;
    // beware: no precision loss check
    return encode(start, static_cast<int64_t>(value * order + std::copysign(epsilon, value)));
}

inline constexpr size_t char_size = 1;
inline constexpr size_t binary4_size = 4;
inline constexpr size_t price_size = 8;
inline constexpr size_t binary8_size = 8;

#define FIELD(name, protocol_type, ctype)                                                \
    inline unsigned char * encode_field_##name(unsigned char * start, const ctype value) \
    {                                                                                    \
        return encode_##protocol_type(start, value);                                     \
    }

#define VAR_FIELD(name, size)                                                                  \
    inline unsigned char * encode_field_##name(unsigned char * start, const std::string & str) \
    {                                                                                          \
        return encode_text(start, str, size);                                                  \
    }

#include "fields.inl"

#define FIELD(name, protocol_type, _) inline constexpr size_t name##_field_size = protocol_type##_size;
#define VAR_FIELD(name, size) inline constexpr size_t name##_field_size = size;

#include "fields.inl"

inline void set_opt_field_bit(unsigned char * bitfield_start, unsigned bitfield_num, unsigned bit)
{
    *(bitfield_start + bitfield_num - 1) |= bit;
}

inline std::string binary_to_base64(uint64_t value)
{
    std::string res;
    int mod;
    while (value) {
        mod = value % 36;
        if (mod < 10) {
            res.push_back(char('0' + mod));
        }
        else {
            res.push_back(char('A' + mod - 10));
        }
        value /= 36;
    }
    std::reverse(res.begin(), res.end());
    return res;
}

inline uint64_t decode_binary4(const std::vector<unsigned char> & message, int offset)
{
    return decode_binary(message, offset, 4);
}

inline std::string decode_binary8(const std::vector<unsigned char> & message, int offset)
{
    return binary_to_base64(decode_binary(message, offset, 8));
}

inline LiquidityIndicator decode_liquidity_indicator_t(const std::vector<unsigned char> & message, int offset)
{
    switch (static_cast<char>(message[offset])) {
    case 'A':
        return LiquidityIndicator::Added;
    case 'R':
        return LiquidityIndicator::Removed;
    }
    return LiquidityIndicator::Unknown;
}

inline RestatementReason decode_reason_t(const std::vector<unsigned char> & message, int offset)
{
    switch (char(message[offset])) {
    case 'R':
        return RestatementReason::Reroute;
    case 'X':
        return RestatementReason::LockedInCross;
    case 'W':
        return RestatementReason::Wash;
    case 'L':
        return RestatementReason::Reload;
    case 'Q':
        return RestatementReason::LiquidityUpdated;
    }
    return RestatementReason::Unknown;
}

inline long double decode_price_t(const std::vector<unsigned char> & message, int offset)
{
    uint64_t res = decode_binary(message, offset, 7) - message[offset + 7] * (static_cast<uint64_t>(1) << 56);
    return res / 1e4;
}

#define LOC_FIELD(name, protocol_type, ctype)                                                \
    inline ctype decode_field_##name(const std::vector<unsigned char> & message, int offset) \
    {                                                                                        \
        return decode_##protocol_type(message, offset);                                      \
    }

#define LOC_VAR_FIELD(name, size)                                                                  \
    inline std::string decode_field_##name(const std::vector<unsigned char> & message, int offset) \
    {                                                                                              \
        return decode_text(message, offset, size);                                                 \
    }

#include "loc_fields.inl"
