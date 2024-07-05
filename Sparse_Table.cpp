struct SparseTable{
//0-based
        int LOG,n;
        vector<vector<int>>S;
        vector<int>bin_log;
        vector<int>a;
        SparseTable(int n,vector<int>&a){
            LOG=1;
            while (LOG<=n)LOG*=2;
            S=vector<vector<int>>(n,vector<int>(LOG));
            bin_log.resize(n+5);
            this->a=a;
            this->n=n;
            build();
        }
        void build(){
            int cur_log=0;
            for(int i=0;i<n;i++){
                S[i][0]=a[i];
                while ((1<<(cur_log+1))<=i+1){
                    cur_log++;
                }
                bin_log[i+1]=cur_log;
            }
            for(int k=1;k<LOG;k++){
                for(int i=0;i+(1<<(k))-1< n;i++){
                    S[i][k]=gcd(S[i][k-1],S[i+(1<<(k-1))][k-1]);
                }
            }
        }
    int query(int L,int R){
        int k=bin_log[R-L+1];
        return gcd(S[L][k],S[R-(1<<k)+1][k]);
    }
    };
