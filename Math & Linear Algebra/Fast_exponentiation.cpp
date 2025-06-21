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
