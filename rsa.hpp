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
    int n;

    //exponent
    int e;

} public_key_t;

//Private key struct
typedef struct private_key
{
    //modulus
    int n;

    //public exponent
    int e;

    //private exponent
    int d;

    //prime 1
    int p;

    //prime 2
    int q;

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
int encrypt(int plaintext, public_key_t *pk);

//----------------------------------------------------------
// decrypt
//
// Takes cyphertext int and private key as input, returns plaintext int
//----------------------------------------------------------
// @param[in]  : pk    - public key struct generated
// @param[in]  : sk - private (secret) key struct generated
// @param[out] : int    - ciphertext int
//
int decrypt(int cyphertext, private_key_t *sk);

/**
 * Takes a base number and raises it to a given power.
 * @param base - The base to be raised to a power
 * @param power - The power the base should be raised to
 * @return - base ** power
 */
int power(int base, int power);

int power2(int x, unsigned int y, int p);

void dut(hls::stream<bit32_t> &strm_in, hls::stream<bit32_t> &strm_out);
#endif /* __RSA_HPP__ */
