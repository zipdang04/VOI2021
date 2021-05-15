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

int t;
int n;
int r[MAX], b[MAX];

pair<int, pii> edge[MAX]; int len = 0;
int dsu[MAX];

int findRoot(int node){
	if (dsu[node] < 0) return node;
	return dsu[node] = findRoot(dsu[node]);
}

bool join(int u, int v){
	u = findRoot(u), v = findRoot(v);
	if (u == v) return false;
	if (dsu[u] > dsu[v]) swap(u, v);
	dsu[u] += dsu[v], dsu[v] = u;
	return true;
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	#ifndef ONLINE_JUDGE
	freopen("cardgame.inp", "r", stdin);
	freopen("cardgame.out", "w", stdout);
	#endif
	cin >> t;
	FOR(int, _, 1, t){
		cin >> n; len = 0;
		FOR(int, i, 1, n) cin >> r[i];
		FOR(int, i, 1, n) cin >> b[i];
		FOR(int, i, 1, n) dsu[i] = -1;

		FOR(int, i, 1, n)
			FOR(int, j, i + 1, n)
				edge[++len] = {min(r[i] ^ b[j], r[j] ^ b[i]), {i, j}};
		
		sort(edge + 1, edge + 1 + len);
		ll answer = 0;
		FOR(int, _, 1, len){
			pair<int, pii> curr = edge[_];
			int u = curr.se.fi, v = curr.se.se;
			if (join(u, v)) answer += curr.fi;
		}
		cout << answer << '\n';
	}
}