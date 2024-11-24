class Trie {
    struct Node {
        int next[26], prefix, end, par, c;

        Node() {
            memset(next, -1, sizeof next);
            prefix = end = par = 0;
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
                trie[trie[v].next[c]].par = v;
                trie[trie[v].next[c]].c = c;
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

    void remove(string &s) {
        int v = 0;
        for (auto &ch: s) {
            int c = ch - 'a';
            if (trie[v].next[c] == -1)return;
            v = trie[v].next[c];
        }
        trie[v].end--;
        while (v != 0) {
            if (!--trie[v].prefix) {
                trie[trie[v].par].next[trie[v].c] = -1;
            }
            v = trie[v].par;
        }
    }
};
