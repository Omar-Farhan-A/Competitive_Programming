/*
 *Use when inserting multiple strings into the SAME suffix automaton.
*Before inserting each new string:
 *      last = 0;
 *      stringIdx++;
 *   distinct[u] ---> number of DIFFERENT input strings that contain
 *           any/every substring represented by state u
 * st[u].id --> last stringIdx in which state u was already counted
     Used to avoid counting the same state more than once
 * for the same string.
 */
struct SAM {
    struct State {
        int len = 0, link = 0, id = -1;
        map<int, int> nxt;
    };

    vector<State> st;
    vector<int> cnt, distinct;
    int last = 0, sz = 0, stringIdx = 0;

    SAM(int n) {
        st.assign(2 * n, {});
        st[0].link = -1;
        cnt.resize(2 * n);
        distinct.resize(2 * n);
    }

    void onlineCounting(int node) {
        while (~node && st[node].id != stringIdx) {
            st[node].id = stringIdx;
            distinct[node]++;
            node = st[node].link;
        }
    }

    void insert(int c) {
        if (st[last].nxt.count(c) && st[st[last].nxt[c]].len == st[last].len + 1) {
            last = st[last].nxt[c];
            onlineCounting(last);
            return;
        }
        int cur = ++sz;
        st[cur].len = st[last].len + 1;
        int p = last;
        while (~p && st[p].nxt.count(c) == 0) {
            st[p].nxt[c] = cur;
            p = st[p].link;
        }
        if (p == -1) {
            st[cur].link = 0;
        } else {
            int q = st[p].nxt[c];
            if (st[q].len == st[p].len + 1) {
                st[cur].link = q;
            } else {
                int clone = ++sz;
                st[clone].len = st[p].len + 1;
                st[clone].nxt = st[q].nxt;
                st[clone].link = st[q].link;
                st[clone].id = st[q].id;
                distinct[clone] = distinct[q];
                while (~p && st[p].nxt.count(c) && st[p].nxt[c] == q) {
                    st[p].nxt[c] = clone;
                    p = st[p].link;
                }
                st[cur].link = clone;
                st[q].link = clone;
            }
        }
        onlineCounting(cur);
        last = cur;
    }
};
