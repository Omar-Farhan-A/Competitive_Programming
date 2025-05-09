struct xorBasis {
    const int LOG = 32;
    vector<ll> basis;
    int s;

    xorBasis() {
        s = 0;
        basis.resize(LOG);
    }

    bool insert(ll mask) {
        for (int i = LOG - 1; ~i; i--) {
            if ((mask >> i) & 1) {
                if (!basis[i]) {
                    basis[i] = mask;
                    s++;
                    return true;
                }
                mask ^= basis[i];
            }

        }
        return false;
    }

    bool exist(ll mask) {
        for (int i = LOG - 1; ~i; i--) {
            if ((mask >> i) & 1) {
                if (!basis[i]) {
                    basis[i] = mask;
                    return false;
                }
                mask ^= basis[i];
            }

        }
        return true;
    }

    ll get_kth_xor_subset(ll k) {
        // 1 and 0 is the greater subset xor
        ll tot = (1ll << s);
        if (k > tot) return -1;
        ll ans = 0;
        for (int i = LOG - 1; i >= 0; i--) {
            if (!basis[i]) continue;
            tot >>= 1;
            ll on = (ans >> i) & 1;
            if ((k > tot) == on) ans ^= basis[i];
            if (k > tot) k -= tot;
        }
        return ans;
    }
};
