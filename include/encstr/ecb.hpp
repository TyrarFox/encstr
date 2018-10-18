#pragma once
#include <encstr/always_inline.hpp>

namespace encstr
{
    template<typename CipherT>
    struct ecb_t
    {
        using cipher_type = CipherT;
        using block_type = typename cipher_type::block_type;
        using key_type = typename cipher_type::key_type;
        using iv_type = block_type;

        constexpr static auto key_size = typename cipher_type::key_size;
        constexpr static auto block_size = typename cipher_type::block_size;

        template<size_t Size>
        ENCSTR_ALWAYS_INLINE static constexpr std::array<uint8_t, Size> encrypt(std::array<uint8_t, Size> input, key_type key, iv_type) noexcept
        {
            static_assert(Size % block_size == 0, "Data size is not properly aligned!");
            std::array<uint8_t, Size> result{ 0 };
            
            for(size_t i = 0; i < Size; i += block_size)
            {
                block_type block{ 0 };
                static_memcpy(block.data(), input.data() + i, block_size);

                block = cipher_type::encode(block, key);

                static_memcpy(result.data() + i, block.data(), block_size);
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
                block_type block{ 0 };
                static_memcpy(block.data(), input.data() + i, block_size);

                block = cipher_type::decode(block, key);

                static_memcpy(result.data() + i, block.data(), block_size);
            }

            return result;
        }
    };
}
