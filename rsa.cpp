#include <cstdlib>
#include <cmath>
#include <ctime>
#include "rsa.hpp"

RSA::RSA() {
    srand((unsigned)time(NULL));
    _listPrimes();
    CreateKey();
}

static std::vector<bool> IsPrime;

void RSA::_listPrimes() {
    size_t max = 10000;
    if (max+1 > IsPrime.size())
        IsPrime.resize(max+1,true);
    IsPrime[0] = false;
    IsPrime[1] = false;

    for (size_t i = 2; i <= max; ++i) {
        if (IsPrime[i])
            for (size_t j = i+1; j <= max; ++j)
                if (j % i == 0)
                    IsPrime[j] = false;
        if (IsPrime[i])
            primes.push_back(i);
    }
}

static uint64_t gcd_impl( uint64_t n, uint64_t m ) {
    for( uint64_t i = 0; i < 10; ++i ) {
            uint64_t t = n - m;
            bool q = m > t;
            n = q ? m : t;
            m = q ? t : m;
            if( m == 0 ) { return n; }
    }
    return gcd_impl( m, n % m );
}

static uint64_t gcd( uint64_t n, uint64_t m ) {
    return n > m ? gcd_impl( n, m ) : gcd_impl( m, n );
}

static uint64_t modinv( const uint64_t &a, const uint64_t &m ) {
    uint64_t j = 1, i = 0, b = m, c = a, x, y;
    while ( c != 0 ) {
        x = b / c;
        y = b - x*c;
        b = c;
        c = y;
        y = j;
        j = i - j*x;
        i = y;
    }
    if ( i < 0 )           // z
        i += m;
    return i;
}

static uint64_t modpow(uint64_t a, uint64_t b, uint64_t n){
    if(b == 0)
        return 1;
    if((b & 1) == 0) {
        uint64_t x = modpow(a,b>>1,n);
        x = x % n;
        return (x*x) % n;
    }
    return (a*modpow(a,b-1,n))%n;
}

void RSA::CreateKey() {
    uint64_t p, q;
restart:
    do {
        p = primes[rand() % primes.size()];
        q = primes[rand() % primes.size()];
    } while (p == q);

    n = p * q;
    e = 257;

    while (gcd(p - 1, e) != 1 || gcd(q - 1, e) != 1) e += 2;
    if (e != 257) goto restart;

    d = modinv(e, (p - 1) * (q - 1));
    uint64_t phi = (p - 1) * (q - 1);
    if ((d * e) % phi != 1) goto restart;
}

uint64_t RSA::Encrypt(uint64_t x) {
    return modpow(x, e, n);
}

uint64_t RSA::Decrypt(uint64_t c) {
    return modpow(c, d, n);
}
