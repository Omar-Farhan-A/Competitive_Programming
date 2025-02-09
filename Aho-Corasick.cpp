const static int MAX_N = 5e5 + 7;
vector<int> leaf[MAX_N], adj[MAX_N], seen(MAX_N), ans(MAX_N);

class AhoCorasick {


    struct Node {
        int next[26], end, link, cnt;

        Node() {
            memset(next, -1, sizeof next);
            cnt = 0;
            link = -1;
        }
    };

    vector<Node> trie;
    int siz;

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
        trie[v].end += 1;
        leaf[v].push_back(siz++);
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
                    for (auto &idx: leaf[trie[v].link]) {
                        leaf[v].push_back(idx);
                    }
                }
            }
        }
        // build a directed tree with the suffix links to calculate number of occurrence for each string
        for (int i = 1; i < int(trie.size()); i++) {
            adj[trie[i].link].push_back(i);
        }

    }


public:
    AhoCorasick(vector<string> &p) {
        trie = vector<Node>(1);
        siz = 0;
        for (int i = 0; i < int(p.size()); i++) {
            add(p[i]);
        }
        build();
    }
    // search for string in the trie and calculate occurrence for each suffix 
    void search(string &s) {
        int v = 0;
        for (auto &i: s) {
            int c = i - 'a';
            while (~v && trie[v].next[c] == -1) {
                v = trie[v].link;
            }
            v = (~v ? trie[v].next[c] : 0);
            seen[v]++;
        }
    }
    // count the number of strings form trie in s 
    int count(string &s) {
        int ans = 0, v = 0;
        for (auto &i: s) {
            int c = i - 'a';
            while (~v && trie[v].next[c] == -1) {
                v = trie[v].link;
            }
            v = (~v ? trie[v].next[c] : 0);
            ans += trie[v].cnt;
        }
        return ans;
    }

    // DFS to calculate occurrence of each string in the trie in s
    int dfs(int u = 0) {
        int cur = seen[u];
        for (auto &v: adj[u]) {
            cur += dfs(v);
        }
        for (auto &idx: leaf[u]) {
            ans[idx] = cur;
        }
        return cur;
    }
    // get indexes of occurrence for each string in the trie in s 
    vector<vector<int>> get_occ(string &s) {
        int v = 0, j = 0;
        vector<vector<int>> ret(siz);
        for (auto &i: s) {
            int c = i - 'a';
            while (~v && trie[v].next[c] == -1) {
                v = trie[v].link;
            }
            v = (~v ? trie[v].next[c] : 0);
            for (auto &idx: leaf[v]) {
                ret[idx].push_back(j);
            }
            j++;
        }
        return ret;
    }

};
