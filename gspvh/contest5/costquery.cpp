
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

/*
struct Node
{
	int node, len;
	Node() {node = len = 0;}
	Node(int node, int len) {this -> node = node, this -> len = len;}
};
typedef vector<Node> vg;
*/

#define MAX 100005
#define MOD 1000000007

#define fi first
#define se second
#define pf push_front
#define pb push_back

#define FOR(type, i, a, b) for(type i = (a); i <= (b); i++)
#define FORR(type, i, b, a) for(type i = (b); i >= (a); i--)

#define testBit(n, bit) (((n) >> (bit)) & 1)
#define flipBit(n, bit) ((n) ^ (1ll << (bit)))
#define cntBit(n) __builtin_popcount(n)
#define cntBitll(n) __builtin_popcountll(n)
#define randomize mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count());

int n, q;
int value[MAX];
ll c[MAX], cost = 0;
int len = 0;

int dsu[MAX];
pair<int, pii> edge[MAX];

void fastscan(int &x)
{
	bool neg=false;
	register int c;
	x =0;
	c=getchar();
	if(c=='-')
	{
		neg = true;
		c=getchar();
	}
	for(;(c>47 && c<58);c=getchar())
		x = (x<<1) + (x<<3) +c -48;
	if(neg)
		x *=-1;
}

int findRoot(int u){
	return (dsu[u] < 0) ? u : (dsu[u] = findRoot(dsu[u]));
}

void join(int u, int v){
	u = findRoot(u), v = findRoot(v);
	ll szU = -dsu[u], szV = -dsu[v];
	cost -= ((szU * (szU - 1)) >> 1) + ((szV * (szV - 1)) >> 1);
	
	if (dsu[u] > dsu[v]) swap(u, v);
	dsu[u] += dsu[v], dsu[v] = u;
	szU = -dsu[u];
	cost += (szU * (szU - 1)) >> 1;
}

ll find(int num){
	int left = 1, right = len, ans = 0;
	while (left <= right){
		int mid = (left + right) >> 1;
		if (value[mid] <= num)
			ans = mid, left = mid + 1;
		else right = mid - 1;
	}
	return c[ans];
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	#ifndef HIEU
	freopen("costquery.inp", "r", stdin);
	freopen("costquery.out", "w", stdout);
	#endif
	// cin >> n >> q; 
	fastscan(n), fastscan(q);
	FOR(int, i, 1, n) dsu[i] = -1;
	FOR(int, i, 1, n - 1){
		int u, v, w; 
		// cin >> u >> v >> w;
		fastscan(u), fastscan(v), fastscan(w);
		edge[i] = {w, {u, v}};
	}
	sort(edge + 1, edge + n);	
	value[++len] = 0; c[len] = 0;
	FOR(int, i, 1, n - 1){
		pair<int, pii> curr = edge[i];
		int u = curr.se.fi, v = curr.se.se, w = curr.fi;
		join(u, v);

		if (w == value[len]) c[len] = cost;
		else{
			value[++len] = w; c[len] = cost;
		}
	}
	value[++len] = 1e9 + 7; c[len] = cost;

	FOR(int, _, 1, q){
		int l, r; 
		fastscan(l), fastscan(r);
		// cin >> l >> r;
		cout << find(r) - find(l - 1) << ' ';
	}
}