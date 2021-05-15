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

#define testBit(n, bit) (((n) >> (bit)) & 1)
#define flipBit(n, bit) ((n) ^ (1ll << (bit)))
#define cntBit(n) __builtin_popcount(n)
#define cntBitll(n) __builtin_popcountll(n)
#define randomize mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count());

int n;
pii t[MAX];
string ans;

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	freopen("icpc.inp", "r", stdin);
	freopen("icpc.out", "w", stdout);
	cin >> n;
	FOR(int, i, 1, n){cin >> t[i].fi; t[i].se = i;}
	sort(t + 1, t + 1 + n);

	int x = 0, last = 0, bai = 0;
	FOR(int, i, 1, n){
		last += t[i].fi;
		if (last > 300) {
			last -= t[i].fi;
			break;
		}
		bai = i;
		x += last;
		ans += char(t[i].se + 'A' - 1);
	}
	cout << bai << ' ' << x << ' ' << last << '\n';
	cout << ans;
}