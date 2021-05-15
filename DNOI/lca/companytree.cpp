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

struct Query {int t, x, y;};
struct Doc
{
	int node, len;
	Doc() {node = len = 0;}
	Doc(int node, int len) {this -> node = node, this -> len = len;}
};

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

int n, m, k;
Query q[MAX];

const int BIT = 16;
int par[MAX], lvl[MAX];
int rmq[BIT + 1][MAX];
Doc doc[MAX];

int dp(int node){
	if (lvl[node]) return lvl[node];
	if (par[node] == 0){
		lvl[node] = 1;
		return 1;
	}
	lvl[node] = dp(par[node]) + 1;
}

void init(){
	FOR(int, bit, 0, BIT)
		if (bit == 0)
			FOR(int, i, 1, n)
				rmq[bit][i] = par[i];
		else
			FOR(int, i, 1, n)
				rmq[bit][i] = rmq[bit - 1][rmq[bit - 1][i]];
}

int jump(int node, int len){
	FOR(int, bit, 0, BIT){
		if (!len) break;
		bool okay = len & 1; len >>= 1;
		if (!okay) continue;

		node = rmq[bit][node];
		if (node == 0) return 0;
	}
	return node;
}

int boss[MAX];
int dsu[MAX];

int findRoot(int node){
	if (dsu[node] < 0) return node;
	return dsu[node] = findRoot(dsu[node]);
}

int join(int u, int v){
	if (dsu[u] > dsu[v]) swap(u, v);
	dsu[u] += dsu[v], dsu[v] = u;
	return u;
}

int addEdge(int node, int parent){
	node = findRoot(node), parent = findRoot(parent);
	boss[join(node, parent)] = boss[parent];
}

int getLen(int node){
	int currBoss = boss[findRoot(node)];
	int lvlNode = lvl[node], lvlBoss = lvl[currBoss];
	return lvlNode - lvlBoss;
}

bool check(int x, int posDoc){
	int node = doc[posDoc].node, maxDist = doc[posDoc].len;
	if (lvl[node] < lvl[x]) return false;
	
	int diffLvl = lvl[node] - lvl[x];
	if (diffLvl > maxDist) return false;

	node = jump(node, diffLvl);
	return node == x;
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m;
	FOR(int, i, 1, m) {
		int t, x, y; cin >> t >> x; if(t != 2) cin >> y;
		q[i] = {t, x, y};

		if (t == 1) par[x] = y;
	}
	
	FOR(int, i, 1, n) dp(i); 
	init();

	FOR(int, i, 1, n) dsu[i] = -1, boss[i] = i;
	FOR(int, _, 1, m){
		Query currQ = q[_];
		int t = currQ.t, x = currQ.x, y = currQ.y;
		if (t == 1)
			addEdge(x, y);
		else if (t == 2)
			doc[++k] = {x, getLen(x)};
		else 
			cout << (check(x, y) ? "YES\n" : "NO\n");
	}
}