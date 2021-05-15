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

#define MAX 300001
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

struct Edge{
	ll len, idx, u, v;
};
bool operator < (Edge a, Edge b){
	return (a.len != b.len) ? (a.len < b.len) : (a.idx < b.idx);
}
bool operator > (Edge a, Edge b){
	return (a.len != b.len) ? (a.len > b.len) : (a.idx > b.idx);
}

int theta, n, k, m, p;
bool haveMoji[MAX] = {};
Edge appear[MAX], plan[MAX];
int dsu[MAX];

void input(){
	cin >> theta >> n >> k;
	FOR(int, i, 1, n) dsu[i] = -1;
	FOR(int, i, 1, k) {
		int pos; cin >> pos;
		haveMoji[pos] = true;
	}
	cin >> m;
	FOR(int, i, 1, m){
		int u, v, l; cin >> u >> v >> l;
		appear[i] = {l, i, u, v};
	}
	cin >> p;
	FOR(int, i, 1, p){
		int u, v, l; cin >> u >> v >> l;
		plan[i] = {l, i, u, v};
	}
}

int findRoot(int node){
	if (dsu[node] < 0) return node;
	return dsu[node] = findRoot(dsu[node]);
}

bool join(int u, int v){
	u = findRoot(u), v = findRoot(v);
	if (u == v) return false;
	if (haveMoji[u] && haveMoji[v]) return false;

	if (dsu[u] > dsu[v]) swap(u, v);
	dsu[u] += dsu[v], haveMoji[u] |= haveMoji[v];
	dsu[v] = u;
	return true;
}

vi ansA, ansP;
ll ans = 0;

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	freopen("moji.inp", "r", stdin);
	freopen("moji.out", "w", stdout);
	
	input();
	sort(appear + 1, appear + 1 + m, greater<Edge>());
	sort(plan + 1, plan + 1 + p);
	
	FOR(int, i, 1, m){
		Edge curr = appear[i];
		if (!join(curr.u, curr.v))
			ans += curr.len, ansA.push_back(curr.idx);
	}
	FOR(int, i, 1, p){
		Edge curr = plan[i];
		if (join(curr.u, curr.v))
			ans += curr.len, ansP.push_back(curr.idx);
	}
	
	sort(ansA.begin(), ansA.end());
	sort(ansP.begin(), ansP.end());

	cout << ans << '\n';
	cout << ansA.size() << '\n';
	for (int i: ansA) cout << i << ' '; cout << '\n';
	cout << ansP.size() << '\n';
	for (int i: ansP) cout << i << ' '; cout << '\n';
}