#ifndef CPLIB_SIEVE_HPP
#define CPLIB_SIEVE_HPP 1

#include <bits/stdc++.h>

using namespace std;

using uint = unsigned;
using ll = long long;
using ull = unsigned long long;
using ld = long double;

namespace cplib {

struct sieve {
    vector<int> lpf;
    vector<int> phi;
    vector<int> mu;
    vector<int> primes;
    int nprimes;
    sieve() : sieve(0) {
    }
    sieve(int up) : lpf(up + 1), phi(up + 1, 1), mu(up + 1, 1), primes{}, nprimes(0) {
        for (int i = 2; i <= up; ++i) {
            if (lpf[i] == 0) {
                lpf[i] = i;
                phi[i] = i - 1;
                mu[i] = -1;
                primes.push_back(i);
            }
            for (int p : primes) {
                if (p > lpf[i] || i * p > up) {
                    break;
                }
                lpf[p * i] = p;
                phi[p * i] = phi[i] * (p == lpf[i] ? p : p - 1);
                mu[p * i] = (p == lpf[i] ? 0 : -mu[i]);
            }
        }
        nprimes = int(primes.size());
    }
};

}  // namespace cplib

#endif  // CPLIB_SIEVE_HPP
