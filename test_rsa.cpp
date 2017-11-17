#include "test_rsa.hpp"

#define NUM_TESTS (100)

int main() {
    // Initialize our rng
    //std::mt19937 rng(std::chrono::system_clock::now().time_since_epoch().count());
    // Arrays are related via index
    int toEnc[NUM_TESTS];
    int encrypted[NUM_TESTS];
    int decrypted[NUM_TESTS];
    // Initialize keys
    public_key_t publicKeys = {0, 0};
    private_key_t private_keys = {0, 0, 0, 0, 0};

    // Generate keys
    int rc = key_gen(&publicKeys, &private_keys);

    if (rc != 0) {
        std::cout << "Key generation failed" << std::endl;
        return 1;
    }

    for (int i = 0; i < NUM_TESTS; i++) {
        // Get random message to encrypt
        //toEnc[i] = rng();
    }

    Timer encTimer("Encryption time");
    Timer decTimer("Decryption time");

    // Encrypt our values
    encTimer.start();

    for (int i = 0; i < NUM_TESTS; i++) {
        encrypted[i] = encrypt(toEnc[i], &publicKeys);
    }
    encTimer.stop();

    decTimer.start();
    // Decrypt values
    for (int i = 0; i < NUM_TESTS; i++) {
        decrypted[i] = decrypt(encrypted[i], &private_keys);
    }
    decTimer.stop();

    // Verify values
    int numWrong = 0;
    for (int i = 0; i < NUM_TESTS; i++) {
        if (toEnc[i] != decrypted[i]) {
            numWrong++;
        }
    }

    if (numWrong > 0) {
        std::cout << "There are " << numWrong << " wrong encryption/decryptions" << std::endl;
    }
}
