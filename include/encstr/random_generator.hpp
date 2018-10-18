#pragma once
#include <cstdint>
#include <encstr/fnv1a.hpp>

namespace encstr
{
    constexpr auto random_seed = fnv1a(__TIME__);

	template<int32_t N>
	class random_generator_t
	{
	private:
		static constexpr uint32_t a = 16807;
		static constexpr uint32_t m = 2147483647;
		static constexpr uint32_t s = random_generator_t<N - 1>::value;
		static constexpr uint32_t lo = a * (s & 0xFFFF);
		static constexpr uint32_t hi = a * (s >> 16);
		static constexpr uint32_t lo2 = lo + ((hi & 0x7FFF) << 16);
		static constexpr uint32_t hi2 = hi >> 15;
		static constexpr uint32_t lo3 = lo2 + hi;

	public:
		static constexpr uint32_t max = m;
		static constexpr uint32_t value = lo3 > m ? lo3 - m : lo3;
	};

	template<>
	class random_generator_t<0>
	{
	public:
		static constexpr uint32_t max = 2147483647;
		static constexpr uint32_t value = random_seed;
	};

    template<int32_t N, size_t Size>
    ENCSTR_ALWAYS_INLINE constexpr std::array<uint8_t, Size> generate_random_block() noexcept
    {
		static_assert(Size > 0, "Block size must be at least 1 byte!");
        std::array<uint8_t, Size> result{ 0 };

        for(size_t i = Size; i >= sizeof(uint32_t); i -= sizeof(uint32_t))
            result = write_uint<uint32_t>(result, (random_generator_t<N>::value << (i & 31)) ^ static_cast<uint32_t>(i ^ N), Size - i);
        
		if constexpr (Size & 3)
		{
			std::array<uint8_t, sizeof(uint32_t)> pad{ 0 };
			pad = write_uint<uint32_t>(pad, random_generator_t<N>::value, 0);

			switch(Size & 3)
			{
			case 3: result[Size - 3] = pad[0];
			case 2: result[Size - 2] = pad[1];
			case 1: result[Size - 1] = pad[2];
			default: break;
			}
		}

        return result;
    }
}
