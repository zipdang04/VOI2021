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

map<int, bool> waiting[MAX];
map<int, bool> success[MAX];
map<int, bool> dsuValue[MAX];
int dsu[MAX] = {};
int ans[MAX] = {};
int n, m, k;

void init(){
	FOR(int, i, 1, n){
		dsu[i] = -1;
		dsuValue[i][i] = true;
	}
}

int findRoot(int u){
	if (dsu[u] < 0) return u;
	dsu[u] = findRoot(dsu[u]);
	return dsu[u];
}

void addCoop(int a, int b){
	int rootA = findRoot(a);
	int rootB = findRoot(b);
	if (rootA != rootB){
		waiting[a][b] = true;
		waiting[b][a] = true;
	} else {
		if (!success[a][b])
			success[a][b] = success[b][a] = true,
			ans[a]++, ans[b]++;
	}
}

void addEdge(int u, int v){
	int rootU = findRoot(u), rootV = findRoot(v);
	if (rootU == rootV) return;
	if (dsu[rootU] > dsu[rootV]) swap(rootU, rootV), swap(u, v);
	dsu[rootU] += dsu[rootV], dsu[rootV] = rootU;
	for (auto val: dsuValue[rootV]){
		int node = val.fi;
		dsuValue[rootU][node] = true;
		vector<int> save;
		for (auto ucv: waiting[node])
			save.push_back(ucv.fi);
		for (int child: save){
			if (findRoot(child) != rootU) continue;
			waiting[node].erase(child);
			waiting[child].erase(node);
			success[node][child] = success[child][node] = true;
			ans[node]++, ans[child]++;
		}
	}
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m >> k;
	init();
	FOR(int, i, 1, m){
		int u, v; cin >> u >> v;
		addCoop(u, v);
	}
	FOR(int, i, 1, k){
		int u, v; cin >> u >> v;
		addEdge(u, v);
	}
	int q; cin >> q;
	FOR(int, _, 1, q){
		char ask; cin >> ask;
		if (ask == '?'){
			int v; cin >> v;
			cout << ans[v] << '\n';
		}
		else if (ask == 'F'){
			int u, v; cin >> u >> v;
			addCoop(u, v);
		} else {
			int u, v; cin >> u >> v;
			addEdge(u, v);
		}
	}
}