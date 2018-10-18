#define ENCSTR_LOOP_UNROLLING
#include <iomanip>
#include <iostream>
#include <encstr/string.hpp>
#include <encstr/ecb.hpp>
#include <encstr/ciphers/xtea_cipher.hpp>

int main()
{
    using encoder = encstr::ecb_t<encstr::ciphers::xtea_cipher_t<encstr::ciphers::xtea_default_rounds, encstr::ciphers::xtea_default_delta>>;
    std::cout << ENCRYPT_STRING_AUTO(char, encoder, "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Aenean volutpat et erat sed volutpat. Duis fringilla.");

    std::cin.get();

    return 0;
}
