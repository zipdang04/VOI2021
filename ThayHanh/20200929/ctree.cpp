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

ll n;
ll a[MAX];
ll f[MAX];
set<ll> s;

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
#ifndef ONLINE_JUDGE
	freopen("ctree.inp", "r", stdin);
	freopen("ctree.out", "w", stdout);
#endif
	cin >> n;
	FOR(ll, i, 1, n) {cin >> a[i]; f[a[i]] = 1;}
	sort(a + 1, a + 1 + n);
	ll ans = f[a[1]];
	FOR(ll, i, 2, n){
		ll num = a[i];
		if (num == a[i - 1]) continue;
		FOR(ll, j, 2, num){
			if (j * j > num) break;
			if (num % j) continue;
			ll n1 = j, n2 = num / j;
			if (n1 == n2){
				if (f[n1])
					f[num] += (f[n1] * f[n2]) % MOD, f[num] %= MOD;
			} else {
				if (f[n1] && f[n2])
					f[num] += ((f[n1] * f[n2]) % MOD * 2) % MOD, f[num] %= MOD;
			}
		}
		ans += f[num];
		ans %= MOD;
	}
	cout << ans << '\n';
}