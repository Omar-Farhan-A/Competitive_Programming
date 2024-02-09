vector<ll> getDivisors(ll n) {
    vector<ll> ret;
    ll i = 1;
    for (i = 1; i * i < n; i++) {
        if (n % i == 0) {
            ret.push_back(i);
            ret.push_back(n / i);
        }
    }

    if (i * i == n) {
        ret.push_back(i);
    }
    return ret;
}