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

#define MAX 7005
#define MOD 998244353

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
string str;
char s[MAX];
int f[MAX][MAX];

bool cmp(int l1, int r1, int l2, int r2){
	int len = r1 - l1 + 1;
	FOR(int, i, 1, len){
		char c1 = s[l1 + i - 1], c2 = s[l2 + i - 1];
		if (c1 < c2) return true;
		if (c1 > c2) return false;
	}
	return false;
}

bool checksub4(){
	FOR(int, i, 2, n)
		if (s[i] != s[i - 1]) return false;
	return true;
}

void sub123(){
	f[1][1] = 1;
	FOR(int, i, 2, n){
		FOR(int, j, 1, i - 1){
			if (s[i - j + 1] == '0') f[i][j] = 0;
			else{
				if (j * 2 > i) f[i][j] = f[i - j][i - j];
				else {
					if (cmp(i - (2 * j) + 1, i - j, i - j + 1, i))
						f[i][j] = f[i - j][j];
					else f[i][j] = f[i - j][j - 1];
				}
			}
			f[i][j] += f[i][j - 1]; f[i][j] %= MOD;
		}
		f[i][i] = (f[i][i - 1] + 1) % MOD;
	}
	cout << f[n][n];
}

void sub4(){
	f[1][1] = 1;
	FOR(int, i, 2, n){
		FOR(int, j, 1, i - 1){
			f[i][j] = (f[i - j][min(i - j, j - 1)] + f[i][j - 1]) % MOD;
		}
		f[i][i] = (f[i][i - 1] + 1) % MOD;

	}
	cout << f[n][n];
}

int diff[MAX][MAX];
bool cmp2(int l1, int r1, int l2, int r2){
	int len = r1 - l1 + 1;
	int firstDiff = diff[l1][l2];
	if (firstDiff > len) return false;
	return s[l1 + firstDiff - 1] < s[l2 + firstDiff - 1];
}

void build(){
	FOR(int, i, 1, n + 1)
		FOR(int, j, 1, n + 1)
			diff[i][j] = n + 1;
	FOR(int, d, 1, n){
		FORR(int, i, n - d, 1){
			char ci = s[i], cj = s[i + d];
			if (ci == cj) diff[i][i + d] = diff[i + 1][i + d + 1] + 1;
			else diff[i][i + d] = 1;
		}
	}
}
void sub5(){
	build();
	f[1][1] = 1;
	FOR(int, i, 2, n){
		FOR(int, j, 1, i - 1){
			if (s[i - j + 1] == '0') f[i][j] = 0;
			else{
				if (j * 2 > i) f[i][j] = f[i - j][i - j];
				else {
					if (cmp2(i - (2 * j) + 1, i - j, i - j + 1, i))
						f[i][j] = f[i - j][j];
					else f[i][j] = f[i - j][j - 1];
				}
			}
			f[i][j] += f[i][j - 1]; f[i][j] %= MOD;
		}
		f[i][i] = (f[i][i - 1] + 1) % MOD;
	}
	cout << f[n][n];
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	// #ifndef ONLINE_JUDGE
	freopen("split.inp", "r", stdin);
	freopen("split.out", "w", stdout);
	// #endif
	cin >> str; n = str.length();
	FOR(int, i, 1, n)
		s[i] = str[i - 1];

	if (checksub4()){
		sub4();
	}
	else sub5();
}