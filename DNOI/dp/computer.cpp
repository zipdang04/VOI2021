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

#define MAX 1001
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

ll a, x, b, y, n;

pii f[MAX][MAX];

bool check(int thres){
	cerr << "ask: " << thres << '\n';
	FOR(int, i, 0, x)
		FOR(int, j, 0, y)
			f[i][j] = {0, 0};
	FOR(int, i, 0, x)
		FOR(int, j, 0, y){
			if (i == 0 && j == 0) continue;
			if (i > 0){
				pii prev = f[i - 1][j];
				prev.se += a;
				if (prev.se >= thres)
					f[i][j] = max(f[i][j], {prev.fi + 1, 0});
				else 
					f[i][j] = max(f[i][j], prev);
			}
			if (j > 0){
				pii prev = f[i][j - 1];
				prev.se += b;
				if (prev.se >= thres)
					f[i][j] = max(f[i][j], {prev.fi + 1, 0});
				else 
					f[i][j] = max(f[i][j], prev);
			}
		}
	return f[x][y].fi >= n;
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	// cin >> a >> x >> b >> y >> n;
	cin >> x >> a >> y >> b >> n;
	
	ll l = 1, r = 1000000, ans = 0;
	while (l <= r){
		ll mid = (l + r) >> 1;
		if (check(mid)) ans = mid, l = mid + 1, ans = mid;
		else r = mid - 1;
	}
	cout << ans;
}