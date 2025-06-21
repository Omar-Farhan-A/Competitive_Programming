#define ll long long
#define isON(n, k) (((n) >> (k)) & 1)
#define sz(x) int(x.size())
#define ON(n, k) ((n) | (1 << (k)))
#define OFF(n, k) ((n) & ~(1 << (k)))
#define isON(n, k) (((n) >> (k)) & 1)
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/rope>
using namespace __gnu_cxx;
using namespace std;
using namespace __gnu_pbds;
template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <class T>
using ordered_multiset = tree<pair<T, T>, null_type, less<pair<T, T>>, rb_tree_tag, tree_order_statistics_node_update>;
constexpr int N = 1e5 + 7, OO = 0x3f3f3f3f, M = 1e6 + 6, MOD = 1e9 + 7;
constexpr ll LINF = 1LL << 62;
int dx[] = {1, 0, -1, 0, 1, 1, -1, -1};
int dy[] = {0, 1, 0, -1, 1, -1, 1, -1};
template <typename T = int>
using Pair = pair<T, T>;
template <typename T = int>
istream &operator>>(istream &in, vector<T> &v)
{
    for (auto &x : v)
        in >> x;
    return in;
}
template <typename T = int>
ostream &operator<<(ostream &out, const vector<T> &v)
{
    for (const T &x : v)
        out << x << ' ';
    return out;
}
long long rng(ll l = 0, ll r = INT64_MAX)
{
    static std::mt19937 gen(
        std::chrono::steady_clock::now().time_since_epoch().count());
    return std::uniform_int_distribution<long long>(l, r)(gen);
}
ios_base::sync_with_stdio(false), cin.tie(nullptr);

__builtin_popcount(n);
__builtin_ctz(n);
__builtin_clz
    __builtin_ctzll(n);
__builtin_clzll(n);
ll findXOR(ll n)
{
    ll mod = n % 4;
    if (mod == 0)
        return n;
    else if (mod == 1)
        return 1;
    else if (mod == 2)
        return n + 1;
    else if (mod == 3)
        return 0;
}
ll findXOR(ll l, ll r)
{
    return (findXOR(l - 1) ^ findXOR(r));
}

///  find all sub masks x from a given mask
int mask = 5;
for (int x = mask; x > 0; x = (x - 1) & mask)
{
}
/*
 *
 * a+b=(a^b)+2(a&b)=(a|b)+(a&b)
 *
 *
 */
__int128 read()
{
    __int128 x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
void print(__int128 x)
{
    if (x < 0)
    {
        putchar('-');
        x = -x;
    }
    if (x > 9)
        print(x / 10);
    putchar(x % 10 + '0');
}