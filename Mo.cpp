template<class T=int>
class MO {
private:
    int q, SQ;
    T ans;
    struct Query {
        int l, r, q_idx;
    };
    vector<Query> Q;
    vector<T> v;

    void add(int i) {
       ans+=v[i];
    }

    void remove(int i) {
       ans-=v[i];
    }

    T calc(...) {
        return ans;
    }

public:
    MO(vector<T> &v) {
        q = 0;
        ans = 0;
        this->v = v;
        SQ = sqrt(v.size());
    }

    void add_query(int l, int r) {
        Q.push_back({l, r, q++});
    }

    void process() {
        vector<T> ans_query(q);
        std::sort(Q.begin(), Q.end(), [&](Query &a, Query &b) {
            if (a.l / SQ != b.l / SQ) {
                return a.l / SQ < b.l / SQ;
            }
            return a.r < b.r;
        });
        int l = 1, r = 0;
        for (auto [L, R, idx]: Q) {
            while (r < R)
                add(++r);
            while (l > L)
                add(--l);
            while (r > R)
                remove(r--);
            while (l < L)
                remove(l++);
            ans_query[idx] = calc();
        }
        for (auto it: ans_query) {
            cout << it<<'\n';
        }
        for (int i = Q.back().l; i <= Q.back().r; i++) remove(i);
    }
};
