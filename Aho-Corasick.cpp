const static int MAX_N = 5e5 + 7;
vector<int> leaf[MAX_N], adj[MAX_N], seen(MAX_N), ans(MAX_N);
 
class AhoCorasick {
 
 
    struct Node {
        int next[26], end, link, par, parc;
 
        Node() {
            memset(next, -1, sizeof next);
            memset(next, -1, sizeof next);
            end = 0;
            par = link = -1;
        }
    };
 
    vector<Node> trie;
 
 
    void add(string &s, int idx) {
        int v = 0;
        for (auto &ch: s) {
            int c = ch - 'a';
            if (trie[v].next[c] == -1) {
                trie[v].next[c] = int(trie.size());
                trie.emplace_back();
                trie.back().par = v;
                trie.back().parc = c;
            }
            v = trie[v].next[c];
        }
        trie[v].end += 1;
        leaf[v].push_back(idx);
    }
 
    void build() {
        queue<int> q;
        q.push(0);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            getLink(u);
            for (int i = 0; i < 26; i++) {
                if (trie[u].next[i] != -1) {
                    q.push(trie[u].next[i]);
                }
            }
        }
        for (int i = 1; i < int(trie.size()); i++) {
            adj[trie[i].link].push_back(i);
        }
 
    }
 
    void getLink(int u) { // call only when all nodes with lower level have already been calculated
        if (trie[u].par == -1) {
            // root
            return;
        }
        int p = trie[u].par;
        if (trie[p].link == -1) {
            // nodes at level 1
            trie[u].link = p;
            return;
        }
        int cur = trie[p].link;
        int c = trie[u].parc;
        while (trie[cur].next[c] == -1) {
            if (trie[cur].link == -1) {
                // cur is now the root
                trie[u].link = cur;
                return;
            }
            cur = trie[cur].link;
        }
        trie[u].link = trie[cur].next[c];
    }
 
public:
    AhoCorasick(vector<string> &p) {
        trie = vector<Node>(1);
        for (int i = 0; i < int(p.size()); i++) {
            add(p[i], i);
        }
        build();
    }
 
    void search(string &s) {
        int v = 0;
        for (int i = 0; i < int(s.size()); i++) {
            int c = s[i] - 'a';
            while (v != 0 && trie[v].next[c] == -1) {
                v = trie[v].link;
            }
            if (trie[v].next[c] != -1) {
                v = trie[v].next[c];
            }
            seen[v]++;
        }
    }
 
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
 
 
};
 
void Solution() {
    string s;
    cin >> s;
    int n;
    cin >> n;
    vector<string> v(n);
    cin >> v;
    AhoCorasick aho(v);
    aho.search(s);
    aho.dfs();
    for (int i = 0; i < n; i++) {
        cout << (ans[i] ? "YES" : "NO") << "\n";
    }
 
}
