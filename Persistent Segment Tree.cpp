template<typename T=int>
class Persistent_Segment_Tree {
public:
    struct Node {
        int left, right;
        T val;

        Node() {
            val = left = right = 0;
        }
    };

private:
    vector<Node> sg;
    vector<int> roots;
    int Nodes = 0, siz;
public:
    Persistent_Segment_Tree(int n, vector<int> a) {
        siz = 1;
        while (siz <= n)siz <<= 1;
        sg.resize(siz * 20);
        roots.push_back(build(1, siz, a));

    }

    T merge(T a, T b) {
        return a + b;
    }

    int build(int lx, int rx, vector<int> &a) {
        int curNode = Nodes++;
        if (lx == rx) {
            if (lx <= a.size())
                sg[curNode].val = a[lx - 1];
            return curNode;
        }
        int m = (lx + rx) >> 1;
        sg[curNode].left = build(lx, m, a);
        sg[curNode].right = build(m + 1, rx, a);
        sg[curNode].val = merge(sg[sg[curNode].left].val, sg[sg[curNode].right].val);
        return curNode;
    }

    T query(int node, int lx, int rx, int l, int r) {
        if (r < lx || rx < l)return 0;
        if (lx >= l && r >= rx)return sg[node].val;
        int m = (lx + rx) >> 1;
        return merge(query(sg[node].left, lx, m, l, r), query(sg[node].right, m + 1, rx, l, r));
    }

    int update(int prevNode, int lx, int rx, int i, T val) {
        int curNode = Nodes++;
        if (lx == rx) {
            sg[curNode].val = val;
            return curNode;
        }
        // copy prev Node's values
        sg[curNode] = sg[prevNode];
        int m = (lx + rx) >> 1;
        if (i <= m) {
            sg[curNode].left = update(sg[prevNode].left, lx, m, i, val);
        } else {
            sg[curNode].right = update(sg[prevNode].right, m + 1, rx, i, val);
        }
        sg[curNode].val = merge(sg[sg[curNode].left].val, sg[sg[curNode].right].val);
        return curNode;
    }

    T query(int l, int r, int k) {
        return query(roots[k - 1], 1, siz, l, r);
    }

    void update(int k, int i, T val) {
        roots[k - 1] = update(roots[k - 1], 1, siz, i, val);
    }

    void makeCopy(int k) {
        roots.push_back(roots[k - 1]);
    }

};
