ll mfp(ll n, ll p, ll m){
    if(p == 0) return 1;
    ll sq = mfp(n, p / 2, m);
    sq = (sq * sq) % m;
    if(p & 1) sq = (sq * n) % m;
    return sq % m;
}