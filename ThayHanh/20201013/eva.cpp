#pragma GCC optimize("Ofast")  
#pragma GCC target("avx,avx2,fma") 
#include <bits/stdc++.h>
using namespace std;
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
*/

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef map<int, int> mii;
typedef unordered_map<int, int> umii;
typedef map<ll, ll> mll;
typedef unordered_map<ll, ll> umll;

template <typename T> inline void read(T &x)
{
    char c;
    bool neg = 0;
    while ((!isdigit(c = getchar())) && (c != '-'));
    if (c == '-')
    {
        neg = 1;
        c = getchar();
    }
    x = c - 48;
    while(isdigit(c = getchar())) x = x * 10 + c - 48;
    if (neg) x =- x;
}
template <typename T> inline void writep(T x)
{
    if (x > 9) writep(x / 10);
    putchar(x % 10 + 48);
}
template <typename T> inline void write(T x)
{
    if (x < 0)
    {
        putchar('-');
        x =- x;
    }
    writep(x);
}
template <typename T> inline void writeln(T x)
{
    write(x);
    putchar('\n');
}

/*
struct Node
{
	int node, len;
	Node() {node = len = 0;}
	Node(int node, int len) {this -> node = node, this -> len = len;}
};
typedef vector<Node> vg;
*/

#define MAX 100001
#define MOD 1000000007

#define fi first
#define se second
#define pf push_front
#define pb push_back

#define FOR(type, i, a, b) for(type i = (a); i <= (b); i++)
#define FORR(type, i, b, a) for(type i = (b); i >= (a); i--)

#define testBit(n, bit) ((n >> bit) & 1)
#define flipBit(n, bit) (n ^ (1ll << bit))
#define cntBit(n) __builtin_popcount(n)
#define cntBitll(n) __builtin_popcountll(n)
#define randomize mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count());

int n, k, m;
vi graph[MAX];
int ans[MAX];
int q[MAX], l = 1, r = 0;
main()
{
//	// #ifndef ONLINE_JUDGE
	freopen("eva.inp", "r", stdin);
	freopen("eva.out", "w", stdout);
	// #endif
	ios_base::sync_with_stdio(0); cin.tie(0);
	read(n); read(k);
	FOR(int, i, 1, k){
		int num; read(num);
		q[++r] = num; ans[num] = 1;	
	}
	read(m);
	for (int i = 0; i < m; i++)
	{
		int u, v; read(u); read(v);
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	while (l <= r){
		int room = q[l++];
		for (int child: graph[room]){
			if (ans[child]) continue;
			ans[child] = ans[room] + 1;
			q[++r] = child;
		}
	}
	FOR(int, i, 1, n) cout << --ans[i] << ' ';
}
    