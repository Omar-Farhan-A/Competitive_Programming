//ax + by = g =gcd(a,b)
ll extended_euclid(ll a,ll b,ll &x,ll &y){
    if(b==0){
        x=1,y=0;
        return a;
    }
    //swap a,b and swap their x, y
    ll g= extended_euclid(b,a%b,y,x);
    //now x=previous y
    y-=(a/b)*x;
    return g;
}
int main() {
    ll a,b,c;cin>>a>>b>>c;
    // c must be divisible by gcd(a,b)
    ll x,y;
    ll g=extended_euclid(a,b,x,y);
    cout<<x*c/g<<' '<<y*c/g<<' ';
}