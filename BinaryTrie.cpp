class BinaryTrie {
    struct Node {
        int next[2], fre[2];

        Node() {
            memset(next, -1, sizeof next);
            fre[0] = fre[1] = 0;
        }
    };

    vector<Node> trie;
public:

    BinaryTrie() {
        trie = vector<Node>(1);
    }

    void update(ll x, int op = 1) {
        int v = 0;
        for (int i = 63; ~i; i--) {
            bool on = (x >> i) & 1;
            if (!trie[v].fre[on]) {
                trie[v].next[on] = int(trie.size());
                trie.emplace_back();
            }
            trie[v].fre[on] += op;
            v = trie[v].next[on];
        }
    }

    ll query_max(ll x) {
        int v = 0;
        ll ans = 0;
        for (int i = 63; ~i; i--) {
            bool on = (x >> i) & 1;
            if (trie[v].fre[!on]) {
                ans |= (1ll << i);
                v = trie[v].next[!on];
            } else {
                v = trie[v].next[on];
            }
        }
        return ans;
    }

    ll query_min(ll x) {
        // must iterate over all bits
        return -1ll ^ query_max(-1ll ^ x);
    }
};
