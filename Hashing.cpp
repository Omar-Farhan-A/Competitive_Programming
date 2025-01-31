vector<ll> pw1(N), pw2(N);
ll mod1 = 1e9 + 7, mod2 = 2e9 + 11, base1 = 31, base2 = 37, inv1, inv2;

ll fpow(ll x, ll y, ll m) {
    ll prod = x, ans = 1;
    while (y) {
        if (y & 1)ans *= prod, ans %= m;
        prod *= prod;
        prod %= m;
        y >>= 1;
    }
    return ans;
}

ll sub(ll a, ll b, ll m) {
    a -= b;
    if (a < 0)a += m;
    return a;
}

void init() {
    inv1 = fpow(base1, mod1 - 2, mod1);
    inv2 = fpow(base2, mod2 - 2, mod2);
    pw1[0] = pw2[0] = 1;
    for (int i = 1; i < N; i++) {
        pw1[i] = (pw1[i - 1] * base1) % mod1;
        pw2[i] = (pw2[i - 1] * base2) % mod2;
    }

}

class Hashing {
private:
    string s;
    int n;
    vector<array<ll, 2>> prefix, suffix;
public:
    Hashing(string &t) {
        s = '#' + t;
        n = sz(s);
        prefix = suffix = vector<array<ll, 2>>(n + 5);
        for (int i = 1; i <= n; i++) {
            (prefix[i][0] = prefix[i - 1][0] * base1 + (s[i] - 'a' + 1)) %= mod1;
            (prefix[i][1] = prefix[i - 1][1] * base2 + (s[i] - 'a' + 1)) %= mod2;
        }
        for (int i = n; i >= 1; i--) {
            (suffix[i][0] = suffix[i + 1][0] * base1 + (s[i] - 'a' + 1)) %= mod1;
            (suffix[i][1] = suffix[i + 1][1] * base2 + (s[i] - 'a' + 1)) %= mod2;
        }
    }

    array<ll, 2> getPrefix(int l, int r) {
        ll h1 = sub(prefix[r][0], pw1[r - l + 1] * prefix[l - 1][0] % mod1, mod1);
        ll h2 = sub(prefix[r][1], pw2[r - l + 1] * prefix[l - 1][1] % mod2, mod2);
        return {h1, h2};
    }

    array<ll, 2> getSuffix(int l, int r) {
        ll h1 = sub(suffix[l][0], pw1[r - l + 1] * suffix[r + 1][0] % mod1, mod1);
        ll h2 = sub(suffix[l][1], pw2[r - l + 1] * suffix[r + 1][1] % mod2, mod2);
        return {h1, h2};
    }

    bool isPalindrome(int l, int r) {
        return getPrefix(l, r) == getSuffix(l, r);
    }


};
