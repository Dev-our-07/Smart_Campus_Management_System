/**
 * @file auth.cpp
 * @brief Implementation of authentication utilities including SHA-256 hashing.
 *
 * This file contains:
 *  - A complete public-domain SHA-256 implementation (FIPS 180-4 compliant)
 *  - The Auth class methods for generating and verifying password hashes
 *
 * No external libraries are required.
 */

#include "../include/auth.h"
#include <iostream>
#include <string>
#include <cstring>
#include <iomanip>
#include <sstream>
#include <cstdint>

/**
 * @typedef uint32
 * @brief 32-bit unsigned integer used internally in SHA-256.
 */
typedef unsigned int uint32;

/**
 * @typedef uint8
 * @brief 8-bit unsigned integer used internally in SHA-256.
 */
typedef unsigned char uint8;

/**
 * @brief SHA-256 round constants (K values).
 */
static const uint32 K[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

#define ROR(x, n) ((x >> n) | (x << (32 - n)))
#define CH(x, y, z) ((x & y) ^ (~x & z))
#define MAJ(x, y, z) ((x & y) ^ (x & z) ^ (y & z))
#define SIGMA0(x) (ROR(x, 2) ^ ROR(x, 13) ^ ROR(x, 22))
#define SIGMA1(x) (ROR(x, 6) ^ ROR(x, 11) ^ ROR(x, 25))
#define sigma0(x) (ROR(x, 7) ^ ROR(x, 18) ^ (x >> 3))
#define sigma1(x) (ROR(x, 17) ^ ROR(x, 19) ^ (x >> 10))

/**
 * @brief Performs the SHA-256 transformation on a 512-bit data block.
 *
 * @param state Current hash state (8 x 32-bit words).
 * @param block 512-bit message block (64 bytes).
 */
static void sha256_transform(uint32 state[8], const uint8 block[64])
{
    uint32 W[64];

    // Message schedule
    for (int i = 0; i < 16; i++)
    {
        W[i] = ((uint32)block[i * 4] << 24) |
               ((uint32)block[i * 4 + 1] << 16) |
               ((uint32)block[i * 4 + 2] << 8) |
               (uint32)block[i * 4 + 3];
    }
    for (int i = 16; i < 64; i++)
    {
        W[i] = sigma1(W[i - 2]) + W[i - 7] + sigma0(W[i - 15]) + W[i - 16];
    }

    // Initialize working variables
    uint32 a = state[0], b = state[1], c = state[2], d = state[3];
    uint32 e = state[4], f = state[5], g = state[6], h = state[7];

    // Main compression loop
    for (int i = 0; i < 64; i++)
    {
        uint32 T1 = h + SIGMA1(e) + CH(e, f, g) + K[i] + W[i];
        uint32 T2 = SIGMA0(a) + MAJ(a, b, c);

        h = g;
        g = f;
        f = e;
        e = d + T1;
        d = c;
        c = b;
        b = a;
        a = T1 + T2;
    }

    // Update state
    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;
    state[4] += e;
    state[5] += f;
    state[6] += g;
    state[7] += h;
}

/**
 * @brief Computes SHA-256 hash for an input string.
 * @param input Plain text input string.
 * @return 64-character hexadecimal SHA-256 hash.
 */
static std::string sha256(const std::string &input)
{
    uint32 state[8] = {
        0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
        0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19};

    uint8 block[64];
    uint64_t len = input.length() * 8;
    uint32 idx = 0;

    // Process input bytes
    for (size_t i = 0; i < input.length(); i++)
    {
        block[idx++] = input[i];
        if (idx == 64)
        {
            sha256_transform(state, block);
            idx = 0;
        }
    }

    // Append padding
    block[idx++] = 0x80;

    if (idx > 56)
    {
        memset(block + idx, 0, 64 - idx);
        sha256_transform(state, block);
        idx = 0;
    }

    memset(block + idx, 0, 56 - idx);

    // Append length
    for (int i = 0; i < 8; i++)
    {
        block[56 + i] = (len >> (56 - i * 8)) & 0xFF;
    }

    sha256_transform(state, block);

    // Convert to hex string
    std::ostringstream oss;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            oss << std::hex << std::setw(2) << std::setfill('0')
                << ((state[i] >> (24 - j * 8)) & 0xFF);
        }
    }
    return oss.str();
}

/**
 * @class Auth
 * @brief Provides authentication utilities such as password hashing and verification.
 */

Auth::Auth() {}
Auth::~Auth() {}

/**
 * @brief Generates SHA-256 hash of a password.
 * @param password Input plain-text password.
 * @return SHA-256 hash as string.
 */
std::string Auth::generateHash(const std::string &password)
{
    return sha256(password);
}

/**
 * @brief Verifies a password against an expected SHA-256 hash.
 * @param password Plain-text password.
 * @param hash Expected SHA-256 hash.
 * @return True if password matches hash, else false.
 */
bool Auth::verifyPassword(const std::string &password, const std::string &hash)
{
    return generateHash(password) == hash;
}
