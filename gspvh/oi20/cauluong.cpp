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
	int node, idx, len;
	Node() {node = idx =  len = 0;}
	Node(int node, int idx, int len) {
		this -> node = node, 
		this -> idx = idx,
		this -> len = len;}
};
typedef vector<Node> vg;
// */

#define MAX 1500
#define MOD 998244353

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

int subtask, n, m;
vg graph[MAX];
int ans[MAX];

struct Calculate{
	int root;

	int dist[MAX] = {};
	void Dijkstra(){
		FOR(int, i, 1, n)
			dist[i] = INT32_MAX;
		priority_queue<pii, vector<pii>, greater<pii>> pq;
		
		dist[root] = 0; pq.push({0, root});
		while (!pq.empty()){
			pii curr = pq.top(); pq.pop();
			int node = curr.se, len = curr.fi;
			if (len != dist[node]) continue;

			for (Node child: graph[node]){
				int newLen = dist[node] + child.len;
				if (dist[child.node] > newLen)
					dist[child.node] = newLen,
					pq.push({newLen, child.node});
			}
		}
	}

	vg forw[MAX], bakw[MAX];
	void buildDAG(){
		FOR(int, node, 1, n){
			for (Node child: graph[node]){
				if (dist[node] + child.len == dist[child.node]){
					forw[node].push_back(child),
					bakw[child.node].push_back({node, child.idx, child.len});
				}
			}
		}
	}

	int f[MAX], b[MAX];
	int dfsF(int node){
		if (f[node] != -1) return f[node];
		f[node] = 1;
		for (Node child: forw[node])
			f[node] += dfsF(child.node),
			f[node] %= MOD;
		return f[node];
	}
	int dfsB(int node){
		if (b[node] != -1) return b[node];
		if (node == root){
			b[node] = 1; return 1;
		}

		b[node] = 0;
		for (Node child: bakw[node])
			b[node] += dfsB(child.node),
			b[node] %= MOD;
		return b[node];
	}

	Calculate(int root): root(root){
		Dijkstra();
		buildDAG();

		FOR(int, i, 1, n) f[i] = b[i] = -1;
		FOR(int, i, 1, n) dfsF(i), dfsB(i);
		FOR(int, node, 1, n)
			for (Node child: forw[node]){
				ans[child.idx] += ll(f[child.node]) * b[node] % MOD,
				ans[child.idx] %= MOD;
			}
	}
};

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	// #ifndef ONLINE_JUDGE
	freopen("cauluong.inp", "r", stdin);
	freopen("cauluong.out", "w", stdout);
	// #endif
	cin >> subtask >> n >> m;
	FOR(int, _, 1, m){
		int u, v, c; cin >> u >> v >> c;
		graph[u].push_back({v, _, c});
	}
	FOR(int, i, 1, n) {
		Calculate cal = Calculate(i);
	}
	FOR(int, i, 1, m) cout << ans[i] << '\n';
}