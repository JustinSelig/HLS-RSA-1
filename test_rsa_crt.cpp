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
        toEnc[i] = rand() % 10; //random int from 0-9
    }

    Timer decTimer("CRT Decryption time");

    // encrypt our data
    for (int i = 0; i < NUM_TESTS; i++) {
      encrypted[i] = encrypt(toEnc[i], &publicKeys);
    }

    // Precompute values for decryption
    rsa_t dp = private_keys.d % (private_keys.p - 1);
    rsa_t dq = private_keys.d % (private_keys.q - 1);
    rsa_t qinv = mod_inv(private_keys.q, private_keys.p);
    
    decTimer.start();
    // Send values to be decrypted
    for (int j = 0; j < NUM_TESTS; j++) {

      // Send the message
      rsa_t sendMsg = encrypted[j];
      for (int i = 0; i < KEY_SIZE / 32; i++) {
	rsa_in.write(sendMsg((i + 1) * 32 - 1, i * 32));
      }

      // Send p
      rsa_t sendP = private_keys.p;
      for (int i = 0; i < KEY_SIZE / 32; i++) {
	rsa_in.write(sendP((i + 1) * 32 - 1, i * 32));
      }

      // Send q
      rsa_t sendQ = private_keys.q;
      for (int i = 0; i < KEY_SIZE / 32; i++) {
	rsa_in.write(sendQ((i + 1) * 32 - 1, i * 32));
      }

      // Send dp
      rsa_t sendDP = dp;
      for (int i = 0; i < KEY_SIZE / 32; i++) {
	rsa_in.write(sendDP((i + 1) * 32 - 1, i * 32));
      }

      // Send dq
      rsa_t sendDQ = dq;
      for (int i = 0; i < KEY_SIZE / 32; i++) {
	rsa_in.write(sendDQ((i + 1) * 32 - 1, i * 32));
      }

      // Send qinv
      rsa_t sendQinv = qinv;
      for (int i = 0; i < KEY_SIZE / 32; i++) {
	rsa_in.write(sendQinv((i + 1) * 32 - 1, i * 32));
      }
    }

    // retrieve decrypted values
    for (int j = 0; j < NUM_TESTS; j++) {
      dut_crt(rsa_in, rsa_out);
      // Read and store result
      rsa_t result;
      for (int i = 0; i < KEY_SIZE / 32; i++) {
	result((i + 1) * 32 - 1, i * 32) = rsa_out.read();
      }
      decrypted[j] = result;
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
