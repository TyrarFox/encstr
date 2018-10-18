#pragma once
#include <cstdint>
#include <cstddef>
#include <encstr/always_inline.hpp>

namespace encstr
{
    template<size_t Alignment, size_t Size>
    struct align_to
    {
        static constexpr auto value = (Size % Alignment) == 0 ? Size : (Size - (Size % Alignment) + Alignment);
    };

    ENCSTR_ALWAYS_INLINE constexpr void static_memcpy(uint8_t* dst, const uint8_t* src, size_t size)
    {
        for(size_t i = 0; i < size; ++i)
            dst[i] = src[i];
    }

    template<typename T, size_t Size>
    ENCSTR_ALWAYS_INLINE constexpr T read_uint(std::array<uint8_t, Size> buffer, size_t offset = 0) noexcept
    {
        static_assert(Size >= sizeof(T), "Buffer is too small to hold an uint32_t!");

        T result = 0;

        for(size_t i = 0; i < sizeof(T); ++i)
            result |= static_cast<T>(buffer[offset + i]) << (i * 8);
        
        return result;
    }
    template<typename T, size_t Size>
    ENCSTR_ALWAYS_INLINE constexpr std::array<uint8_t, Size> write_uint(std::array<uint8_t, Size> buffer, uint32_t val, size_t offset = 0) noexcept
    {
        static_assert(Size >= 4, "Buffer is too small to hold an uint32_t!");

        for(size_t i = 0; i < sizeof(T); ++i)
            buffer[offset + i] = static_cast<uint8_t>((val >> (i * 8)) & 0xff);

        return buffer;
    }
}
