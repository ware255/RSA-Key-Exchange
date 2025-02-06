#ifndef _RSA_HPP_
#define _RSA_HPP_

#include <cstdint>
#include <vector>

class RSA {
	uint64_t n;
	uint64_t d;
	uint64_t e;
	uint64_t x;

    // Vector of all primes up to 100
    std::vector<uint64_t> primes;

    // Creates a list of all prime numbers to pull from
    void _listPrimes();
    void CreateKey();
public:
    RSA();
    uint64_t Encrypt(uint64_t x);
    uint64_t Decrypt(uint64_t c);
    uint64_t getPubKey() { return n; }
    void setPubKey(uint64_t N) { n = N, e = 257; }
};

#endif
