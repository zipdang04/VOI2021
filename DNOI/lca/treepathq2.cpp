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

#define MAX 200001
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

int n, k;
vi graph[MAX];
vi group[MAX];

const int BIT = 17;
int par[MAX], lvl[MAX];
int f[BIT + 1][MAX];

void dfs(int node, int parent){
	par[node] = parent; if (node != parent) lvl[node] = lvl[parent] + 1;
	for (int child: graph[node]){
		if (child == parent) continue;
		dfs(child, node);
	}
}

void init(){
	FOR(int, bit, 0, BIT)
		if (bit == 0)
			FOR(int, i, 1, n)
				f[bit][i] = par[i];
		else
			FOR(int, i, 1, n)
				f[bit][i] = f[bit - 1][f[bit - 1][i]];
}

int jump(int node, int dist){
	FOR(int, bit, 0, BIT){
		if (!dist) break;
		bool okay = dist & 1; dist >>= 1;
		if (!okay) continue;

		node = f[bit][node];
	}
	return node;
}

int dist(int u, int v){
	if (lvl[u] > lvl[v]) swap(u, v);
	int ans = lvl[v] - lvl[u];
	v = jump(v, ans);

	if (u != v){
		int sameDist = 0;
		FORR(int, bit, BIT, 0)
			if (f[bit][u] == f[bit][v]) continue;
			else sameDist = flipBit(sameDist, bit), u = f[bit][u], v = f[bit][v];
		sameDist++;
		ans += sameDist * 2;
	}

	return ans;
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n >> k;
	FOR(int, i, 1, n){
		int gr, par; cin >> gr >> par;
		group[gr].push_back(i);
		graph[par].push_back(i);
		graph[i].push_back(par);
	}
	dfs(0, 0);
	init();

	FOR(int, i, 1, k){
		int u = 1; int bestV = 1, best = 0;
		for (int v: group[i]){
			// cerr << v << '|';
			int currDist = dist(u, v);
			if (currDist > best)
				best = currDist, bestV = v;
		}
		// cerr << '\n';
		u = bestV, best = 0;
		// cerr << "choose: " << u << '\n';
		for (int v: group[i]){
			// cerr << v << "/" << dist(u, v) << '\n';
			best = max(best, dist(u, v));
		}
		cout << best << '\n';
	}
}