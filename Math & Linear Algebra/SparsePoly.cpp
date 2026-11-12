struct SparsePoly {
    map<int, int, greater<int> > a;
    int shift = 0;
    // Get coefficient of x^degree
    int get(int degree) const {
        auto it = a.find(degree - shift);
        return it == a.end() ? 0 : it->second;
    }

    // Add coefficient (modulo mod)
    void add(int degree, int value) {
        value %= mod;
        if (value < 0) value += mod;
        if (!value) return;

        int key = degree - shift;
        int &x = a[key];

        x += value;
        if (x >= mod) x -= mod;
        if (!x) a.erase(key);
    }

    // Create c * x^degree
    static SparsePoly monomial(int degree, int c = 1) {
        SparsePoly p;
        c = (c % mod + mod) % mod;

        if (c) {
            p.shift = degree;
            p.a[0] = c;
        }
        return p;
    }

    // Multiply polynomials (consumes other)
    SparsePoly &operator*=(SparsePoly &other) {
        if (a.empty() || other.a.empty()) {
            a.clear();
            shift = 0;
            return *this;
        }
        // Lazy shift
        shift += other.shift;
        // Small-to-large
        if (a.size() < other.a.size())
            a.swap(other.a);
        // Monomial optimization
        if (other.a.size() == 1) {
            auto [degree, coefficient] = *other.a.begin();
            shift += degree;
            if (coefficient != 1) {
                for (auto &[key, value]: a)
                    value = 1LL * value * coefficient % mod;
            }
            return *this;
        }
        // General multiplication
        map<int, int, greater<int> > res;
        for (auto [i, x]: a) {
            for (auto [j, y]: other.a) {
                int &val = res[i + j];
                val = (val + 1LL * x * y) % mod;
            }
        }
        // Remove zero coefficients
        for (auto it = res.begin(); it != res.end();) {
            if (it->second == 0)
                it = res.erase(it);
            else
                ++it;
        }

        a.swap(res);
        return *this;
    }

    // Remove terms with degree > limit
    void trim(int limit) {
        while (!a.empty() &&
               a.begin()->first + shift > limit)
            a.erase(a.begin());
    }
};
