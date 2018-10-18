#include <iomanip>
#include <iostream>
#include <encstr/string.hpp>
#include <encstr/cfb.hpp>
#include <encstr/ciphers/xtea_cipher.hpp>

int main()
{
    using encoder = encstr::cfb_t<encstr::ciphers::xtea_cipher_t>;
    std::cout << ENCRYPT_STRING_AUTO_A(encoder, "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Aenean volutpat et erat sed volutpat. Duis fringilla.");

    std::cin.get();

    return 0;
}
