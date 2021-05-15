#include <bits/stdc++.h>
using namespace std;
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<ll, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
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

#define MAX 101
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

ll n, m;
ll a[MAX];
bool mat[MAX][MAX];

#define test(a, b, c, d) (mat[a][b] && mat[b][c] && mat[c][d])

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m; FOR(ll, i, 1, n) cin >> a[i];
	FOR(ll, i, 1, m){
		ll u, v; cin >> u >> v;
		mat[u][v] = mat[v][u] = true;
	}
	ll ans = -1;
	FOR(ll, i, 1, n)
		FOR(ll, j, i + 1, n)
			FOR(ll, k, j + 1, n)
				FOR(ll, l, k + 1, n){
					
					bool okay = false;
					if (test(i, j, k, l)) okay = true;
					if (test(i, j, l, k)) okay = true;
					if (test(i, k, j, l)) okay = true;
					if (test(i, k, l, j)) okay = true;
					if (test(i, l, j, k)) okay = true;
					if (test(i, l, k, j)) okay = true;
					
					if (test(j, i, k, l)) okay = true;
					if (test(j, i, l, k)) okay = true;
					if (test(j, k, i, l)) okay = true;
					if (test(j, k, l, i)) okay = true;
					if (test(j, l, i, k)) okay = true;
					if (test(j, l, k, i)) okay = true;
					
					if (test(k, j, i, l)) okay = true;
					if (test(k, j, l, i)) okay = true;
					if (test(k, i, j, l)) okay = true;
					if (test(k, i, l, j)) okay = true;
					if (test(k, l, j, i)) okay = true;
					if (test(k, l, i, j)) okay = true;
					
					if (test(l, j, k, i)) okay = true;
					if (test(l, j, i, k)) okay = true;
					if (test(l, k, j, i)) okay = true;
					if (test(l, k, i, j)) okay = true;
					if (test(l, i, j, k)) okay = true;
					if (test(l, i, k, j)) okay = true;
					if (!okay) continue;
					ans = max(ans, a[i] + a[j] + a[k] + a[l]);
					// cerr << i << ' ' << j << ' ' << k << ' ' << l << ' ' << a[i] + a[j] + a[k] + a[l] << '\n';
				}
	cout << ans;
}