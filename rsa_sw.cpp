#include "rsa_sw.hpp"

int main() {

  // Arrays are related via index
  rsa_t toEnc[NUM_TESTS];
  rsa_t encrypted[NUM_TESTS];
  rsa_t decrypted[NUM_TESTS];
  // Initialize keys
  public_key_t pk = {0, 0};
  private_key_t sk = {0, 0, 0, 0, 0};

  // Create timers
  Timer encTimer("Encryption time");
  Timer decTimer("Decryption time");
  Timer crtTimer("CRT Decryption time");

  // Generate keys
  int rc = key_gen(&pk, &sk);

  if (rc != 0) {
    std::cout << "Key generation failed" << std::endl;
    return 1;
  }

  for (int i = 0; i < NUM_TESTS; i++) {
    toEnc[i] = rand() % 10;
  }

  // Start to encrypt values
  encTimer.start();

  for (int i = 0; i < NUM_TESTS; i++) {
    encrypted[i] = encrypt(toEnc[i], &pk);
  }
  encTimer.stop();

  decTimer.start();
  // Start decrypting with traditional method
  for (int i = 0; i < NUM_TESTS; i++) {
    decrypted[i] = decrypt(encrypted[i], &sk);
  }
  decTimer.stop();

  // Check our values to make sure we got the correct message back
  int num_wrong = 0;
  for (int i = 0; i < NUM_TESTS; i++) {
    if (toEnc[i] != decrypted[i]) {
      num_wrong++;
    }
  }

  if (num_wrong > 0) {
    std::cout << "Standard RSA has " << num_wrong << " incorrect calculations" << std::endl;
  }

  // Now do decryption with CRT method
  // Precalculate needed values
  rsa_t dp = sk.d % (sk.p - 1);
  rsa_t dq = sk.d % (sk.q - 1);
  rsa_t qinv = mod_inv(sk.q, sk.p);

  crtTimer.start();
  for (int i = 0; i < NUM_TESTS; i++) {
    decrypted[i] = rsaCRT(encrypted[i], sk.p, sk.q, dp, dq, qinv);
  }
  crtTimer.stop();

  // Check our values to make sure we got the correct message back
  num_wrong = 0;
  for (int i = 0; i < NUM_TESTS; i++) {
    if (toEnc[i] != decrypted[i]) {
      num_wrong++;
    }
  }

  if (num_wrong > 0) {
    std::cout << "CRT RSA has " << num_wrong << " incorrect calculations" << std::endl;
  }
}
