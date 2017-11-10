#include "test_rsa.hpp"

#define NUM_TESTS (100)

int main() {
    // Initialize our rng
    std::mt19937_64 rng(std::chrono::system_clock::now().time_since_epoch().count());
    // Arrays are related via index
    int toEnc[NUM_TESTS];
    int encrypted[NUM_TEST];
    int decrypted[NUM_TESTS];
    public_key_t *publicKeys[NUM_TESTS];
    private_key_t *private_keys[NUM_TESTS];
    // array of corresponding public keys
    // array of corresponding private keys

    for (int i = 0; i < NUM_TESTS; i++) {
        // Generate key pairs
        // Get random message to encrypt
    }

    Timer encTime("Encryption time");
    Timer decTime("Decryption time");

    // Encrypt our values
    encTimer.start();

    for (int i = 0; i < NUM_TESTS; i++) {
        encypted[i] = encrypt(toEnc[i], publicKeys[i]);
    }
    encTimer.stop();

    decTime.start();
    // Decrypt values
    for (int i = 0; i < NUM_TESTS; i++) {
        decrypted[i] = decrypt(encrypted[i], privateKeys[i]);
    }
    decTime.stop();

    // Verify values
    int numWrong = 0;
    for (int i = 0; i < NUM_TESTS; i++) {
        if (toEnc[i] != decrypted[i]) {
            numWrong++;
        }
    }

    if (numWrong > 0) {
        std::cout << "There are " << numWrong << "encryption/decryptions" << std::endl;
    }
}
