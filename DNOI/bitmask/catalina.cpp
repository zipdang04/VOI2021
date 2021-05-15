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

// /*
struct Node
{
	int node, len;
	Node() {node = len = 0;}
	Node(int node, int len) {this -> node = node, this -> len = len;}
};
typedef vector<Node> vg;
// */

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

ll n, m, k;
ll bank[21];
vg graph[MAX];
ll cost[21][21];
ll f[MAX];
ll tsp[18][1 << 18];

#define ass(node, val) f[node] = val, pq.push({val, node})
void Dijkstra(ll root){
	fill(f, f + n + 1, INT64_MAX);
	priority_queue<pll, vector<pll>, greater<pll>> pq;
	ass(root, 0);
	while (!pq.empty()){
		pll curr = pq.top(); pq.pop();
		// cerr << curr.se << ':' << curr.fi << '\n';
		ll len = curr.fi, node = curr.se;
		if (len != f[node]) continue;

		for (Node child: graph[node]){
			ll nowLen = len + child.len;
			// cerr << "///" << child.node << ' ' << child.len << "=> " << nowLen << "&" << f[child.node] << '\n';
			if (nowLen < f[child.node])
				ass(child.node, nowLen);
		}
	}
}

ll dp(ll node, ll state){
	// cerr << node << ' ' << bitset<3>(state) << '\n';
	if (tsp[node][state] != INT64_MAX) return tsp[node][state];
	if (cntBitll(state) == 1){
		tsp[node][state] = 0; return 0;
	}
	
	ll newState = flipBit(state, node);
	FOR(ll, i, 0, k - 1){
		if (i == node) continue;
		if (!testBit(newState, i)) continue;

		tsp[node][state] = min(tsp[node][state], dp(i, newState) + cost[node][i]);
	}
	return tsp[node][state];
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	//input
	cin >> n >> m >> k;
	FOR(ll, i, 0, k - 1) cin >> bank[i];
	for (ll i = 0; i < m; i++)
	{
		ll u, v, w; cin >> u >> v >> w;
		graph[u].push_back(Node(v, w));
		graph[v].push_back(Node(u, w));
	}
	//=========================
	//build matrix
	FOR(ll, i, 0, k - 1){
		Dijkstra(bank[i]);
		FOR(ll, j, 0, k - 1){
			cost[i][j] = f[bank[j]];
		}
	}
	//=========================
	//TSP
	FOR(ll, i, 0, k - 1)
		FOR(ll, j, 0, (1 << k) - 1)
			tsp[i][j] = INT64_MAX;
	ll ans = INT64_MAX;
	FOR(ll, i, 0, k - 1)
		ans = min(ans, dp(i, (1 << k) - 1));
	//=========================
	cout << ans << '\n';
}