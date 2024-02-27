int n,LOG=20;
vector<vector<int>>S(N,vector<int>(LOG));
vector<int>a,bin_log(N);
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
            S[i][k]=min(S[i][k-1],S[i+(1<<(k-1))][k-1]);
        }
    }
}
int query(int L,int R){
    int k=bin_log[R-L+1];
    return min(S[L][k],S[R-(1<<k)+1][k]);
}
void burn() {
cin>>n;
int q;cin>>q;
a=vector<int>(n);
cin>>a;
build();
    while (q--){
        int l,r;cin>>l>>r;
        cout<<query(--l,--r)<<'\n';
    }

}
