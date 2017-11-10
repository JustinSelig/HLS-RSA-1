#include "rsa.hpp"

int key_gen(public_key * pk, private_key *sk)
{

}

int encrypt(int plaintext, public_key *pk)
{
    return power(plaintext, pk->e) % pk->n;
}

int decrypt(int cyphertext, private_key *sk)
{
    return power(cyphertext, sk->d) % sk->n
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
