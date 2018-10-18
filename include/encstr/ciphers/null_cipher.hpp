#pragma once
#include <cstdint>
#include <array>
#include <encstr/always_inline.hpp>

namespace encstr::ciphers
{
    struct null_cipher_t
    {
        constexpr static size_t block_size = 1;
        constexpr static size_t key_size = 0;

        using block_type = std::array<uint8_t, block_size>;
        using key_type = std::array<uint8_t, key_size>;

        ENCSTR_ALWAYS_INLINE constexpr static block_type encode(block_type input, key_type) noexcept { return input; }
        ENCSTR_ALWAYS_INLINE constexpr static block_type decode(block_type input, key_type) noexcept { return input; }
    };
}
