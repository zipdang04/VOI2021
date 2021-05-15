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
#define MOD 998244353

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

ll	 k, n;
ll f[6][MAX];

struct Matrix{
	ll mat[26][26] = {};
};
Matrix operator * (Matrix a, Matrix b){
	Matrix ans;
	FOR(ll, k, 0, 25)
		FOR(ll, i, 0, 25)
			FOR(ll, j, 0, 25)
				ans.mat[i][j] += (a.mat[i][k] * b.mat[k][j]) % MOD,
				ans.mat[i][j] %= MOD;
	return ans;
}
Matrix operator ^ (Matrix a, ll n){
	if (n == 1) return a;
	Matrix ans = a ^ (n >> 1); ans = ans * ans;
	if (n & 1) return ans * a;
	return ans;
}
ll sub5(){
	Matrix f;
	f.mat[0][1] = 1;
	f.mat[1][1] = 1;
	f.mat[1][2] = 1;
	f.mat[2][3] = 1;
	f.mat[3][4] = 1;
	f.mat[4][3] = 1;
	f.mat[3][5] = 1;
	f.mat[5][6] = 1;
	f.mat[6][7] = 1;
	f.mat[7][8] = 1;
	f.mat[8][9] = 1;
	f.mat[9][7] = 1;
	f.mat[7][10] = 1;
	f.mat[10][11] = 1;
	f.mat[11][12] = 1;
	f.mat[12][13] = 1;
	f.mat[13][14] = 1;
	f.mat[14][15] = 1;
	f.mat[15][16] = 1;
	f.mat[16][13] = 1;
	f.mat[13][17] = 1;
	f.mat[17][18] = 1;
	f.mat[18][19] = 1;
	f.mat[19][20] = 1;
	f.mat[20][21] = 1;
	f.mat[21][22] = 1;
	f.mat[22][23] = 1;
	f.mat[23][24] = 1;
	f.mat[24][25] = 1;
	f.mat[25][21] = 1;

	f = f ^ n;
	if (k == 1) return f.mat[0][1];
	if (k == 2) return f.mat[0][3];
	if (k == 3) return f.mat[0][7];
	if (k == 4) return f.mat[0][13];
	if (k == 5) return f.mat[0][21];
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	// #ifndef ONLINE_JUDGE
	freopen("diduduadi.inp", "r", stdin);
	freopen("diduduadi.out", "w", stdout);
	// #endif
	cin >> n >> k;
	// if (k == 2){
	// 	cout << (n - 1) / 2;
	// 	return 0;
	// }
	// if (n <= 1000000){
	// 	FOR(ll, i, 1, n) f[1][i] = 1;
	// 	FOR(int, turn, 2, k){
	// 		int mod[turn] = {};
	// 		FOR(int, i, 1, n){
	// 			f[turn][i] = mod[i % turn];
	// 			mod[i % turn] += f[turn - 1][i];
	// 			mod[i % turn] %= MOD;
	// 		}
	// 	}
	// 	cout << f[k][n];
	// 	return 0;
	// }
	cout << sub5();
}