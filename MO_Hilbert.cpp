template<class T=int>
class MO {
private:
    static inline int64_t hilbertOrder(int x, int y, int pow, int rotate) {
        if (pow == 0) return 0;
        int hpow = 1 << (pow - 1);
        int seg = (x < hpow) ? ((y < hpow) ? 0 : 3) : ((y < hpow) ? 1 : 2);
        seg = (seg + rotate) & 3;
        const int rotateDelta[4] = {3, 0, 0, 1};
        int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
        int nrot = (rotate + rotateDelta[seg]) & 3;
        int64_t subSquareSize = int64_t(1) << (2 * pow - 2);
        int64_t ordd = seg * subSquareSize;
        int64_t add = hilbertOrder(nx, ny, pow - 1, nrot);
        ordd += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
        return ordd;
    }


    struct Query {
        int l, r, q_idx;
        int64_t ord;

        Query(int L = 0, int R = 0, int Idx = 0) : l(L), r(R), q_idx(Idx) {
            calcOrder();
        }

        inline void calcOrder() {
            ord = hilbertOrder(l, r, 20, 0); // 20 should be minimum such that 2^20 >= n
        }

        bool operator<(const Query &rhs) const {
            return ord < rhs.ord;
        }
    };

    int q;
    vector<Query> Q;
    vector<T> v;

    void add(int i) {
       
    }

    void remove(int i) {
       
    }

    T calc(...) {
      
        return 0;
    }

public:
    MO(vector<T> &v) {
        q = 0;
        this->v = v;

    }

    void add_query(int l, int r) {
        Q.push_back({l, r, q++});
    }

    void process() {
        vector<T> ans_query(q);
        std::sort(Q.begin(), Q.end());
        int l = 1, r = 0;
        for (auto [L, R, idx, ord]: Q) {
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
            cout << it << '\n';
        }
    }
};
