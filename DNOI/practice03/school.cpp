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

const int oo = 1e9;

int n, m, k;
vg gA[MAX], gB[MAX], revA[MAX], revB[MAX];
int wlkLen[MAX];
int staLen[MAX];
int carLen[MAX];

void init(int *arr){
	FOR(int, i, 1, n)
		arr[i] = oo;
}

void Dijkstra(int root, int *f, vg *graph){
	init(f);
	priority_queue<pii, vector<pii>, greater<pii>> pq;
	f[root] = 0; pq.push({0, root});
	while (!pq.empty()){
		pii curr = pq.top(); pq.pop();
		int node = curr.se, len = curr.fi;
		if (len != f[node]) continue;

		for (Node child: graph[node]){
			int newLen = len + child.len;
			if (newLen < f[child.node])
				f[child.node] = newLen, pq.push({newLen, child.node});
		}
	}
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m >> k; 
	FOR(int, _, 1, m){
		int u, v, a, b; cin >> u >> v >> a >> b;
		gA[u].push_back({v, a});
		revA[v].push_back({u, a});
		gB[u].push_back({v, b});
		revB[v].push_back({u, b});
	}
	Dijkstra(k, wlkLen, revA);
	Dijkstra(1, staLen, gB);
	Dijkstra(n, carLen, revB);

	int ans = oo;
	FOR(int, trans, 1, n){
		int sta = staLen[trans], car = carLen[trans], wlk = wlkLen[trans];
		if (sta + wlk > 59) continue;
		ans = min(ans, sta + car);
	}
	cout << ans;
}