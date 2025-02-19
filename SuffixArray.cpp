void count_sort(vector<int> &p, vector<int> &c) {
    int n = p.size();
    vector<int> pos(n), cnt(n), p_new(n);
    for (auto &x: c) {
        cnt[x]++;
    }
    for (int i = 1; i < n; i++) {
        pos[i] = pos[i - 1] + cnt[i - 1];
    }
    for (auto &x: p) {
        int i = c[x];
        p_new[pos[i]++] = x;
    }
    p.swap(p_new);
}

vector<int> p, c, lcp;

void process(string s) {
    s += "$";
    int n = s.size();
    p = c = lcp = vector<int>(n);
    {
        vector<pair<int, int>> a(n);
        for (int i = 0; i < n; i++) {
            a[i] = {s[i], i};
        }
        std::sort(a.begin(), a.end());
        for (int i = 0; i < n; i++) {
            p[i] = a[i].second;
        }
        c[p[0]] = 0;
        for (int i = 1; i < n; i++) {
            if (s[p[i]] == s[p[i - 1]]) {
                c[p[i]] = c[p[i - 1]];
            } else c[p[i]] = c[p[i - 1]] + 1;
        }
    }
    int k = 0;
    while ((1 << k) < n) {
        for (int i = 0; i < n; i++) {
            p[i] = p[i] - (1 << k);
            if (p[i] < 0)p[i] += n;
        }
        count_sort(p, c);
        vector<int> c_new(n);
        c_new[p[0]] = 0;
        for (int i = 1; i < n; i++) {
            pair<int, int> prev = {c[p[i - 1]], c[(p[i - 1] + (1 << k)) % n]};
            pair<int, int> cur = {c[p[i]], c[(p[i] + (1 << k)) % n]};
            if (cur == prev) {
                c_new[p[i]] = c_new[p[i - 1]];
            } else {
                c_new[p[i]] = c_new[p[i - 1]] + 1;
            }
        }
        c.swap(c_new);
        k++;
    }
    k = 0;
    for (int i = 0; i < n - 1; i++) {
        int pi = c[i];
        int j = p[pi - 1];
        while (s[i + k] == s[j + k])k++;
        lcp[pi] = k;
        k = max(0, k - 1);
    }
}
