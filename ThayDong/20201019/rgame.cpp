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

ll n, a[MAX], f[MAX][2];

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	ll t; cin >> t;
	FOR(ll, _, 1, t){
		cin >> n; FOR(ll, i, 1, n) {cin >> a[i]; a[i] <<= 1;}
		
		f[1][0] = 0, f[1][1] = a[2];
		ll answer = max(f[1][0], f[1][1]);
		FOR(ll, i, 2, n){
			f[i][0] = f[i][1] = 0;

			f[i][0] = max(f[i - 1][0] + a[i - 1], f[i - 1][1]);
			
			if (i < n)
				f[i][1] = max(f[i - 1][0] + (a[i - 1] + a[i + 1]) / 2, f[i - 1][1] + a[i + 1]);
			else
				f[i][1] = max(f[i - 1][0] + a[i - 1], f[i - 1][1] + a[i + 1]);
			answer = max(answer, max(f[i][0], f[i][1]));
		}

		cout << answer / 2 << ((answer & 1) ? ".5" : ".0") << '\n';
	}
}