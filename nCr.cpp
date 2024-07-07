ll nCr(ll n, ll r){
    if(n<r)return 0;
    ll ans = 1;
    ll div = 2; // r!
    for (ll i = (n-r) + 1; i <= n; i++){
        ans = ans * i;
        if(ans%div==0&&div<=r){
            ans /= div;
            div++;
        }
    }

    return ans;
}
