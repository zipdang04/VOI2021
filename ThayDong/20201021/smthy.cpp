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

#define MC 10001
const pll NON = {0, 0};
pll operator + (pll a, pll b){return {a.fi + b.fi, a.se + b.se};}
pll operator * (pll a, ll b){return {a.fi * b, a.se * b};}
pll bit[MC] = {};
void add(ll cost){
	pll tmp = {1, cost};
	while (cost < MC)
		bit[cost] = bit[cost] + tmp, cost += cost & -cost;
}
void del(ll cost){
	pll tmp = {-1, -cost};
	while (cost < MC)
		bit[cost] = bit[cost] + tmp, cost += cost & -cost;
}
pll get(ll cost){
	pll ans(0, 0);
	while (cost)
		ans = ans + bit[cost], cost -= cost & -cost;
	return ans;
}
pll bestM(ll m){
	ll left = 1, right = MC - 1, pos = 0; pll ans = {0, 0};
	while (left <= right){
		ll mid = (left + right) >> 1;
		pll tmp = get(mid);
		if (tmp.fi >= m)
			ans = tmp, pos = mid, right = mid - 1;
		else
			left = mid + 1;
	}
	if (ans == NON) return get(MC - 1);
	if (ans.fi == m) return ans;
	ans.se -= ((ans.fi - m) * pos); ans.fi = m;
	return ans;
}

ll n, m, t;
pll capacity = NON; 
pll ans = NON;
ll prevTime = 0; 
pll action[MAX]; ll len = 0;

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m >> t;
	FOR(int, i, 1, n){
		ll l, r, c; cin >> l >> r >> c;
		action[++len] = {l, c};
		action[++len] = {r + 1, -c};
	}
	sort(action + 1, action + len + 1);
	FOR(int, i, 1, len){
		pll curr = action[i];
		if (curr.se > 0) add(curr.se);
		else del(-curr.se);
		if (curr.fi != action[i + 1].fi){
			ans = ans + capacity * (curr.fi - prevTime);
			prevTime = curr.fi; capacity = bestM(m);
		}
		// cerr << ans.fi << '/' << ans.se << '\n';
	}
	cout << ans.fi << ' ' << ans.se;
}