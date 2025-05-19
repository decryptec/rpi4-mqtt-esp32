# Install script for directory: /nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/var/empty/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

# Set path to fallback-tool for dependency-resolution.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/nix/store/y90z6gpcvp1c1w6mmhqpib7zan539kic-xtensa-esp-elf-esp-idf-v5.4.1/bin/xtensa-esp32-elf-objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mbedtls" TYPE FILE PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ FILES
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/mbedtls/aes.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/mbedtls/aria.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/mbedtls/asn1.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/mbedtls/asn1write.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/mbedtls/base64.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/mbedtls/bignum.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/mbedtls/block_cipher.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/mbedtls/build_info.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/mbedtls/camellia.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/mbedtls/ccm.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/mbedtls/chacha20.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/mbedtls/chachapoly.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/mbedtls/check_config.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/mbedtls/cipher.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/mbedtls/cmac.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/mbedtls/compat-2.x.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/mbedtls/config_adjust_legacy_crypto.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/mbedtls/config_adjust_legacy_from_psa.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/mbedtls/config_adjust_psa_from_legacy.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/mbedtls/config_adjust_psa_superset_legacy.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/mbedtls/config_adjust_ssl.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/mbedtls/config_adjust_x509.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/mbedtls/config_psa.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/mbedtls/constant_time.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/mbedtls/ctr_drbg.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/mbedtls/debug.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/mbedtls/des.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/mbedtls/dhm.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/mbedtls/ecdh.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/mbedtls/ecdsa.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/mbedtls/ecjpake.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/mbedtls/ecp.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/mbedtls/entropy.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/mbedtls/error.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/mbedtls/gcm.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/mbedtls/hkdf.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/mbedtls/hmac_drbg.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/mbedtls/lms.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/mbedtls/mbedtls_config.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/mbedtls/md.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/mbedtls/md5.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/mbedtls/memory_buffer_alloc.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/mbedtls/net_sockets.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/mbedtls/nist_kw.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/mbedtls/oid.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/mbedtls/pem.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/mbedtls/pk.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/mbedtls/pkcs12.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/mbedtls/pkcs5.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/mbedtls/pkcs7.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/mbedtls/platform.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/mbedtls/platform_time.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/mbedtls/platform_util.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/mbedtls/poly1305.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/mbedtls/private_access.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/mbedtls/psa_util.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/mbedtls/ripemd160.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/mbedtls/rsa.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/mbedtls/sha1.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/mbedtls/sha256.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/mbedtls/sha3.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/mbedtls/sha512.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/mbedtls/ssl.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/mbedtls/ssl_cache.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/mbedtls/ssl_ciphersuites.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/mbedtls/ssl_cookie.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/mbedtls/ssl_ticket.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/mbedtls/threading.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/mbedtls/timing.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/mbedtls/version.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/mbedtls/x509.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/mbedtls/x509_crl.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/mbedtls/x509_crt.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/mbedtls/x509_csr.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/psa" TYPE FILE PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ FILES
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/psa/build_info.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/psa/crypto.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/psa/crypto_adjust_auto_enabled.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/psa/crypto_adjust_config_dependencies.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/psa/crypto_adjust_config_key_pair_types.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/psa/crypto_adjust_config_synonyms.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/psa/crypto_builtin_composites.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/psa/crypto_builtin_key_derivation.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/psa/crypto_builtin_primitives.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/psa/crypto_compat.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/psa/crypto_config.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/psa/crypto_driver_common.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/psa/crypto_driver_contexts_composites.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/psa/crypto_driver_contexts_key_derivation.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/psa/crypto_driver_contexts_primitives.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/psa/crypto_extra.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/psa/crypto_legacy.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/psa/crypto_platform.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/psa/crypto_se_driver.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/psa/crypto_sizes.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/psa/crypto_struct.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/psa/crypto_types.h"
    "/nix/store/cx2807958xk7lmkxjg6r96byxcvkxb1i-esp-idf-v5.4.1/components/mbedtls/mbedtls/include/psa/crypto_values.h"
    )
endif()

