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

#define testBit(n, bit) ((n >> bit) & 1)
#define flipBit(n, bit) (n ^ (1ll << bit))
#define cntBit(n) __builtin_popcount(n)
#define cntBitll(n) __builtin_popcountll(n)
#define randomize mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count());

const ll oo = ll(1e18);

ll n;
ll f[1 << 20];
ll a[20][20];

ll dp(ll row, ll mask){
	if (f[mask] != oo) return f[mask];
	if (row == 0){
		ll col = 0;
		FOR(ll, i, 0, n -1)
			if (testBit(mask, i)){col = i; break;}
		
		f[mask] = a[row][col];
		return f[mask];
	}

	FOR(int, col, 0, n - 1){
		if (!testBit(mask, col)) continue;
		f[mask] = min(f[mask], dp(row - 1, flipBit(mask, col)) + a[row][col]);
	}
	return f[mask];
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	ll t; cin >> t;
	FOR(ll, _, 1, t){
		cin >> n;
		FOR(ll, i, 0, n - 1)
			FOR(ll, j, 0, n - 1) cin >> a[i][j];
		FOR(ll, i, 0, (1 << n) - 1) f[i] = oo;
		cout << dp(n - 1, (1 << n) - 1) << '\n';
	}
}