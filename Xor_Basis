template<typename T = int>
class Basis {
    vector<T> basis;
public:
    int sz, bits;
    Basis(int b = 32) {
        sz = 0;
        bits = b;
        basis.resize(bits);
    }

    void insert(int mask) {
        for (int i = bits - 1; i >= 0; i--) {
            if ((mask >> i) & 1) {
                if (!basis[i]) {
                    basis[i] = mask;
                    sz++;
                    return;
                }
                mask ^= basis[i];
            }
        }
    }

    bool check_mask(int mask) {
        for (int i = bits - 1; i >= 0; i--) {
            if ((mask >> i) & 1) {
                if (!basis[i]) {
                    return false;
                }
                mask ^= basis[i];
            }
        }
        return true;
    }
};
