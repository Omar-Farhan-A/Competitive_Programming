template<typename T=int>
class Segment_Tree {
    struct Node {
        T val, lazy;

        Node(T v = 0) {
            val = v;
            lazy = 0;
        }

        void merge(Node a, Node b) {
            val = a.val + b.val;
        }
    };

    vector<Node> sg;
    int size;

    void propagate(int idx, int lx, int rx) {
        if (!sg[idx].lazy)return;
        sg[idx].val += sg[idx].lazy * (rx - lx + 1);
        int left = idx << 1, right = idx << 1 | 1;
        if (lx != rx) {
            sg[left].lazy += sg[idx].lazy;
            sg[right].lazy += sg[idx].lazy;
        }
        sg[idx].lazy = 0;
    }

    void build(int idx, int lx, int rx, vector<int> &a) {
        if (lx == rx) {
            sg[idx] = (lx < a.size() ? a[lx] : 0);
            return;
        }
        int m = (lx + rx) >> 1, left = idx << 1, right = idx << 1 | 1;
        build(left, lx, m, a);
        build(right, m + 1, rx, a);
        sg[idx].merge(sg[left], sg[right]);
    }

    void update(int idx, int lx, int rx, int l, int r, T val) {
        propagate(idx, lx, rx);
        if (lx > r || rx < l)return;
        if (l <= lx && rx <= r) {
            sg[idx].lazy += val;
            propagate(idx, lx, rx);
            return;
        }
        int m = (lx + rx) >> 1, left = idx << 1, right = idx << 1 | 1;
        update(left, lx, m, l, r, val);
        update(right, m + 1, rx, l, r, val);
        sg[idx].merge(sg[left], sg[right]);
    }

    T query(int idx, int lx, int rx, int l, int r) {
        if (lx > r || rx < l)return 0;
        propagate(idx, lx, rx);
        if (l <= lx && rx <= r) {
            return sg[idx].val;
        }
        int m = (lx + rx) >> 1, left = idx << 1, right = idx << 1 | 1;
        return query(left, lx, m, l, r) + query(right, m + 1, rx, l, r);
    }

public:
    Segment_Tree(vector<int> &a) {
        size = 1;
        while (size < a.size())size <<= 1;
        sg.resize(size << 1);
        build(1, 0, size - 1, a);
    }

    T query(int l, int r) {
        return query(1, 0, size - 1, l, r);
    }

    void update(int l, int r, T val) {
        update(1, 0, size - 1, l, r, val);
    }
};
