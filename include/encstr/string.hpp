#pragma once
#include <utility>
#include <string_view>
#include <encstr/always_inline.hpp>
#include <encstr/utils.hpp>
#include <encstr/random_generator.hpp>

namespace encstr
{
    template<typename CharT, typename EncryptT, typename IndexT>
	class string_t;

    template<typename CharT, typename EncryptT, size_t... I>
	class string_t<CharT, EncryptT, std::index_sequence<I...>> {
	public:
		using value_type = CharT;
        using encryptor_type = EncryptT;
        using key_type = typename encryptor_type::key_type;
        using iv_type = typename encryptor_type::iv_type;
        static constexpr auto block_size = encryptor_type::block_size;
        static constexpr auto key_size = encryptor_type::key_size;
		using storage_type = std::array<uint8_t, align_to<block_size, (sizeof...(I) + 1) * sizeof(value_type)>::value>;

		ENCSTR_ALWAYS_INLINE constexpr explicit string_t(std::basic_string_view<value_type> str, key_type key, iv_type iv) noexcept :
            key_{ key },
            iv_{ iv },
			data_{ encrypt(str, key, iv) }
		{
		}

		ENCSTR_ALWAYS_INLINE const value_type* decrypt() const noexcept(false)
		{
            if(!decrypted_)
            {
                decrypted_ = true;

                data_ = encryptor_type::decrypt(data_, key_, iv_);
            }

            return reinterpret_cast<const value_type*>(data_.data());
		}

	private:
        key_type key_;
        iv_type iv_;
		mutable storage_type data_;
		mutable bool decrypted_ = false;

		ENCSTR_ALWAYS_INLINE static constexpr storage_type encrypt(std::basic_string_view<value_type> str, key_type key, iv_type iv) noexcept
		{
            storage_type plaintext{ 0 };

            for(auto i = 0; i < str.length() && i * sizeof(value_type) < plaintext.size(); ++i)
            {
                if constexpr (sizeof(value_type) != 1)
                {
                    const auto chr = str[i];

                    for(auto j = 0; j < sizeof(value_type); ++j)
                        plaintext[i * sizeof(value_type) + 1 - j] = static_cast<uint8_t>(chr & (0xff << 8 * (sizeof(value_type) - 1 - j))) >> (8 * (sizeof(value_type) - 1 - j));
                }
                else
                    plaintext[i] = str[i];
            }

            return encryptor_type::encrypt(plaintext, key, iv);
		}
	};
}

#define MAKE_ENCRYPTED_STRING(CharT, EncryptorT, Str, Key, IV) encstr::string_t<CharT, EncryptorT, std::make_index_sequence<(sizeof(Str) - sizeof(CharT)) / sizeof(CharT)>>(Str, Key, IV)
#define MAKE_ENCRYPTED_STRING_AUTO(CharT, EncryptorT, Str) MAKE_ENCRYPTED_STRING(CharT, EncryptorT, Str, encstr::generate_random_block<__COUNTER__, EncryptorT::key_size>(), encstr::generate_random_block<__COUNTER__, EncryptorT::block_size>())

#define ENCRYPT_STRING(CharT, EncryptorT, Str, Key, IV) []() { constexpr encstr::string_t<CharT, EncryptorT, std::make_index_sequence<(sizeof(Str) - sizeof(CharT)) / sizeof(CharT)>> str(Str, Key, IV); return str; }().decrypt()
#define ENCRYPT_STRING_AUTO(CharT, EncryptorT, Str) []() { constexpr encstr::string_t<CharT, EncryptorT, std::make_index_sequence<(sizeof(Str) - sizeof(CharT)) / sizeof(CharT)>> str(Str, encstr::generate_random_block<__COUNTER__, EncryptorT::key_size>(), encstr::generate_random_block<__COUNTER__, EncryptorT::block_size>()); return str; }().decrypt()

#define MAKE_ENCRYPTED_STRING_A(EncryptorT, Str, Key, IV) MAKE_ENCRYPTED_STRING(char, EncryptorT, Str, Key, IV)
#define MAKE_ENCRYPTED_STRING_W(EncryptorT, Str, Key, IV) MAKE_ENCRYPTED_STRING(wchar_t, EncryptorT, Str, Key, IV)

#define MAKE_ENCRYPTED_STRING_AUTO_A(EncryptorT, Str) MAKE_ENCRYPTED_STRING_AUTO(char, EncryptorT, Str)
#define MAKE_ENCRYPTED_STRING_AUTO_W(EncryptorT, Str) MAKE_ENCRYPTED_STRING_AUTO(wchar_t, EncryptorT, Str)

#define ENCRYPT_STRING_A(EncryptorT, Str, Key, IV) ENCRYPT_STRING(char, EncryptorT, Str, Key, IV)
#define ENCRYPT_STRING_W(EncryptorT, Str, Key, IV) ENCRYPT_STRING(wchar_t, EncryptorT, Str, Key, IV)

#define ENCRYPT_STRING_AUTO_A(EncryptorT, Str) ENCRYPT_STRING_AUTO(char, EncryptorT, Str)
#define ENCRYPT_STRING_AUTO_W(EncryptorT, Str) ENCRYPT_STRING_AUTO(wchar_t, EncryptorT, Str)
