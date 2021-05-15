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

#define MAX 23
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

int r, c;
int state[MAX];

int cnt = 0;
void test(int row){
	// FOR(int, i, 0, r - 1){
	// 	cerr << bitset<5>(state[i]) << '\n';
	// }
	// cerr << '\n';
	int msk = state[row - 1]; cnt += cntBit(msk);
	int mskMid = (msk ^ (msk >> 1) ^ (msk << 1)) & ((1 << c) - 1);
	
	state[row - 1] ^= msk, state[row + 1] ^= msk, state[row] ^= mskMid;
	
	if (row == r - 1){
		if (state[row]) cnt = 1e9; 
	} else test(row + 1);

	state[row - 1] ^= msk, state[row + 1] ^= msk, state[row] ^= mskMid;
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	#ifndef HIEU
	freopen("billboard.inp", "r", stdin);
	freopen("billboard.out", "w", stdout);
	#endif
	cin >> r >> c;
	FOR(int, i, 0, r - 1){
		string s; cin >> s;
		FOR(int, j, 0, c - 1)
			state[i] ^= int(s[j] == 'X') << j;
	}
	int ans = 1e9;
	FOR(int, msk, 0, (1 << c) - 1){
		int mskMid = (msk ^ (msk >> 1) ^ (msk << 1)) & ((1 << c) - 1);
		state[0] ^= mskMid;
		state[1] ^= msk;
		// FOR(int, i, 0, r - 1)
		// 	cerr << bitset<5>(msk) << ' ' << bitset<5>(state[i]) << '\n';
		
		cnt = cntBit(msk);
		if (r > 1)
			test(1);
		else if (state[0])
			cnt = 1e9;
		ans = min(ans, cnt);
		// cerr << ans << ' ' << cnt << ' ' << cntBit(msk) << '\n';
		
		state[0] ^= mskMid;
		state[1] ^= msk;
	}
	if (ans == 1e9) cout << "Damaged billboard.";
	else cout << "You have to tap " << ans << " tiles.";
}