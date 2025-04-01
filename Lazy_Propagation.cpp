template<typename T=int>
class Segment_Tree {
    struct Node {
        T val, lazy;

        Node(T v = 0) {
            val = v;
            lazy = 0;
        }

        void apply(int lx, int rx, T v) {
            val += v * (rx - lx + 1);
            lazy += v;
        }

        void merge(Node a, Node b) {
            val = a.val + b.val;
        }
    };

    vector<Node> sg;
    int size;

    void propagate(int x, int lx, int rx) {
        if (!sg[x].lazy)return;
        int m = (lx + rx) >> 1;
        if (lx != rx) {
            sg[2 * x + 1].apply(lx, m, sg[x].lazy);
            sg[2 * x + 2].apply(m + 1, rx, sg[x].lazy);
        }
        sg[x].lazy = 0;
    }

    void build(int x, int lx, int rx, vector<int> &a) {
        if (lx == rx) {
            sg[x].apply(lx, rx, lx < a.size() ? a[lx] : 0);
            return;
        }
        int m = (lx + rx) >> 1;
        build(2 * x + 1, lx, m, a);
        build(2 * x + 2, m + 1, rx, a);
        sg[x].merge(sg[2 * x + 1], sg[2 * x + 2]);
    }

    void update(int x, int lx, int rx, int l, int r, T val) {
        if (lx > r || rx < l)return;
        if (l <= lx && rx <= r) {
            sg[x].apply(lx, rx, val);
            return;
        }
        int m = (lx + rx) >> 1;
        propagate(x, lx, rx);
        update(2 * x + 1, lx, m, l, r, val);
        update(2 * x + 2, m + 1, rx, l, r, val);
        sg[x].merge(sg[2 * x + 1], sg[2 * x + 2]);
    }

    T query(int x, int lx, int rx, int l, int r) {
        if (lx > r || rx < l)return 0;
        propagate(x, lx, rx);
        if (l <= lx && rx <= r) {
            return sg[x].val;
        }
        int m = (lx + rx) >> 1;
        return query(2 * x + 1, lx, m, l, r) + query(2 * x + 2, m + 1, rx, l, r);
    }

public:
    Segment_Tree(vector<int> &a) {
        size = 1;
        while (size < a.size())size <<= 1;
        sg.resize(size << 1);
        build(0, 0, size - 1, a);
    }

    T query(int l, int r) {
        return query(0, 0, size - 1, l, r);
    }

    void update(int l, int r, T val) {
        update(0, 0, size - 1, l, r, val);
    }
};
