mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

struct Treap {
    struct Node {
        int key, cnt;
        uint64_t priority;
        Node *left, *right;

        Node(int key): key(key), priority(rng()), left(nullptr), right(nullptr), cnt(1) {
        }
    };

    using pnode = Node *;
    pnode root = nullptr;

    int size(pnode t) {
        return t ? t->cnt : 0;
    }

    void update(pnode t) {
        if (t)
            t->cnt = 1 + size(t->left) + size(t->right);
    }

    void split(pnode t, int key, pnode &l, pnode &r) {
        if (!t) {
            l = r = nullptr;
            return;
        }
        if (t->key <= key) {
            split(t->right, key, t->right, r);
            l = t;
            update(l);
        } else {
            split(t->left, key, l, t->left);
            r = t;
            update(r);
        }
    }

    pnode merge(pnode a, pnode b) {
        if (!a)return b;
        if (!b)return a;
        if (a->priority > b->priority) {
            a->right = merge(a->right, b);
            update(a);
            return a;
        }
        b->left = merge(a, b->left);
        update(b);
        return b;
    }

    bool find(pnode t, int key) {
        if (!t)return false;
        if (t->key == key)return true;
        if (t->key > key)return find(t->left, key);
        return find(t->right, key);
    }

    bool find(int key) {
        return find(root, key);
    }

    void insert(int key) {
        if (find(key))return;
        pnode a, b;
        split(root, key, a, b);
        auto node = new Node(key);
        root = merge(merge(a, node), b);
    }

    void erase(pnode &t, int key) {
        if (!t)return;
        if (t->key == key) {
            pnode tmp = t;
            t = merge(t->left, t->right);
            delete tmp;
        } else if (t->key > key) {
            erase(t->left, key);
        } else erase(t->right, key);
        update(t);
    }

    void erase(int key) {
        erase(root, key);
    }
};
