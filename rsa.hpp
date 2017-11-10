/**
 * RSA implementation for ECE 5770 Final Project
 */

//Public key struct
typedef struct 
{
	//mod
    int n;
	
	//exponent
    int e;
	
} public_key;

//Private key struct
typedef struct
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

} private_key;
 
 
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
int encrypt(int plaintext, public_key *pk);

//----------------------------------------------------------
// decrypt
//
// Takes cyphertext int and private key as input, returns plaintext int
//----------------------------------------------------------
// @param[in]  : pk    - public key struct generated
// @param[in]  : sk - private (secret) key struct generated
// @param[out] : int    - ciphertext int
//
int decrypt(int cyphertext, private_key *sk);
