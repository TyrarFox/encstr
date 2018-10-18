#pragma once

#if defined(__clang__) || defined(__GNUC__)
    #define ENCSTR_ALWAYS_INLINE __attribute__((always_inline))
#elif defined(_MSC_VER)
    #define ENCSTR_ALWAYS_INLINE __forceinline
#else
    #define ENCSTR_ALWAYS_INLINE inline
#endif
