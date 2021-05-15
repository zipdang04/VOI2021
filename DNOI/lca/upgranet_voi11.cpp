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

#define MAX 1000001
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

typedef pair<int, pii> Edge;

int n, m;
Edge edge[MAX];

vg graph[MAX];
int dsu[MAX];
int findRoot(int node){
	if (dsu[node] < 0) return node;
	return dsu[node] = findRoot(dsu[node]);
}
bool join(int u, int v){
	cerr << "join:" << u << '/' << v << ' ';
	u = findRoot(u), v = findRoot(v);
	cerr << u << '|' << v << '\n';
	if (u == v) return false;

	if (dsu[u] > dsu[v]) swap(u, v);
	dsu[u] += dsu[v], dsu[v] = u;
	return true;
}
void Kruskal(){
	FOR(int, i, 1, n) dsu[i] = -1;
	FOR(int, i, 1, m){
		Edge curr = edge[i];
		int w = curr.fi, u = curr.se.fi, v = curr.se.se;
		cerr <<  "currently:" <<  u << ' ' << v << '\n';
		if (!join(u, v)) continue;
		cerr << "okay\n";

		graph[u].push_back({v, w});
		graph[v].push_back({u, w});
	}
}

#define BIT 16
int upLen[MAX], lvl[MAX], par[MAX];
pii rmq[BIT + 1][MAX];

void dfs(int node, int parent){
	cerr << node << '/' << parent << '\n';
	lvl[node] = lvl[parent] + 1;
	par[node] = parent;
	
	for (Node child: graph[node]){
		if (child.node == parent) continue;
		
		upLen[child.node] = child.len;
		dfs(child.node, node);
	}
}

void buildRMQ(){
	FOR(int, bit, 0, BIT)
		if (bit == 0)
			FOR(int, i, 1, n)
				rmq[bit][i] = {par[i], upLen[i]};
		else
			FOR(int, i, 1, n){
				pii one = rmq[bit - 1][i], two = rmq[bit - 1][one.fi];
				two.se = min(two.se, one.se);
				rmq[bit][i] = two;
			}
	FOR(int, bit, 0, BIT){
		FOR(int, i, 1, n) cerr << rmq[bit][i].fi << '/' << rmq[bit][i].se << ' ';
		cerr << '\n';
	}
}

pii get(int node, int dist){
	pii ans = {0, INT32_MAX};
	FOR(int, bit, 0, BIT){
		if (testBit(node, bit)){
			pii curr = rmq[bit][node];
			node = curr.fi;
			ans = min(ans, curr.se);
		}
	}
	return ans;
}

int lca(int u, int v){
	if (lvl[u] > lvl[v]) swap(u, v);
	int diff = lvl[v] - lvl[u];
	
	int ans = get(v, diff), v = u;
	FORR(int, bit, BIT, 0){
		pii one = rmq[bit][u], two = rmq[bit][v];
		if (one.fi == two.fi) continue;
		u = one.fi, v = two.fi;
		ans = min(ans, min(one.se, two.se));

	}
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	//init
	cin >> n >> m;
	FOR(int, _, 1, m){
		int u, v, w; cin >> u >> v >> w;
		edge[_] = {w, {u, v}};
	}
	sort(edge + 1, edge + 1 + m, greater<Edge>());
	//=========================
	Kruskal();
	dfs(1, 0);
	buildRMQ();
	ll answer = 0;
	FOR(int, _, 1, m){
		Edge curr = edge[_];
		int w = curr.fi, u = curr.se.fi, v = curr.se.se;
		if (lvl[u] > lvl[v]) swap(u, v);
		int diff = lvl[v] - lvl[u];
		cerr << u << '/' << v << ' ' << lvl[u] << '/' << lvl[v] << ' ' << diff << ' ' << get(u, diff) << ' ' << w << '\n';

		answer += max(0, get(v, diff) - w);
	}
	cout << answer;
}