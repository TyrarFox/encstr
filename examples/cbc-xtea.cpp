#include <iomanip>
#include <iostream>
#include <encstr/string.hpp>
#include <encstr/cbc.hpp>
#include <encstr/ciphers/xtea_cipher.hpp>

int main()
{
    using encoder = encstr::cbc_t<encstr::ciphers::xtea_cipher_t<encstr::ciphers::xtea_default_rounds, encstr::ciphers::xtea_default_delta>>;
    std::cout << ENCRYPT_STRING_AUTO(char, encoder, "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Aenean volutpat et erat sed volutpat. Duis fringilla.");

    std::cin.get();

    return 0;
}
