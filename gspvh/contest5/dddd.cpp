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

#define MAX 300005
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

struct PathCount{
	int mod;
	int arr[30] = {};

	PathCount(){
		memset(arr, 0, sizeof(arr));
		arr[0] = 1;
	}
	PathCount(int mod): mod(mod){
		memset(arr, 0, sizeof(arr));
		arr[0] = 1;
	}
};

PathCount shift(PathCount pc, int x){
	int mod = pc.mod;
	PathCount ans(mod);
	FOR(int, i, 0, mod - 1){
		ans.arr[(i + mod + x) % mod] = pc.arr[i];
	}
	return ans;
}
PathCount operator + (PathCount a, PathCount b){
	int mod = a.mod;
	PathCount ans(mod);
	FOR(int, i, 0, mod - 1)
		ans.arr[i] = a.arr[i] + b.arr[i];
	return ans;
}
PathCount operator - (PathCount a, PathCount b){
	int mod = a.mod;
	PathCount ans(mod);
	FOR(int, i, 0, mod - 1)
		ans.arr[i] = a.arr[i] - b.arr[i];
	return ans;
}

int n, p;
int par[MAX];
PathCount forw[MAX], bakw[MAX];
vi graph[MAX];
int ans[MAX];

void dfsF(int node, int parent){
	par[node] = parent;
	forw[node] = PathCount(p);
	for (int child: graph[node]){
		if (child == parent) continue;
		dfsF(child, node);

		FOR(int, i, 0, p - 1)
			forw[node].arr[(i + 1) % p] += forw[child].arr[i];
	}
}

void dfsB(int node, int parent){
	bakw[node] = PathCount(p); bakw[node].arr[0] = 0;
	if (parent != node){
		FOR(int, i, 0, p - 1)
			bakw[node].arr[(i + 1) % p] = bakw[parent].arr[i];
		PathCount curr = forw[parent] - shift(forw[node], 1);

		bakw[node] = bakw[node];
		FOR(int, i, 0, p - 1)
			forw[node].arr[(i + 1) % p] += curr.arr[i];
	}
	ans[node] = forw[node].arr[0]  + bakw[node].arr[0];

	for (int child: graph[node]){
		if (child == parent) continue;
		dfsB(child, node);
	}
}

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

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	// #ifndef ONLINE_JUDGE
	freopen("dddd.inp", "r", stdin);
	freopen("dddd.out", "w", stdout);
	// #endif
	// cin >> n >> p;
	scanf("%d%d", &n, &p);
	// fastscan(n), fastscan(p);
	FOR(int, _, 1, n - 1){
		int u, v; 
		scanf("%d%d", &u, &v);
		// cin >> u >> v;
		// fastscan(u), fastscan(v);
		graph[u].push_back(v);
		graph[v].push_back(u);
	}

	dfsF(1, 1);
	dfsB(1, 1);
	FOR(int, i, 1, n)
		cout << ans[i] << ' ';
}