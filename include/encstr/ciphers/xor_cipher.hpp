#pragma once
#include <cstdint>
#include <array>
#include <encstr/always_inline.hpp>
#include <encstr/unroll.hpp>

namespace encstr::ciphers
{
    constexpr size_t xor_default_block_size = 4;
    constexpr size_t xor_default_key_size_min = 1;
    constexpr size_t xor_default_key_size_max = 16;

    template<size_t BlockSize = xor_default_block_size, size_t KeySize = std::clamp(BlockSize, xor_default_key_size_min, xor_default_key_size_max)>
    struct basic_xor_cipher_t
    {
        constexpr static size_t block_size = BlockSize;
        constexpr static size_t key_size = KeySize;

        using block_type = std::array<uint8_t, block_size>;
        using key_type = std::array<uint8_t, key_size>;

        struct encoder_t
        {
            block_type data;

            ENCSTR_ALWAYS_INLINE constexpr explicit encoder_t(block_type _data) noexcept :
                data{ _data }
            {
            }

            ENCSTR_ALWAYS_INLINE constexpr void operator()(size_t i, key_type key) noexcept
            {
                data[i % block_size] ^= key[i % key_size];
            }
        };
        using decoder_t = encoder_t;

        ENCSTR_ALWAYS_INLINE constexpr static block_type encode(block_type input, key_type key) noexcept
        {
            encoder_t encoder{ input };

#if defined(ENCSTR_LOOP_UNROLLING)
            unroll_t<std::max<size_t>(key_size, block_size)>{}(encoder, key);
#else
            for(size_t i = 0; i < std::max<size_t>(key_size, block_size); ++i)
                encoder(i, key);
#endif

            return encoder.data;
        }
        ENCSTR_ALWAYS_INLINE constexpr static block_type decode(block_type input, key_type key) noexcept { return encode(input, key); }
    };

    using xor_cipher_t = basic_xor_cipher_t<xor_default_block_size, std::clamp<size_t>(xor_default_block_size, xor_default_key_size_min, xor_default_key_size_max)>;
}
