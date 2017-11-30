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

    Timer encTimer("Encryption time");
    Timer decTimer("Decryption time");

    // Encrypt our values
    encTimer.start();

    // Send data to be encrypted
    


    for (int j = 0; j < NUM_TESTS; j++) {

      // Send the message to be encrypted
      rsa_t sendMsg = toEnc[j];
      for (int i = 0; i < KEY_SIZE / 32; i++) {
	rsa_in.write(sendMsg((i + 1) * 32 - 1, i * 32));
      }

      // Send the exponent for encryption
      rsa_t sendExp = publicKeys.e;
      for (int i = 0; i < KEY_SIZE / 32; i++) {
	rsa_in.write(sendExp((i + 1) * 32 - 1, i * 32));
      }

      // Send the modulus key for encryption
      rsa_t sendKey = publicKeys.n;
      for (int i = 0; i < KEY_SIZE / 32; i++) {
	rsa_in.write(sendKey((i + 1) * 32 - 1, i * 32));
      }
    }

    // Get our encryped values back

    for (int j = 0; j < NUM_TESTS; j++) {
      dut(rsa_in, rsa_out);

      // Read and store result
      rsa_t result;
      for (int i = 0; i < KEY_SIZE / 32; i++) {
	result((i + 1) * 32 - 1, i * 32) = rsa_out.read();
      }
      encrypted[j] = result;
    }
    encTimer.stop();
}
