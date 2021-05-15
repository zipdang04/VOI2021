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

#define MAX 10001
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

//====================================================================
int n, c, m;
vi graph[MAX];

int cock[MAX];
vi cockPos[MAX];
vector<pii> queryCock[MAX];

int ans[MAX];
//====================================================================
const int BIT = 10;
int par[MAX], lvl[MAX];
int rmq[BIT + 1][MAX];

void dfs(int node, int parent){
	par[node] = parent; 
	lvl[node] = lvl[parent] + 1;
	for (int child: graph[node])
		if (child != parent)
			dfs(child, node);
}

void buildRMQ(){
	FOR(int, i, 1, n)
		rmq[0][i] = par[i];
	FOR(int, bit, 1, BIT)
		FOR(int, i, 1, n)
			rmq[bit][i] = rmq[bit - 1][rmq[bit - 1][i]];
}

void init(){dfs(1, 0); buildRMQ();}

int jump(int node, int dist){
	FOR(int, bit, 0, BIT)
		if (testBit(dist, bit))
			node = rmq[bit][node];
	return node;
}

int dist(int u, int v){
	if (lvl[u] > lvl[v]) swap(u, v);
	
	int ans = lvl[v] - lvl[u];
	v = jump(v, ans);
	if (u == v) return ans;

	int tmp = 0;
	FORR(int, bit, BIT, 0)
		if (rmq[bit][u] != rmq[bit][v])
			tmp = flipBit(tmp, bit),
			u = rmq[bit][u], v = rmq[bit][v];
	tmp++; tmp <<= 1;
	return ans + tmp;
}
//====================================================================

void p1(int cockType){
	vi cockList = cockPos[cockType];
	for (pii i: queryCock[cockType]){
		int node = i.fi, pos = i.se;
		int mini = INT32_MAX;

		for (int currCock: cockList)
			mini = min(mini, dist(node, currCock));
		ans[pos] = mini;
	}
}

void p2(int cockType){
	int dist[MAX] = {};
	queue<int> q;
	for (int node: cockPos[cockType]){
		dist[node] = 1;
		q.push(node);
	}

	while (!q.empty()){
		int node = q.front(); q.pop();
		int curr = dist[node];

		for (int child: graph[node]){
			if (dist[child]) continue;
			dist[child] = curr + 1;
			q.push(child);
		}
	}

	for (pii i: queryCock[cockType])
		ans[i.se] = dist[i.fi] - 1;
}

void process(int cockType){
	// cerr << "cockType: " << cockType << ", size: " << cockPos[cockType].size() << '\n';
	if (cockPos[cockType].size() <= 100)
		p1(cockType);
	else
		p2(cockType);
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
	cin >> c;
	FOR(int, i, 1, n) {
		cin >> cock[i];
		cockPos[cock[i]].push_back(i);
	}
	cin >> m;
	FOR(int, i, 1, m){
		int x, y; cin >> x >> y;
		queryCock[y].push_back({x, i});
	}
	
	init();
	FOR(int, i, 1, c) process(i);
	FOR(int, i, 1, m) cout << ans[i] << '\n';
}