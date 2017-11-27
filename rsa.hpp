#ifndef __RSA_HPP__
#define __RSA_HPP__

/**
 * RSA implementation for ECE 5770 Final Project
 */

#include <stdlib.h>
#include <hls_stream.h>
#include "typedefs.h"
//#include "hls_math.h"

//Public key struct
typedef struct public_key
{
    //mod
    rsa_t n;

    //exponent
    rsa_t e;

} public_key_t;

//Private key struct
typedef struct private_key
{
    //modulus
    rsa_t n;

    //public exponent
    rsa_t e;

    //private exponent
    rsa_t d;

    //prime 1
    rsa_t p;

    //prime 2
    rsa_t q;

} private_key_t;


//----------------------------------------------------------
// key_gen
//
// Generates private key and public key for one individual
// Returns error code on failure
//----------------------------------------------------------
// @param[in]  : pk    - public key struct generated
// @param[in]  : sk - private (secret) key struct generated
// @param[out] : int    - 0 on success
//
int key_gen(public_key * pk, private_key *sk);

//----------------------------------------------------------
// encrypt
//
// Takes plaintext int and public key as input, returns ciphertext int
//----------------------------------------------------------
// @param[in]  : pk    - public key struct generated
// @param[in]  : sk - private (secret) key struct generated
// @param[out] : int    - ciphertext int
//
int encrypt(rsa_t plaintext, public_key_t *pk);

//----------------------------------------------------------
// decrypt
//
// Takes cyphertext int and private key as input, returns plaintext int
//----------------------------------------------------------
// @param[in]  : pk    - public key struct generated
// @param[in]  : sk - private (secret) key struct generated
// @param[out] : int    - ciphertext int
//
int decrypt(rsa_t cyphertext, private_key_t *sk);

/**
 * Takes a base number and raises it to a given power.
 * @param base - The base to be raised to a power
 * @param power - The power the base should be raised to
 * @return - base ** power
 */
int power(int base, int power);

int power2(rsa_t x, rsa_t y, rsa_t p);

void dut(hls::stream<bit32_t> &strm_in, hls::stream<bit32_t> &strm_out);
#endif /* __RSA_HPP__ */
