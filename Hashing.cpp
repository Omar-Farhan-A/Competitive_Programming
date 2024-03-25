  vector<ll>pw1(N),pw2(N);
ll mod1=1e9+7,mod2=2e9+11,base1=31,base2=37,inv1,inv2;
ll fpow(ll x,ll y){
    ll prod = x,ans = 1;
    while(y){
        if(y&1)ans*=prod,ans%=MOD;
        prod*=prod;
        prod%=MOD;
        y>>=1;
    }
    return ans;
}
void init(){
inv1=fpow(base1,mod1-2);
inv2=fpow(base2,mod2-2);
pw1[0]=pw2[0]=1;
for(int i=1;i<N;i++){
    pw1[i]=(pw1[i-1]*base1)%mod1;
    pw2[i]=(pw2[i-1]*base2)%mod2;
}

}
struct Hashing{
        int len;
        ll h1,h2,v;
        deque<char>d;
        Hashing(){
            h1=h2=len=0;
        }
        void push_back(char c){
             v=c-'a'+1;
            h1=(h1*base1+v)%mod1;
            h2=(h2*base2+v)%mod2;
            d.push_back(c);
            len++;
        }
        void push_front(char c){
             v=c-'a'+1;
            h1=(pw1[len]*v+h1)%mod1;
            h2=(pw2[len]*v+h2)%mod2;
            d.push_front(c);
            len++;
        }
        void pop_back(){
            if(!len)return;
             v=d.back()-'a'+1;
            h1=(h1-v+mod1)%mod1;
            h1=(h1*inv1)%mod1;
            h2=(h2-v+mod2)%mod2;
            h2=(h2*inv2)%mod2;
            len--;
            d.pop_back();
        }
        void pop_front(){
            if(!len)return;
             v=d.front()-'a'+1;
            h1=((h1-v*pw1[len-1])%mod1+mod1)%mod1;
            h2=((h2-v*pw2[len-1])%mod2+mod2)%mod2;
            len--;
            d.pop_front();
        }
        pair<ll,ll>get(){
            return {h1,h2};
        }
    };
