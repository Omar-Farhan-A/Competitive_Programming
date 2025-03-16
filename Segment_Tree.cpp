template<typename T = int>
class Segment_Tree {
    struct Node {
        T sum;

        Node(T v = 0) {
            sum = v;
        }

        void merge(Node a, Node b) {
            sum = a.sum + b.sum;
        }

    };

    vector<Node> sg;

    void build(int x, int lx, int rx, vector<int> &a) {
        if (lx == rx) {
            sg[x] = (lx < a.size() ? a[lx] : 0);
            return;
        }
        int m = (lx + rx) >> 1;
        build(2 * x + 1, lx, m, a);
        build(2 * x + 2, m + 1, rx, a);
        sg[x].merge(sg[2 * x + 1], sg[2 * x + 2]);
    }

    void update(int x, int lx, int rx, int i, T val) {
        if (lx == rx) {
            sg[x] = val;
            return;
        }
        int m = (lx + rx) >> 1;
        if (i <= m)
            update(2 * x + 1, lx, m, i, val);
        else
            update(2 * x + 2, m + 1, rx, i, val);
        sg[x].merge(sg[2 * x + 1], sg[2 * x + 2]);
    }

    T query(int x, int lx, int rx, int l, int r) {
        if (lx > r || rx < l)return 0;
        if (l <= lx && rx <= r) {
            return sg[x].sum;
        }
        int m = (lx + rx) >> 1;
        return query(2 * x + 1, lx, m, l, r) + query(2 * x + 2, m + 1, rx, l, r);
    }

public:
    int size;

    Segment_Tree(vector<int> &a) {
        size = 1;
        while (size < a.size())size <<= 1;
        sg.resize(size << 1);
        build(0, 0, size - 1, a);
    }

    void update(int i, T val) {
        update(0, 0, size - 1, i, val);
    }

    T query(int l, int r) {
        return query(0, 0, size - 1, l, r);
    }

};
