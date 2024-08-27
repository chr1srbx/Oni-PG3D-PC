#pragma once
#include <cstdint>

#include <random>
#include "random.hpp"

#include <array>
#include <cstdint>

namespace obfuscate
{
    // Compile-time hash function for string literals
    constexpr uint32_t hash(const char* str) {
        return *str ? static_cast<uint32_t>(*str) + 33 * hash(str + 1) : 5381;
    }

    template <uint32_t Size, uint32_t Seed>
    struct ObfuscatedString
    {
        static constexpr uint32_t XOR = hash(__FILE__) ^ Seed;
        std::array<char, Size> Encrypted;

        static __forceinline constexpr char Encrypt(uint32_t Idx, char C) {
            return C ^ (XOR + Idx) % 256;
        }

        template <size_t... Idx>
        __forceinline constexpr ObfuscatedString(const char* Str, std::index_sequence<Idx...>) :
            Encrypted({ Encrypt(Idx, Str[Idx])... }) { }

        __forceinline const char* Decrypt() {
            for (uint32_t x = 0; x < Size; x++)
                Encrypted[x] ^= (XOR + x) % 256;

            return Encrypted.data();
        }
    };
}

#define OBFUSCATE_STR(s) (obfuscate::ObfuscatedString<sizeof(s), obfuscate::hash(__FILE__)>(s, std::make_index_sequence<sizeof(s)>()).Decrypt())