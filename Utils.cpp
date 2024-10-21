#include "utils.h"
#include <openssl/evp.h>  // EVP API for cryptographic operations
#include <sstream>
#include <iomanip>
using namespace std;

string hashPassword(const string& password) {
    // Initialize EVP context
    EVP_MD_CTX* context = EVP_MD_CTX_new();
    if (context == nullptr) {
        throw runtime_error("Failed to create EVP context.");
    }

    // Initialize digest operation for SHA-256
    if (1 != EVP_DigestInit_ex(context, EVP_sha256(), nullptr)) {
        EVP_MD_CTX_free(context);
        throw runtime_error("Failed to initialize SHA-256.");
    }

    // Update the context with the password data
    if (1 != EVP_DigestUpdate(context, password.c_str(), password.size())) {
        EVP_MD_CTX_free(context);
        throw runtime_error("Failed to update SHA-256.");
    }

    // Finalize the digest and obtain the result
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int lengthOfHash = 0;
    if (1 != EVP_DigestFinal_ex(context, hash, &lengthOfHash)) {
        EVP_MD_CTX_free(context);
        throw runtime_error("Failed to finalize SHA-256.");
    }

    // Clean up
    EVP_MD_CTX_free(context);

    // Convert hash to a hex string
    stringstream ss;
    for (unsigned int i = 0; i < lengthOfHash; ++i) {
        ss << hex << setw(2) << setfill('0') << (int)hash[i];
    }

    return ss.str();
}
