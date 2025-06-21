struct Node {
    ll val{};
    Node *left, *right;

    Node() {}

    Node(int val) : val(val) {}

    Node(Node *l, Node *r) {
        left = l;
        right = r;
        if (left)val += left->val;
        if (right)val += right->val;
    }
};

struct PST {
    int n;
    vector<Node *> roots;

    Node *build(int lx, int rx, vector<int> &a) {
        if (lx == rx)return new Node(a[lx]);
        int m = (lx + rx) >> 1;
        auto left = build(lx, m, a);
        auto right = build(m + 1, rx, a);
        return new Node(left, right);
    }

    Node *update(Node *node, int lx, int rx, int i, int x) {
        if (lx == rx) return new Node(x);
        int m = (lx + rx) >> 1;
        if (i <= m)
            return new Node(update(node->left, lx, m, i, x), node->right);
        else
            return new Node(node->left, update(node->right, m + 1, rx, i, x));
    }

    ll query(Node *node, int lx, int rx, int l, int r) {
        if (lx > r || rx < l) return 0;
        if (l <= lx && rx <= r) return node->val;
        int m = (lx + rx) >> 1;
        return query(node->left, lx, m, l, r) + query(node->right, m + 1, rx, l, r);
    }

    PST(vector<int> &a) {
        n = sz(a);
        roots.push_back(build(0, n - 1, a));
    }

    void update(int k, int i, int x) {
        roots[k] = update(roots[k], 0, n - 1, i, x);
    }

    ll query(int k, int l, int r) {
        return query(roots[k], 0, n - 1, l, r);
    }

    void makeCopy(int k) {
        roots.push_back(roots[k]);
    }
};
