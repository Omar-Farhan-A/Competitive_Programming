class Hashing {
    const ll MOD = (1ll << 61) - 1;
    vector<ll> p{1}, h{0};
    static ll base;

    ll sub(ll a, ll b) {
        a -= b;
        if (a < 0)a += MOD;
        return a;
    }

public:
    Hashing(const auto &a) {
        for (int i = 0; i < a.size(); i++) {
            p.push_back((__int128_t) p[i] * base % MOD);
            h.push_back(((__int128_t) h[i] * base + a[i]) % MOD);
        }
    }

    ll substr(int l, int r) {
        return sub(h[r + 1], (__int128_t) h[l] * p[r - l + 1] % MOD);
    }

    ll merge(ll h1, ll h2, int l2) {
        return ((__int128_t) h1 * p[l2] + h2) % MOD;
    }

};

ll rng(ll l = (1ll << 40), ll r = (1ll << 60)) {
    static std::mt19937 gen(
            std::chrono::steady_clock::now().time_since_epoch().count());
    return std::uniform_int_distribution<long long>(l, r)(gen);
}

ll Hashing::base = rng();
