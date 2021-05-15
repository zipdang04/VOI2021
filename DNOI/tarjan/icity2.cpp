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

#define testBit(n, bit) (((n) >> (bit)) & 1)
#define flipBit(n, bit) ((n) ^ (1ll << (bit)))
#define cntBit(n) __builtin_popcount(n)
#define cntBitll(n) __builtin_popcountll(n)
#define randomize mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count());

int n, m, s, t;
vi graph[MAX];

int par[MAX], lvl[MAX], visited[MAX];
void dfs(int node, int parent){
	lvl[node] = lvl[parent] + 1;
	par[node] = parent;

	visited[node] = true;
	for (int child: graph[node]){
		if (visited[child]) continue;
		dfs(child, node);
	}
}

int nList[MAX], len = 0;
bool flag[MAX];
void make(){
	len = lvl[t];
	int node = t;
	FORR(int, i, len, 1)
		flag[t] = true,
		nList[i] = t, t = par[t];
}

pii range[MAX]; int cnt = 0;
void browse(int node, int parent, int nodeLvl){
	visited[node] = true;
	for (int child: graph[node]){		
		int childLvl = lvl[child];
		if (childLvl < nodeLvl) continue;
		if (childLvl <= len && flag[child]){
			if (nodeLvl + 1 < childLvl)
				range[++cnt] = {nodeLvl + 1, childLvl - 1};
		} 
		else
			if (!visited[child])
			browse(child, node, nodeLvl);
	}
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m >> s >> t;
	FOR(int, _, 1, m){
		int u, v; cin >> u >> v;
		graph[u].push_back(v);
	}
	
	dfs(s, 0); make();
	memset(visited, false, sizeof(visited));
	FOR(int, i, 1, len - 1){
		int node = nList[i];
		browse(node, par[node], i);
	}
	sort(range + 1, range + 1 + cnt);

	int ans = len - 2;
	pii prev = range[1];
	FOR(int, i, 2, cnt){
		pii curr = range[i];
		if (curr.fi > prev.se){
			ans -= prev.se - prev.fi + 1;
			prev = curr;
		} else
			prev.se = max(prev.se, curr.se);
	}
	if (cnt)
	ans -= prev.se - prev.fi + 1;
	cout << ans;
}