#define ON(n, k) ((n) | (1 << (k)))
#define OFF(n, k) ((n) & ~(1 << (k)))
#define isON(n, k) (((n) >> (k)) & 1)
void bitmasks(){
    int n=5;
    __builtin_popcount(n);
    // count number of ones in binary
    cout<<__builtin_ctz(n);
    // بتعد الأصفار الي قبل اول رقم من ع اليمين
    cout<<__builtin_clz(n);
    // بتعد الاصفار الزيادة الي ع الشمال بعد اخر واحد
    /* for ll
     * cout<<__builtin_ctzll(n);
     cout<<__builtin_clzll(n);

     */
    /*
     *
     * a+b=(a^b)+2(a&b)=(a|b)+(a&b)
     *
     *
     */
}
ll findXOR(ll n)
{
    ll mod = n % 4;
    if (mod == 0)return n;
    else if (mod == 1)return 1;
    else if (mod == 2)return n + 1;
    else if (mod == 3)return 0;
}
ll findXOR(ll l, ll r)
{
    return (findXOR(l - 1) ^findXOR(r));
}