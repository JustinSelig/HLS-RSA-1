#include "rsa.hpp"


//----------------------------------------------------------
// Top function
//----------------------------------------------------------

void dut(
    hls::stream<bit32_t> &strm_in,
    hls::stream<bit32_t> &strm_out
)
{
  rsa_t msg;
  rsa_t exp;
  rsa_t key;

  bit32_t input_msg = strm_in.read();
  bit32_t input_exp = strm_in.read();
  bit32_t input_key = strm_in.read();

  // read two 32-bit input words into digit
  msg = input_msg;
  exp = input_exp;
  key = input_key;

  rsa_t result = power2(msg, exp, key);
  // write out the result
  strm_out.write(result);
}



int gcd(rsa_t a, rsa_t h) {
    rsa_t temp;
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
int is_prime(rsa_t n) {
    if(n%3==0) return n==3;
    rsa_t p = 5;
    while (p*p <= n) {
        if (n%p==0) return 0;
        p += 2;
        if (n%p==0) return 0;
        p += 4;
    }
    return 1;
}

//generates random prime number in range [lower,upper]
rsa_t get_prime(rsa_t lower, rsa_t upper)
{
    rsa_t spread = upper - lower + 1;
    while (1) {
        rsa_t p = 1 | (rand() % spread + lower);
        if (is_prime(p)) {
            return p;
        }
    }

}

//ref: https://www.thecrazyprogrammer.com/2017/03/rsa-algorithm.html
int key_gen(public_key *pk, private_key *sk)
{
        //generate private key
    rsa_t p = get_prime(0, 50);
    rsa_t q = get_prime(0, 50);
    rsa_t n = p * q;
    rsa_t totient = (p-1)*(q-1); //phi

        //calculate  e
        int count;
        rsa_t e = 2; //1 < e < totient
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
        rsa_t k = 2;

        //calculate modinv to get secret exponent
        rsa_t d = (1 + (k * totient)) / e;

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

int encrypt(rsa_t plaintext, public_key_t *pk)
{
  return power2(plaintext, pk->e, pk->n);
}

int decrypt(rsa_t cyphertext, private_key_t *sk)
{
    return power2(cyphertext, sk->d, sk->n);
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

// Iterative Function to calculate (x^y)%p in O(log y)
// Source: http://www.geeksforgeeks.org/modular-exponentiation-power-in-modular-arithmetic/
int power2(rsa_t x, rsa_t y, rsa_t p)
{
    int res = 1;      // Initialize result

    x = x % p;  // Update x if it is more than or
                // equal to p
    //    int trips = hls::log10((float)y) * 3.3;

 L1 : while (y > 0)
    {
#pragma HLS loop_tripcount max=32
        // If y is odd, multiply x with result
        if (y & 1)
            res = (res*x) % p;

        // y must be even now
        y = y>>1; // y = y/2
        x = (x*x) % p;
    }
    return res;
}
