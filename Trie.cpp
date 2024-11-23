class Trie {
    struct Node {
        int next[26], prefix, end;

        Node() {
            memset(next, -1, sizeof next);
            prefix = end = 0;
        }
    };

    vector<Node> trie;
public:

    Trie() {
        trie = vector<Node>(1);
    }

    void insert(string &s) {
        int v = 0;
        for (auto &ch: s) {
            int c = ch - 'a';
            if (trie[v].next[c] == -1) {
                trie[v].next[c] = int(trie.size());
                trie.emplace_back();
            }
            v = trie[v].next[c];
            trie[v].prefix++;
        }
        trie[v].end++;
    }

    int cnt_word(string &s) {
        int v = 0;
        for (auto &ch: s) {
            int c = ch - 'a';
            if (trie[v].next[c] == -1) {
                return 0;
            }
            v = trie[v].next[c];
        }
        return trie[v].end;
    }

    int cnt_prefix(string &s) {
        int v = 0;
        for (auto &ch: s) {
            int c = ch - 'a';
            if (trie[v].next[c] == -1) {
                return 0;
            }
            v = trie[v].next[c];
        }
        return trie[v].prefix;
    }
};
