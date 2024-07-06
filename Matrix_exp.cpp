#define vvl vector<vector<ll>>
vvl IDN={{1,0},{0,1}};
vvl mulMat(vvl &a,vvl &b){
    int rows=int(a.size());
    int cols=int(b[0].size());
    vvl ret(rows,vector<ll>(cols));
    int K=int(b.size());
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            for(int k=0;k<K;k++){
                (ret[i][j]+=a[i][k] * b[k][j])%=MOD;
            }
        }
    }
    return ret;
}
vvl fastExp(vvl &x,ll n){
    vvl product=IDN;
    while(n > 0) {
        if(n % 2) {
            product = mulMat( product , x);
        }
        x = mulMat(x , x);
        n /= 2;
    }
    return product;
}
void burn() {
    ll n;cin>>n;
    vvl trans={{1,1},{1,0}};
    vvl fib={{1,0}};
    vvl v= fastExp(trans,n);
    vvl ans= mulMat(v,fib);
    cout<<ans[1][0];
}
