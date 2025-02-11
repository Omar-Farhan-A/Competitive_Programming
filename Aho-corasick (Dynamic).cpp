class AhoCorasick_static {
    struct Node {
        int next[26], link, cnt;

        Node() {
            memset(next, -1, sizeof next);
            cnt = 0;
            link = -1;
        }
    };

    vector<Node> trie;
public:


    void add(string &s) {
        int v = 0;
        for (auto &ch: s) {
            int c = ch - 'a';
            if (trie[v].next[c] == -1) {
                trie[v].next[c] = int(trie.size());
                trie.emplace_back();
            }
            v = trie[v].next[c];
        }
        trie[v].cnt += 1;
    }

    void build() {
        queue<int> q;
        q.push(0);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int c = 0; c < 26; c++) {
                int v = trie[u].next[c];
                if (~v) {
                    int cur = trie[u].link;
                    while (~cur && trie[cur].next[c] == -1) {
                        cur = trie[cur].link;
                    }
                    // link the current node with its suffix link
                    trie[v].link = (~cur ? trie[cur].next[c] : 0);
                    // add suffix cnt to current node
                    trie[v].cnt += trie[trie[v].link].cnt;
                    q.push(v);
                }
            }
        }
    }

    AhoCorasick_static() {
        trie = vector<Node>(1);
    }

    void clear() {
        trie = vector<Node>(1);
    }

    // count the number of strings form trie in s
    int count(string &s) {
        int ret = 0, v = 0;
        for (auto &i: s) {
            int c = i - 'a';
            while (~v && trie[v].next[c] == -1) {
                v = trie[v].link;
            }
            v = (~v ? trie[v].next[c] : 0);
            ret += trie[v].cnt;
        }
        return ret;
    }

};

class AhoCorasick {
    vector<string> li[20];
    AhoCorasick_static ac[20];
public:
    void add_word(string &s) {
        int pos = 0;
        for (int i = 0; i < 20; i++) {
            if (li[i].empty()) {
                pos = i;
                break;
            }
        }
        li[pos].push_back(s);
        ac[pos].add(s);
        for (int i = 0; i < pos; i++) {
            ac[i].clear();
            for (auto &t: li[i]) {
                li[pos].push_back(t);
                ac[pos].add(t);
            }
            li[i].clear();
        }
        ac[pos].build();
    }

    int get_count(string &s) {
        int count = 0;
        for (int i = 0; i < 20; i++) {
            count += ac[i].count(s);
        }
        return count;
    }

    void delete_word(string &s) {
        for (int i = 0; i < 20; i++) {
            auto it = std::find(li[i].begin(), li[i].end(), s);
            if (it != li[i].end()) {
                li[i].erase(it);
                ac[i].clear();
                for (auto &t: li[i]) {
                    ac[i].add(t);
                }
                ac[i].build();
                break;
            }
        }
    }

};
