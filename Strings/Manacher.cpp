class Manacher {
    // 0-based
private:
    vector<int> p;
public:
    Manacher(string &s) {
        string t;
        for (auto &c: s) {
            t += string("#") + c;
        }
        t += '#';
        auto res = manacher_odd(t);
        p = vector<int>(begin(res) + 1, end(res));
    }

    vector<int> manacher_odd(string s) {
        int n = int(s.size());
        s = "$" + s + "^";
        vector<int> v(n + 2);
        int l = 1, r = 1;
        for (int i = 1; i <= n; i++) {
            v[i] = max(0, min(r - i, v[l + (r - i)]));
            while (s[i - v[i]] == s[i + v[i]]) {
                v[i]++;
            }
            if (i + v[i] > r) {
                r = i + v[i];
                l = i - v[i];
            }
        }
        return vector<int>(begin(v) + 1, end(v) - 1);
    }

    int get_odd(int i) {
        return p[i << 1] / 2;
    }

    int get_even(int i) {
        return p[i << 1 | 1] / 2;
    }

    int get(int i) {
        return get_even(i) + get_odd(i);
    }

    bool isPalindrome(int l, int r) {
        int m = (l + r) / 2;
        int k = r - l + 1;
        if (k & 1) {
            return get_odd(m) >= k / 2 + 1;
        }
        return get_even(m) >= k / 2;

    }

};
