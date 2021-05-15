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

ll query(ll need, ll d){
	if (need == 1) return 0;
	ll p = 1;
	FOR(ll, i, 1, need){
		if (i > d) break;
		if (i * i > need) break;
		if (need % i) continue;

		p = max(p, i);
		if (need / i <= d) p = max(p, need / i);
	}
	if (p == 1) return -1;
	
	ll cnt = 0;
	while (need >= p && (need % p == 0)){
		need /= p; cnt++;
	}
	ll cnt2 = query(need, d);
	if (cnt2 == -1) return -1;
	return cnt + cnt2;
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	ll a, b, d; cin >> a >> b >> d;
	ll lcm = a * b / __gcd(a, b);
	
	ll ans1 = query(lcm / a, d);
	if (ans1 == -1) {cout << -1; return 0;}
	ll ans2 = query(lcm / b, d);
	if (ans2 == -1) {cout << -1; return 0;}
	
	cout << ans1 + ans2;
}