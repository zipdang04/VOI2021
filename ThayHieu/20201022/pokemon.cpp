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

#define MAX 42
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

struct Point{ll x, y;};
Point operator + (Point a, Point b){return {a.x + b.x, a.y + b.y};}
Point operator - (Point a, Point b){return {a.x - b.x, a.y - b.y};}
ld abs(Point a){return sqrt(a.x * a.x + a.y * a.y);}

ll n, m;
Point poke[MAX][MAX];
ll cnt[MAX];
vector<vector<ld>> f[17];

const ld NaN = 1e18;
ld dp(ll type, ll pos, ll mask){
	if (mask == (1 << m) - 1) return 0;
	ld &ans = f[type][pos][mask];
	if (ans != NaN) return ans;

	FOR(ll, nextType, 0, m - 1){
		if (testBit(mask, nextType)) continue;
		ll newMask = flipBit(mask, nextType);
		FOR(ll, nextPos, 1, cnt[nextType]){
			ans = min(ans, dp(nextType, nextPos, newMask) + abs(poke[type][pos] - poke[nextType][nextPos]));
		}
	}
	return ans;
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m;
	FOR(int, i, 1, n){
		int x, y, t; cin >> x >> y >> t; t--;
		poke[t][++cnt[t]] = {x, y};
	}
	ld ans = NaN;
	FOR(int, type, 0, m - 1){
		int quantity = cnt[type];
		f[type] = vector<vector<ld>>(quantity + 1);
		FOR(int, i, 1, quantity)
			f[type][i] = vector<ld>((1 << m) - 1, NaN);
	}
	Point root = {0, 0};
	FOR(int, i, 0, m - 1){
		FOR(int, j, 1, cnt[i]){
			ans = min(ans, dp(i, j, 1 << i) + abs(root - poke[i][j]));
		}
	}
	cout << fixed << setprecision(3) << ans;
}