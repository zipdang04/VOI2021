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

const int N = 5e4 + 500;
ll f[1 << 26];
int nxt[N][26];

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	string s, t;
	cin >> s >> t;
	int n = s.size(), m = t.size();
	for (int c = 0; c < 26; c++) nxt[n][c] = n;
	for (int i = n - 1; i >= 0; i--) {
		for (int c = 0; c < 26; c++) {
			nxt[i][c] = nxt[i + 1][c];
			if (i < n - 1 and s[i + 1] - 'A' == c) nxt[i][c] = i + 1;
		}
	} 
	for (int i = 0; i < n; i++) {
		int msk = 1 << (s[i] - 'A');
		for (int pos = i; pos < n; ) {//pos jump by nxt
			int jump = n;
			for (int c = 0; c < 26; c++) 
				if ((msk & (1 << c)) == 0) jump = min(jump, nxt[pos][c]);
			f[msk] += jump - pos;
			pos = jump;
			if (pos < n)
				msk |= 1 << (s[pos] - 'A');
		}
	}
	ll ans = 0;
	for (int c = 0; c < 26; c++) nxt[m][c] = m;
	for (int i = m - 1; i >= 0; i--) {
		for (int c = 0; c < 26; c++) {
			nxt[i][c] = nxt[i + 1][c];
			if (i < m - 1 and t[i + 1] - 'A' == c) nxt[i][c] = i + 1;
		}
	} 
	for (int i = 0; i < m; i++) {
		int msk = 1 << (t[i] - 'A');
		for (int pos = i; pos < m; ) {//pos jump by nxt
			int jump = m;
			for (int c = 0; c < 26; c++) 
				if ((msk & (1 << c)) == 0) jump = min(jump, nxt[pos][c]);
			ans += (ll) (jump - pos) * f[msk];
			pos = jump;
			if (pos < m)
				msk |= 1 << (t[pos] - 'A');
		}
	}
	cout << ans;
}