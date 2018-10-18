#pragma once
#include <cstdint>

namespace encstr
{
    constexpr uint32_t fnv1a(std::string_view str)
    {
        uint32_t result = 0x811c9dc5ul;

		for (auto chr : str)
		{
			result = static_cast<uint32_t>(static_cast<uint64_t>(result) ^ static_cast<uint64_t>(chr));
			result = static_cast<uint32_t>(static_cast<uint64_t>(result) * static_cast<uint64_t>(16777619ul));
		}

		return result;
    }
}
