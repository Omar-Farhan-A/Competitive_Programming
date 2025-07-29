ll power(ll n, ll k) {
    ll res = 1;
    while (k) {
        if (k & 1)res = res * n % MOD;
        n = n * n;
        k >>= 1;
    }
    return res;
}
