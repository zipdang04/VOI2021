#include <bits/stdc++.h>
using namespace std;
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
*/

typedef long long ll;
typedef double ld;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef pair<int, int> pii;
typedef pair<ld, ld> pdd;
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

const ld oo = 1e8;
const ld eps = 1;
ll n, d;
pdd range[MAX];
ll f[MAX];

bool cmp(pdd a, pdd b){
	if (b.fi - a.fi > eps) return true;
	if (a.fi - b.fi > eps) return false;
	return a.se - b.se > eps;
}


main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n >> d;
	FOR(ll, i, 1, n){
		ll x, y; cin >> x >> y;
		ld sq = sqrt(d * d - y * y);
		if (y > d){cout << -1; return 0;}

		range[i] = {x - sq, x + sq};
	}
	sort(range + 1, range + 1 + n);
	ld endPoint = oo;
	int ans = 1;
	FOR(ll, i, 1, n){
		pdd curr = range[i];
		if ((curr.fi - endPoint) > eps)
			ans++, endPoint = curr.se;

		endPoint = min(endPoint, curr.se);
	}
	cout << ans;
}