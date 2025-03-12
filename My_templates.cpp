#define ll long long
#define isON(n, k) (((n) >> (k)) & 1)
#define sz(x) int(x.size())
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/rope>
using namespace __gnu_cxx;
using namespace std;
using namespace __gnu_pbds;
template<class T> using ordered_set = tree<T, null_type , less<T> , rb_tree_tag , tree_order_statistics_node_update> ;
template<class T> using ordered_multiset= tree<pair<T, T>, null_type, less<pair<T, T>>, rb_tree_tag, tree_order_statistics_node_update>;
constexpr int N=1e5+7,OO=0x3f3f3f3f,M=1e6+6,MOD=1e9+7;
constexpr ll LINF = 1LL << 62;
int dx[]={1,0, -1,0,1,1,-1,-1};
int dy[]={0,1, 0,-1,1,-1,1,-1};
template < typename T = int > using Pair = pair < T, T >;
template < typename T = int > istream& operator >> (istream &in, vector < T > &v) {
    for (auto &x: v) in >> x;
    return in;
}
template < typename T = int > ostream& operator << (ostream &out, const vector < T > &v) {
    for (const T &x: v) out << x<<' ';
    return out;
}
long long rng(ll l = 0, ll r = INT64_MAX) {
    static std::mt19937 gen(
            std::chrono::steady_clock::now().time_since_epoch().count());
    return std::uniform_int_distribution<long long>(l, r)(gen);
}
   ios_base::sync_with_stdio(false), cin.tie(nullptr);
