#pragma once
#include <encstr/always_inline.hpp>
#include <encstr/unroll.hpp>

namespace encstr
{
    template<typename CipherT>
    struct cfb_t
    {
        using cipher_type = CipherT;
        using block_type = typename cipher_type::block_type;
        using key_type = typename cipher_type::key_type;
        using iv_type = block_type;

        constexpr static auto key_size = typename cipher_type::key_size;
        constexpr static auto block_size = typename cipher_type::block_size;

        template<size_t Size>
        ENCSTR_ALWAYS_INLINE static constexpr std::array<uint8_t, Size> encrypt(std::array<uint8_t, Size> input, key_type key, iv_type iv) noexcept
        {
            static_assert(Size % block_size == 0, "Data size is not properly aligned!");
            std::array<uint8_t, Size> result{ 0 };

            for(size_t i = 0; i < Size; i += block_size)
            {
                iv = cipher_type::encode(iv, key);

                for(size_t j = 0; j < block_size; ++j)
                    iv[j] ^= input[i + j];

                static_memcpy(result.data() + i, iv.data(), block_size);
            }

            return result;
        }

        template<size_t Size>
        ENCSTR_ALWAYS_INLINE static constexpr std::array<uint8_t, Size> decrypt(std::array<uint8_t, Size> input, key_type key, iv_type iv) noexcept
        {
            static_assert(Size % block_size == 0, "Data size is not properly aligned!");
            std::array<uint8_t, Size> result{ 0 };
            
            for(size_t i = 0; i < Size; i += block_size)
            {
                iv = cipher_type::encode(iv, key);

                for(size_t j = 0; j < block_size; ++j)
                    result[i + j] = iv[j] ^ input[i + j];

                static_memcpy(iv.data(), input.data() + i, block_size);
            }

            return result;
        }
    };
}
