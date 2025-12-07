const int mod = 1e9 + 7;

struct Mobius {
    int n;
    vector<int> frq, mob, primes;

    Mobius(vector<int> &a) {
        n = *std::max_element(a.begin(), a.end());
        frq.assign(n + 1, 0);
        for (auto &x: a)frq[x]++;
        compute();
    }

    void compute() {
        mob.assign(n + 1, 1);
        vector<int> lp(n + 1);
        for (int i = 2; i <= n; i++) {
            if (lp[i] == 0) {
                lp[i] = i;
                primes.push_back(i);
                mob[i] = -1;
            }
            for (int p: primes) {
                if (p > lp[i] || 1LL * i * p > n) break;
                lp[i * p] = p;
                if (p == lp[i]) {
                    mob[i * p] = 0;
                } else {
                    mob[i * p] = -mob[i];
                }
            }
        }
    }

    vector<ll> gcdPairs() {
        vector<ll> C(n + 1, 0);
        for (int k = 1; k <= n; k++) {
            for (int m = k; m <= n; m += k) {
                C[k] += frq[m];
            }
        }
        vector<ll> T(n + 1, 0);
        for (int k = 1; k <= n; k++) {
            T[k] = (C[k] - 1) * C[k];
        }
        vector<ll> ret(n + 1, 0);
        for (int k = 1; k <= n; k++) {
            ll sum = 0;
            for (int d = 1; k * d <= n; d++) {
                sum += mob[d] * T[k * d];
                sum %= mod;
            }
            ret[k] = sum;
        }
        return ret;
    }

    vector<ll> lcmPairs() {
        vector<ll> D(n + 1, 0);
        for (int d = 1; d <= n; d++) {
            if (frq[d] == 0) continue;
            for (int m = d; m <= n; m += d) {
                D[m] += frq[d];
            }
        }

        vector<ll> ret(n + 1, 0);
        for (int k = 1; k <= n; k++) {
            ll sum = 0;
            for (int d = 1; d * d <= k; d++) {
                if (k % d == 0) {
                    int x = k / d;
                    sum += mob[d] * 1LL * (D[x] - 1) * D[x];
                    if (d * d != k) {
                        int y = d;
                        sum += mob[k / d] * 1LL * (D[y] - 1) * D[y];
                    }
                }
                sum %= mod;
            }
            ret[k] = sum;
        }

        return ret;
    }

};
