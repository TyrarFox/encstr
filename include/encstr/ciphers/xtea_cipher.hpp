#pragma once
#include <cstdint>
#include <array>
#include <encstr/always_inline.hpp>
#include <encstr/unroll.hpp>
#include <encstr/utils.hpp>

namespace encstr::ciphers
{
    constexpr size_t xtea_default_rounds = 32;
    constexpr uint32_t xtea_default_delta = 0x9e3779b9u;

    template<size_t Rounds = xtea_default_rounds, uint32_t Delta = xtea_default_delta>
    struct basic_xtea_cipher_t
    {
        constexpr static size_t block_size = 8;
        constexpr static size_t key_size = 16;

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
                auto sum = static_cast<uint32_t>(static_cast<uint64_t>(Delta) * static_cast<uint64_t>(i));

                auto v0 = read_uint<uint32_t>(data, 0);
                auto v1 = read_uint<uint32_t>(data, 4);

                v0 = static_cast<uint32_t>(static_cast<uint64_t>(v0) + ((static_cast<uint64_t>((v1 << 4) ^ (v1 >> 5)) + static_cast<uint64_t>(v1)) ^ (static_cast<uint64_t>(sum) + static_cast<uint64_t>(read_uint<uint32_t>(key, (sum & 3) * 4)))));
                sum = static_cast<uint32_t>(static_cast<uint64_t>(sum) + static_cast<uint64_t>(Delta));
                v1 = static_cast<uint32_t>(static_cast<uint64_t>(v1) + ((static_cast<uint64_t>((v0 << 4) ^ (v0 >> 5)) + static_cast<uint64_t>(v0)) ^ (static_cast<uint64_t>(sum) + static_cast<uint64_t>(read_uint<uint32_t>(key, ((sum >> 11) & 3) * 4)))));

                data = write_uint<uint32_t>(write_uint<uint32_t>(data, v0, 0), v1, 4);
            }
        };
        struct decoder_t
        {
            block_type data;

            ENCSTR_ALWAYS_INLINE constexpr explicit decoder_t(block_type _data) noexcept :
                data{ _data }
            {
            }

            ENCSTR_ALWAYS_INLINE constexpr void operator()(size_t i, key_type key) noexcept
            {
                auto sum = static_cast<uint32_t>(static_cast<uint64_t>(Delta) * static_cast<uint64_t>(Rounds - i));

                auto v0 = read_uint<uint32_t>(data, 0);
                auto v1 = read_uint<uint32_t>(data, 4);

                v1 = static_cast<uint32_t>(static_cast<uint64_t>(v1) - ((static_cast<uint64_t>((v0 << 4) ^ (v0 >> 5)) + static_cast<uint64_t>(v0)) ^ (static_cast<uint64_t>(sum) + static_cast<uint64_t>(read_uint<uint32_t>(key, ((sum >> 11) & 3) * 4)))));
                sum = static_cast<uint32_t>(static_cast<uint64_t>(sum) - static_cast<uint64_t>(Delta));
                v0 = static_cast<uint32_t>(static_cast<uint64_t>(v0) - ((static_cast<uint64_t>((v1 << 4) ^ (v1 >> 5)) + static_cast<uint64_t>(v1)) ^ (static_cast<uint64_t>(sum) + static_cast<uint64_t>(read_uint<uint32_t>(key, (sum & 3) * 4)))));

                data = write_uint<uint32_t>(write_uint<uint32_t>(data, v0, 0), v1, 4);
            }
        };

        ENCSTR_ALWAYS_INLINE constexpr static block_type encode(block_type input, key_type key) noexcept
        {
            encoder_t encoder{ input };

#if defined(ENCSTR_LOOP_UNROLLING)
            unroll_t<Rounds>{}(encoder, key);
#else
		    for (auto i = 0u; i < Rounds; ++i)
                encoder(i, key);
#endif

            return encoder.data;
        }
        ENCSTR_ALWAYS_INLINE constexpr static block_type decode(block_type input, key_type key) noexcept
        {
            decoder_t decoder{ input };

#if defined(ENCSTR_LOOP_UNROLLING)
            unroll_t<Rounds>{}(decoder, key);
#else
		    for (auto i = 0u; i < Rounds; ++i)
                decoder(i, key);
#endif

            return decoder.data;
        }
    };

    using xtea_cipher_t = basic_xtea_cipher_t<xtea_default_rounds, xtea_default_delta>;
}
