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
ll turn[MAX]; 
ll f[256];
ll answer;

ll dp(ll state){
	if (cntBitll(state) == 1) return 0;
	if (f[state] != -1) return f[state];

	bool save[n]; FOR(ll, i, 0, n - 1) save[i] = testBit(state, i);

	FOR(ll, i, 0, n - 1){
		if (!save[i]) continue;
		ll nextState = flipBit(state, i);

		if (i > 0 && i < n - 1 && (save[i - 1] && save[i + 1])){
			f[state] = max(f[state], dp(nextState) + (a[i - 1] + a[i + 1]) / 2);
		}
		else if (i > 0 && save[i - 1]){
			f[state] = max(f[state], dp(nextState) + a[i - 1]);
		}
		else if (i < n - 1 && save[i + 1]){
			f[state] = max(f[state], dp(nextState) + a[i + 1]);
		}
		else f[state] = max(f[state], dp(nextState));
	}
	return f[state];
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	ll T; cin >> T;

	FOR(ll, _, 1, T){
		cin >> n; FOR(ll, i, 0, n - 1) {cin >> a[i]; a[i] <<= 1;}
		FOR(int, i, 0, (1 << n) - 1) f[i] = -1;
		answer = dp((1 << n) - 1);

		cout << (answer >> 1);
		if (answer & 1) cout << ".5";
		else cout << ".0";
		cout << '\n';
	}
}