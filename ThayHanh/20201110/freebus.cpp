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
	ll node, len;
	Node() {node = len = 0;}
	Node(ll node, ll len) {this -> node = node, this -> len = len;}
};
typedef vector<Node> vg;
// */

#define MAX 1000001
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

ll n, m, k, s, t;
vg graph[MAX];
ll f[6][MAX];

void init(){
	FOR(int, i, 0, 5)
		FOR(int, j, 1, n) f[i][j] = INT64_MAX;
}

typedef pair<ll, pll> plpll;
priority_queue<plpll, vector<plpll>, greater<plpll>> pq;

void Dijkstra(){
	f[0][s] = 0; pq.push({0, {0, s}});
	while (!pq.empty()){
		plpll curr = pq.top(); pq.pop();
		ll node = curr.se.se, ticket = curr.se.fi, len = curr.fi;
		if (f[ticket][node] > len) continue;

		for (Node child: graph[node]){
			ll c1 = child.len + len, t1 = ticket;
			if (f[t1][child.node] > c1)
				f[t1][child.node] = c1, pq.push({c1, {t1, child.node}});
			
			if (ticket == k) continue;
			ll c2 = len, t2 = ticket + 1;
			if (f[t2][child.node] > c2)
				f[t2][child.node] = c2, pq.push({c2, {t2, child.node}});
		}
	}
}

main()
{
	#ifndef ONLINE_JUDGE
	freopen("freebus.inp", "r", stdin);
	freopen("freebus.out", "w", stdout);
	#endif
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m >> k >> s >> t;
	for (int i = 0; i < m; i++)
	{
		int u, v, w; cin >> u >> v >> w;
		graph[u].push_back(Node(v, w));
		graph[v].push_back(Node(u, w));
	}

	init();
	Dijkstra();


	ll answer = INT64_MAX;
	FOR(int, i, 0, k)
		answer = min(answer, f[i][t]);
	cout << answer;
}