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

#define MAX 5001
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

ll n;
ll a[MAX];
vl graph[MAX];

ll f[MAX][MAX];
ll cnt[MAX];
void dfs(ll node, ll parent){
	if (node != 1 && graph[node].size() == 1){
		f[node][0] = a[node];
		f[node][1] = abs(a[node] - 1);
		cnt[node] = 1;
		return;
	}

	ll size = 0;
	for (ll child: graph[node]){
		if (child == parent) continue;
		dfs(child, node);
		
		ll s2 = cnt[child];
		ll save[size + s2 + 1] = {};
		FOR(int, i, 0, size + s2) save[i] = -1;
		FOR(ll, i, 0, size)
			FOR(ll, j, 0, s2){
				ll pos = i + j;
				if (save[pos] == -1)
					save[pos] = f[node][i] + f[child][j];
				else 
					save[pos] = min(save[pos], f[node][i] + f[child][j]);
			}
		size += s2;
		FOR(ll, i, 0, size) f[node][i] = save[i];
	}
	FOR(ll, i, 0, size){
		f[node][i] += abs(a[node] - i);
	}
	cnt[node] = size;
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	// #ifndef ONLINE_JUDGE
	// freopen("stree.inp", "r", stdin);
	// freopen("stree.out", "w", stdout);
	// #endif
	//input & init
	cin >> n; FOR(ll, i, 1, n) cin >> a[i];
	if (n == 1){
		cout << min(a[1], abs(a[1] - 1)); 
		return 0;
	}
	for (ll i = 1; i < n; i++)
	{
		ll u, v; cin >> u >> v;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	FOR(int, i, 1, n)
		FOR(int, j, 1, n)
			f[i][j] = -1;
	//=========================
	dfs(1, 1);
	ll answer = INT64_MAX;
	FOR(ll, i, 0, cnt[1]){
		answer = min(answer, f[1][i]);
	}
	cout << answer << '\n';
	
}