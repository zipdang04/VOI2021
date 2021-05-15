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

#define testBit(n, bit) (((n) >> (bit)) & 1)
#define flipBit(n, bit) ((n) ^ (1ll << (bit)))
#define cntBit(n) __builtin_popcount(n)
#define cntBitll(n) __builtin_popcountll(n)
#define randomize mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count());

struct Data{ll len, cake;};
Data operator + (Data a, Data b) {
	return {a.len + b.len, a.cake + b.cake};
}
bool operator < (Data a, Data b){
	return (a.len < b.len) ? true : (
		(a.len == b.len && a.cake > b.cake) ? true : false
	);
}
bool operator > (Data a, Data b){
	return (a.len < b.len) ? true : (
		(a.len == b.len && a.cake > b.cake) ? true : false
	);
}
bool operator == (Data a, Data b){
	return (a.len == b.len) && (a.cake == b.cake);
}
bool operator != (Data a, Data b){
	return (a.len != b.len) && (a.cake != b.cake);
}
const ll oo = 1e18;
const Data NaN = {oo, oo};

ll n, m;
ll p[MAX];
vg graph[MAX];

Data cost[MAX];
typedef pair<Data, int> PQDat;
priority_queue<PQDat, vector<PQDat>, greater<PQDat>> pq;

main()
{
	freopen("quanho.inp", "r", stdin);
	freopen("quanho.out", "w", stdout);
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n; FOR(int, i, 1, n) cin >> p[i];
	cin >> m; FOR(int, i, 1, m){
		int u, v, c; cin >> u >> v >> c;
		graph[u].push_back({v, c});
		graph[v].push_back({u, c});
	}

	FOR(int, i, 1, n) cost[i] = NaN;
	cost[1] = {0, p[1]}; pq.push({cost[1], 1});
	while (!pq.empty()){
		PQDat curr = pq.top(); pq.pop();
		Data currDat = curr.fi; int currNode = curr.se;
		if (cost[currNode] != currDat) continue;

		for (Node child: graph[currNode]){
			Data nowDat = {child.len, p[child.node]};
			nowDat = nowDat + currDat;

			if (nowDat < cost[child.node])
				cost[child.node] = nowDat,
				pq.push({nowDat, child.node});
		}
	}
	if (cost[n].len == oo) cout << "impossible";
	else cout << cost[n].len << ' ' << cost[n].cake;
}