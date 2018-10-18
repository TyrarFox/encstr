#include <iomanip>
#include <iostream>
#include <encstr/string.hpp>
#include <encstr/cbc.hpp>
#include <encstr/ciphers/xor_cipher.hpp>

int main()
{
    using encoder = encstr::cbc_t<encstr::ciphers::xor_cipher_t>;
    std::cout << ENCRYPT_STRING_AUTO_A(encoder, "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Aenean volutpat et erat sed volutpat. Duis fringilla.");

    std::cin.get();

    return 0;
}
