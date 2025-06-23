template <int N = (int)2e5>
class MEX {
private:
    int SQ;
    vector<int> block, freq;
 
public:
    MEX() {
        SQ = sqrt(N + 1) + 1;
        freq.assign(N + 1, 0);
        block.assign(SQ, 0);
    }
 
    void add(int x) {
        if (!freq[x]) {
            block[x / SQ]++;
        }
        freq[x]++;
    }
 
    void remove(int x) {
        freq[x]--;
        if (!freq[x]) {
            block[x / SQ]--;
        }
    }
 
    int get_mex() {
        for (int i = 0; i < SQ; ++i) {
            if (block[i] != SQ) {
                for (int j = i * SQ; j < i * SQ + SQ; ++j) {
                    if (!freq[j]) {
                        return j;
                    }
                }
            }
        }
    }
};
