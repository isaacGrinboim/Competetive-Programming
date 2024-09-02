#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
using namespace std;
typedef long long ll;
vector<bool> sieve(int n) {
    vector<bool> ps(n + 1, true);
    ps[0] = false;
    ps[1] = false;
    int sqrtn = sqrt(n);
    for (int i = 2; i <= sqrtn; ++i) {
        if (ps[i]) {
            for (int j = i * i; j <= n; j += i) {
                ps[j] = false;
            }
        }
    }
    return ps;
}
void modifiedSieve(ll L, ll U, vector<bool>& isPrime) {
    ll limit = sqrt(U) + 1;
    vector<bool> basePrimes = sieve(limit);
    fill(isPrime.begin(), isPrime.end(), true);
    if (L == 1) isPrime[0] = false;
    for (ll i = 2; i <= limit; ++i) {
        if (basePrimes[i]) {
            for (ll j = max(i * i, (L + i - 1) / i * i); j <= U; j += i) {
                isPrime[j - L] = false;
            }
        }
    }
}
pair<ll, ll> getAdjacentPrimes(const vector<bool>& isPrime, ll L, ll U) {
    ll prev = -1, first = -1, second = -1;
    for (ll i = L; i <= U; ++i) {
        if (isPrime[i - L]) {
            if (prev != -1) {
                first = prev;
                second = i;
                break;
            }
            prev = i;
        }
    }
    return {first, second};
}
void solve(ll L, ll U) {
    vector<bool> isPrime(U - L + 1);
    modifiedSieve(L, U, isPrime);
    pair<ll, ll> closest, farest;
    closest = farest = getAdjacentPrimes(isPrime, L, U);
    if (closest.first == -1 || closest.second == -1) {
        cout << "There are no adjacent primes." << endl;
        return;
    }
    ll mini = closest.second - closest.first;
    ll maxi = closest.second - closest.first;
    ll prev = closest.second;
    for (ll i = closest.second + 1; i <= U; ++i) {
        if (isPrime[i - L]) {
            ll dist = i - prev;
            if (dist < mini) {
                mini = dist;
                closest = {prev, i};
            }
            if (dist > maxi) {
                maxi = dist;
                farest = {prev, i};
            }
            prev = i;
        }
    }
    cout << closest.first << "," << closest.second << " are closest, ";
    cout << farest.first << "," << farest.second << " are most distant." << endl;
}
int main() {
    ll L, U;
    while (cin >> L >> U) {
        solve(L, U);
    }
    return 0;
}
