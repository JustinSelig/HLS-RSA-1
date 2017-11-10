#include "rsa.hpp"

int gcd(int a, int h) {
    int temp;
    while(1) {
	    temp = a % h;
		if (temp == 0) {
		    return h;
		}
		a = h;
		h = temp;
	}
}

int get_prime()
{
    
    
}

int key_gen(public_key * pk, private_key *sk)
{
	//generate private key
    int p = get_prime();
	int q = get_prime();
	int n = p * q;
    int totient = (p-1)*(q-1); //phi

	//calculate  e
	int count;
	int e = 2; //1 < e < totient
	while (e < totient) {
	    count = gcd(e, totient);
		if (count == 1) {
		    break;
		}
		else {
		    e++;
		}
	}

	//choose arbitrary k
	int k = 2;

	//calculate modinv to get secret exponent
	int d = (1 + (k * totient)) / e;

	//set secret key values
	sk->p = p;
	sk->q = q;
	sk->n = n;
	sk->e = e;
	sk->d = d;

	//set public key values
	pk->n = n;
	pk->e = e;
}

int encrypt(int plaintext, public_key *pk)
{

}

int decrypt(int cyphertext, private_key *sk)
{

}

int power(int base, int power) {
    if (power == 0) {
        return 1;
    } else {
        int sum = base;
        for (int i = 1; i < power; i++) {
            sum *= base;
        }
        return sum;
    }
}
