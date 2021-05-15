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

umii bit[MAX];

int n;
pair<int, pii> res[MAX];

void update(int x, int y2){
	for (; x <= n; x += x & -x)
		for(int y = y2; y <= n; y += y & -y)
			bit[x][y]++;
}

int get(int x, int y2){
	int ans = 0;
	for (; x; x -= x & -x)
		for(int y = y2; y; y -= y & -y)
			ans += bit[x][y];
	return ans;
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	//input
	cin >> n;
	FOR(int, i, 1, n){
		int a, b, c; cin >> a >> b >> c;
		res[i] = {a, {n - b + 1, n - c + 1}};
		// cerr << a << '/' << n - b + 1 << '/' << n - c + 1 << '\n';
	}
	sort(res + 1, res + 1 + n, greater<pair<int, pii>>());
	//=========================
	ll ans = n * (n - 1) / 2;
	FOR(int, i, 1, n){
		pii curr = res[i].se;
		// cerr << curr.fi << ' ' << curr.se << '\n';
		ans -= get(curr.fi, curr.se);
		update(curr.fi, curr.se);
	}
	cout << ans << '\n';
}