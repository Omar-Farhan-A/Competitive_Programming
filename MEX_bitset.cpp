class MEX {
private:
    bitset<N + 1> mex;
    vector<int> cnt;
public:
    MEX() {
        mex.set();
        cnt.assign(N + 1, 0);
    }

    void add(int x) {
        if (++cnt[x] == 1) {
            mex[x] = false;
        }
    }

    void remove(int x) {
        if (--cnt[x] == 0) {
            mex[x] = true;
        }
    }

    int get_mex() {
        return mex._Find_first();
    }
};
