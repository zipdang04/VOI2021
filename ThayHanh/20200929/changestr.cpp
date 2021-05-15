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

#define MAX 100001
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

#define c2i(ch) (ch - 'a' + 1)
#define i2c(num) (num + 'a' - 1)

ll cost[27][27] = {};
ll cnt[MAX][27] = {};
ll n, m;
char s[MAX];

main()
{
#ifndef ONLINE_JUDGE
	freopen("changestr.inp", "r", stdin);
	freopen("changestr.out", "w", stdout);
#endif
	ios_base::sync_with_stdio(0); cin.tie(0);
	//init
	cin >> n >> m >> s + 1;
	FOR(ll, i, 1, m)
	FOR(ll, i, 1, 26) {
		FOR(ll, j, 1, 26) cost[i][j] = INT32_MAX;
		cost[i][i] = 0;
	}
	FOR(ll, i, 1, m){
		char a, b; ll c; cin >> a >> b >> c;
		cost[c2i(a)][c2i(b)] = min(cost[c2i(a)][c2i(b)], c);
	}
	//floyd
	FOR(ll, k, 1, 26)
		FOR(ll, i, 1, 26)
			FOR(ll, j, 1, 26)
				cost[i][j] = min(cost[i][j], cost[i][k] + cost[k][j]);
	//main thing
	ll miCost = INT64_MAX;
	FOR(ll, len, 2, n){
		if (n % len) continue;

		FOR(ll, i, 0, len - 1)
			FOR(ll, j, 1, 26) cnt[i][j] = 0; 
		FOR(ll, i, 1, n) cnt[i % len][c2i(s[i])]++;

		ll currCost = 0;
		bool good = true;
		FOR(ll, i, 0, len - 1){
			ll mi = INT64_MAX;
			bool lvl1 = false;
			FOR(ll, root, 1, 26){
				ll curr = 0;
				bool lvl2 = true;
				FOR(ll, ch, 1, 26){
					if (i == ch) continue;
					if (!cnt[i][ch]) continue;
					if (cost[ch][root] == INT32_MAX){lvl2 = false; break;}
					curr += cnt[i][ch] * cost[ch][root];
				}
				if (!lvl2) continue;
				lvl1 = true;
				cerr << "//" << curr << '\n';
				mi = min(mi, curr);
			}
			if (!lvl1){
				good = false; break;
			}
			cerr << "/////" << mi << '\n';
			currCost += mi;
		}
		if (!good) continue;
		cerr << "=======\n";
		miCost = min(miCost, currCost);
	}
	if (miCost == INT64_MAX) cout << -1;
	else cout << miCost;
}