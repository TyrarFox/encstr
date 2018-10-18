cmake_minimum_required(VERSION 3.10)
project(encstr)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED 17)

option(ENCSTR_BUILD_EXAMPLES "Build encstr examples." ON)

set(ENCSTR_INCLUDES
    ${CMAKE_CURRENT_SOURCE_DIR}/include/encstr/string.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/encstr/always_inline.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/encstr/utils.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/encstr/unroll.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/encstr/fnv1a.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/encstr/random_generator.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/encstr/ecb.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/encstr/cbc.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/encstr/cfb.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/encstr/ciphers/null_cipher.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/encstr/ciphers/xor_cipher.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/encstr/ciphers/xtea_cipher.hpp
)

add_library(encstr INTERFACE)
target_include_directories(encstr INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/encstr
    DESTINATION include
)

if(ENCSTR_BUILD_EXAMPLES)
    add_executable(encstr-example-ecb-xor ${CMAKE_CURRENT_SOURCE_DIR}/examples/ecb-xor.cpp ${ENCSTR_INCLUDES})
    add_executable(encstr-example-cbc-xor ${CMAKE_CURRENT_SOURCE_DIR}/examples/cbc-xor.cpp ${ENCSTR_INCLUDES})
    add_executable(encstr-example-cfb-xor ${CMAKE_CURRENT_SOURCE_DIR}/examples/cfb-xor.cpp ${ENCSTR_INCLUDES})
    add_executable(encstr-example-ecb-xtea ${CMAKE_CURRENT_SOURCE_DIR}/examples/ecb-xtea.cpp ${ENCSTR_INCLUDES})
    add_executable(encstr-example-cbc-xtea ${CMAKE_CURRENT_SOURCE_DIR}/examples/cbc-xtea.cpp ${ENCSTR_INCLUDES})
    add_executable(encstr-example-cfb-xtea ${CMAKE_CURRENT_SOURCE_DIR}/examples/cfb-xtea.cpp ${ENCSTR_INCLUDES})
    add_executable(encstr-example-ecb-xor-unroll ${CMAKE_CURRENT_SOURCE_DIR}/examples/ecb-xor-unroll.cpp ${ENCSTR_INCLUDES})
    add_executable(encstr-example-cbc-xor-unroll ${CMAKE_CURRENT_SOURCE_DIR}/examples/cbc-xor-unroll.cpp ${ENCSTR_INCLUDES})
    add_executable(encstr-example-cfb-xor-unroll ${CMAKE_CURRENT_SOURCE_DIR}/examples/cfb-xor-unroll.cpp ${ENCSTR_INCLUDES})
    add_executable(encstr-example-ecb-xtea-unroll ${CMAKE_CURRENT_SOURCE_DIR}/examples/ecb-xtea-unroll.cpp ${ENCSTR_INCLUDES})
    add_executable(encstr-example-cbc-xtea-unroll ${CMAKE_CURRENT_SOURCE_DIR}/examples/cbc-xtea-unroll.cpp ${ENCSTR_INCLUDES})
    add_executable(encstr-example-cfb-xtea-unroll ${CMAKE_CURRENT_SOURCE_DIR}/examples/cfb-xtea-unroll.cpp ${ENCSTR_INCLUDES})

    target_link_libraries(encstr-example-ecb-xor PUBLIC encstr)
    target_link_libraries(encstr-example-cbc-xor PUBLIC encstr)
    target_link_libraries(encstr-example-cfb-xor PUBLIC encstr)
    target_link_libraries(encstr-example-ecb-xtea PUBLIC encstr)
    target_link_libraries(encstr-example-cbc-xtea PUBLIC encstr)
    target_link_libraries(encstr-example-cfb-xtea PUBLIC encstr)
    target_link_libraries(encstr-example-ecb-xor-unroll PUBLIC encstr)
    target_link_libraries(encstr-example-cbc-xor-unroll PUBLIC encstr)
    target_link_libraries(encstr-example-cfb-xor-unroll PUBLIC encstr)
    target_link_libraries(encstr-example-ecb-xtea-unroll PUBLIC encstr)
    target_link_libraries(encstr-example-cbc-xtea-unroll PUBLIC encstr)
    target_link_libraries(encstr-example-cfb-xtea-unroll PUBLIC encstr)
endif(ENCSTR_BUILD_EXAMPLES)
