ll fast_exp(ll x,ll y){
    ll prod = x,ans = 1;
    while(y){
        if(y&1)ans*=prod,ans%=MOD;
        prod*=prod;
        prod%=MOD;
        y>>=1;
    }
    return ans;
}

struct Mint {
    ll v;
    explicit operator ll() const { return v; }
    Mint(ll _v=0) {
        v=_v%MOD;
        if (v<0)v+=MOD;
    }
};
vector<Mint>fact(N),inv(N);
Mint &operator+=(Mint &a, Mint b) {
    if ((a.v += b.v) >= MOD) a.v -= MOD;
    return a;
}
Mint &operator-=(Mint &a, Mint b) {
    if ((a.v -= b.v) < 0) a.v += MOD;
    return a;
}
Mint operator+(Mint a, Mint b) { return a += b; }
Mint operator-(Mint a, Mint b) { return a -= b; }
Mint operator*(Mint a, Mint b) { return Mint(a.v * b.v); }
Mint &operator*=(Mint &a, Mint b) { return a = a * b;}
Mint &operator/=(Mint &a, Mint b) {
    return a*=inv[b.v];
}

void pre(){
    fact[0]=1;
    for(int i=1;i<N;i++){
        fact[i]=fact[i-1]*i;
    }
    inv[N-1]= fast_exp(fact[N-1].v,MOD-2);
    for(int i=N-2;i>=0;i--){
        inv[i]=inv[i+1]*(i+1);
    }
}
Mint nCr(int n,int r){
    if(r>n)return 0;
    Mint ret=fact[n];
    ret/=r;
    ret/=n-r;
    return ret;
}
