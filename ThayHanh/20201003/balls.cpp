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

const ll oo = INT64_MIN;

ll n, q;
ll v[MAX], c[MAX];
ll ans[MAX];
pll best, scnd;

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	freopen("balls.inp", "r", stdin);
	freopen("balls.out", "w", stdout);
	cin >> n >> q;
	FOR(ll, i, 1, n) cin >> v[i];
	FOR(ll, i, 1, n) cin >> c[i];
	FOR(ll, _, 1, q){
		ll a, b; cin >> a >> b;
		if (n == 1){cout << max(0ll, v[1] * b) << '\n'; continue;}
		
		FOR(ll, i, 1, n) ans[i] = oo;
		best = {oo, 1}, scnd = {oo, 2};
		best.fi = oo, scnd.fi = oo;
		FOR(ll, i, 1, n){
			ll color = c[i], value = v[i];
			
			ll val1 = b * value;
			ll val2 = ans[color]; 
			if (val2 != oo) val2 += a * value;
			else val2 = oo; //invalidate

			ll val3 = b * value;
			if (best.se != color){
				if (best.fi != oo) val3 += best.fi;
				else val3 = oo; // invalidate;
			} else {
				if (scnd.fi != oo) val3 += scnd.fi;
				else val3 = oo; // invalidate;
			}
			
			val1 = max(val1, val2);
			val1 = max(val1, val3);
			ans[color] = max(val1, ans[color]);
			val1 = ans[color];
			
			if (val1 >= best.fi){
				if (color != best.se)
					scnd = best,
					best = {val1, color};
				else 
					best.fi = val1;
			} else if (val1 >= scnd.fi) 
				scnd = {val1, color};
		}
		cout << max(0ll, best.fi) << '\n';
	}
}