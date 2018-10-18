#pragma once
#include <utility>
#include <encstr/always_inline.hpp>

namespace encstr
{
    template<size_t Count, size_t Step = 1>
    struct unroll_t
    {
        template<typename Fn, typename... Args>
        ENCSTR_ALWAYS_INLINE constexpr auto operator()(Fn&& fn, Args&&... args) noexcept -> decltype(std::forward<Fn>(fn)(std::declval<size_t>(), std::forward<Args>(args)...))
        {
            unroll_t<Count - Step>{}(std::forward<Fn>(fn), std::forward<Args>(args)...);
            return std::forward<Fn>(fn)(Count - Step, std::forward<Args>(args)...);
        }
    };
    template<size_t Step>
    struct unroll_t<1, Step>
    {
        template<typename Fn, typename... Args>
        ENCSTR_ALWAYS_INLINE constexpr auto operator()(Fn&& fn, Args&&... args) noexcept -> decltype(std::forward<Fn>(fn)(std::declval<size_t>(), std::forward<Args>(args)...))
        {
            return std::forward<Fn>(fn)(0, std::forward<Args>(args)...);
        }
    };
}
