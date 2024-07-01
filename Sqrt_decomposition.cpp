struct Sqrt_decomposition {
        // 0-based
private:
        vector<ll>v,b;
        int SQ,n;
public:
        Sqrt_decomposition(int n,vector<ll>&a){
            v=a;
            SQ=int(sqrt(n+.0))+1;
            b=vector<ll>(SQ,0);
            this->n=n;
            build();
        }
        void build(){
            for(int i=0;i<n;i++){
                b[i/SQ]+=v[i];
            }
        }
        ll Query(int l,int r){
            ll ret=0;
            for(int i=l;i<=r;){
                if(i%SQ==0&&i+SQ-1<=r){
                    ret+=b[i/SQ];
                    i+=SQ;
                }
                else {
                    ret+=v[i];
                    i++;
                }
            }
            return ret;
        }
        void update(int idx,ll val){
            b[idx/SQ]-=v[idx];
            v[idx]=val;
            b[idx/SQ]+=v[idx];
        }
    };
