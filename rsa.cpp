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

//ref: https://math.stackexchange.com/questions/424238/random-primes-between-4000000000-and-4294967291-c
int is_prime(int n) {
    if(n%3==0) return n==3;
    int p = 5;
    while (p*p <= n) {
        if (n%p==0) return 0;
        p += 2;
        if (n%p==0) return 0;
        p += 4;
    }
    return 1;
}

//generates random prime number in range [lower,upper]
int get_prime(int lower, int upper)
{
    int spread = upper - lower + 1;
    while (1) {
        int p = 1 | (rand() % spread + lower);
        if (is_prime(p)) {
            return p;
        }
    }

}

//ref: https://www.thecrazyprogrammer.com/2017/03/rsa-algorithm.html
int key_gen(public_key *pk, private_key *sk)
{
        //generate private key
    int p = get_prime(0, 50);
    int q = get_prime(0, 50);
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
        return 0;
}

int encrypt(int plaintext, public_key_t *pk)
{
    return power(plaintext, pk->e, pk->n);
}

int decrypt(int cyphertext, private_key_t *sk)
{
    return power(cyphertext, sk->d, sk->n);
}

int modMul(int a, int b, int m) {
    long double x;
    int c;
    int r;
    if (a >= m) a %= m;
    if (b >= m) b %= m;
    x = a;
    c = x * b / m;
    r = (int)(a * b - c * m) % (int)m;
    return r < 0 ? r + m : r;
}

int power(int base, int power, int mod) {
    int r = 1;
    while (power > 0) {
        if (power % 2 == 1) {
            r = modMul(r, base, mod);
        }
        power = power >> 1;
        base = modMul(base, base, mod);
    }
    return r;
}
