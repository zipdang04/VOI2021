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

#define testBit(n, bit) ((n >> bit) & 1)
#define flipBit(n, bit) (n ^ (1ll << bit))
#define cntBit(n) __builtin_popcount(n)
#define cntBitll(n) __builtin_popcountll(n)
#define randomize mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count());

int n, m;
vi graph[MAX];
int par[MAX], size[MAX], lvl[MAX];
void dfs(int node, int parent){
	par[node] = parent; 
	size[node] = 1;
	lvl[node] = lvl[parent] + 1;
	for (int child: graph[node]){
		if (child == parent) continue;
		dfs(child, node);
		size[node] += size[child];
	}
}
#define BIT 16
int rmq[BIT + 1][MAX];
void init(){
	FOR(int, bit, 0, BIT)
		if (bit == 0) 
			FOR(int, i, 1, n) 
				rmq[bit][i] = par[i];
		else
			FOR(int, i, 1, n)
				rmq[bit][i] = rmq[bit - 1][rmq[bit - 1][i]];
}
int jump(int node, int dist){
	FOR(int, bit, 0, BIT){
		if (!dist) break;
		
		bool state = dist & 1; dist >>= 1;
		if (!state) continue;

		node = rmq[bit][node];
	}
	return node;
}

int lcaSame(int u, int v){
	if (u == v) return 0;

	int dist = 0;
	FORR(int, bit, BIT, 0){
		if (rmq[bit][u] == rmq[bit][v]) continue;
		else dist = flipBit(dist, bit), u = rmq[bit][u], v = rmq[bit][v];
	}
	
	return dist + 1;
}

int process(int u, int v){
	if (lvl[u] > lvl[v]) swap(u, v);
	int oldU = u, oldV = v;
	bool alot = true;
	int dist = lvl[v] - lvl[u];
	
	if (dist){
		alot = false;
		if (dist & 1) return 0;
		v = jump(v, dist);
	}
	int remain = lcaSame(u, v);

	if (alot) return size[1] - size[jump(u, remain - 1)] - size[jump(v, remain - 1)];
	int div2 = dist / 2 + remain;
	int realLca = jump(oldV, div2), prev = jump(oldV, div2 - 1);
	
	return size[realLca] - size[prev];
}


main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	FOR(int, _, 1, n - 1){
		int u, v; cin >> u >> v;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	dfs(1, 0); init();

	int m; cin >> m;
	FOR(int, _, 1, m){
		int x, y; cin >> x >> y;
		cout << process(x, y) << '\n';
	}
}