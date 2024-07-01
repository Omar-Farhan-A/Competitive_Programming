struct FenwickTree{
0-based
private:
        vector<ll>tree;
        int N;
public:
        FenwickTree(int n){
            N=n;
            tree.resize(N+5);
        }
        void add(int idx,ll val){
            while (idx<=N){
                tree[idx]+=val;
                idx+=idx&-idx;
            }
        }
        ll query(int idx){
            ll ret=0;
            while (idx>0){
                ret+=tree[idx];
                idx-=idx&-idx;
            }
            return ret;
        }
        ll query(int l,int r){
            return query(r)- query(l-1);
        }

    };
