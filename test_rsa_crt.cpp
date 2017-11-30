#include "test_rsa.hpp"


int main() {
    // Initialize our rng
    //std::mt19937 rng(std::chrono::system_clock::now().time_since_epoch().count());
    // Arrays are related via index
    rsa_t toEnc[NUM_TESTS];
    rsa_t encrypted[NUM_TESTS];
    rsa_t decrypted[NUM_TESTS];
    // Initialize keys
    public_key_t publicKeys = {0, 0};
    private_key_t private_keys = {0, 0, 0, 0, 0};

    // HLS streams for communicating with the enc block
    hls::stream<bit32_t> rsa_in;
    hls::stream<bit32_t> rsa_out;

    // Generate keys
    int rc = key_gen(&publicKeys, &private_keys);

    if (rc != 0) {
        std::cout << "Key generation failed" << std::endl;
        return 1;
    }

    for (int i = 0; i < NUM_TESTS; i++) {
        // Get random message to encrypt
        //toEnc[i] = rng();
        toEnc[i] = rand() % 10; //random int from 0-9
    }

//    Timer encTimer("Encryption time");
    Timer decTimer("Decryption time");

    // Encrypt our values
//    encTimer.start();

    // Send data to be encrypted
    for (int i = 0; i < NUM_TESTS; i++) {
//      rsa_in.write(toEnc[i]);
//      rsa_in.write(publicKeys.e);
//      rsa_in.write(publicKeys.n);
      encrypted[i] = encrypt(toEnc[i], &publicKeys);
    }

    // Get our encryped values back
//    for (int i = 0; i < NUM_TESTS; i++) {
//      dut(rsa_in, rsa_out);

      // Read and store result
//      encrypted[i] = rsa_out.read();
//    }
//    encTimer.stop();

    // Precompute values for decryption
    rsa_t dp = private_keys.d % (private_keys.p - 1);
    rsa_t dq = private_keys.d % (private_keys.q - 1);
    rsa_t qinv = mod_inv(private_keys.q, private_keys.p);
    
    decTimer.start();
    // Send values to be decrypted
    for (int i = 0; i < NUM_TESTS; i++) {
      rsa_in.write(encrypted[i]);
      rsa_in.write(private_keys.p);
      rsa_in.write(private_keys.q);
      rsa_in.write(dp);
      rsa_in.write(dq);
      rsa_in.write(qinv);
    }

    // retrieve decrypted values
    for (int i = 0; i < NUM_TESTS; i++) {
      dut_crt(rsa_in, rsa_out);
      decrypted[i] = rsa_out.read();
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
        std::cout << "There are " << numWrong << " wrong crt encryption/decryptions" << std::endl;
    }
}
