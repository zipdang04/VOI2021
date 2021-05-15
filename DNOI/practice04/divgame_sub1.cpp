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

#define MAX 101
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

#define A true
#define B false

ll x, y;
int win[MAX][MAX][2];

bool game(bool turn, int x, int y){
	if (x == 1 && y == 1) return false;
	if (win[x][y][turn] != -1) return win[x][y][turn];

	bool canWin = false;
	//change X only
	FOR(int, i, 1, x){
		if (i * i > x) break;
		if (x % i) continue;
		int num1 = i, num2 = x / i;
		if (num1 != x && !game(!turn, num1, y)) canWin = true;
		if (num2 != x && !game(!turn, num2, y)) canWin = true;
	}
	//=========================
	//change Y only
	FOR(int, i, 1, y){
		if (i * i > y) break;
		if (y % i) continue;
		int num1 = i, num2 = y / i;
		if (num1 != y && !game(!turn, x, num1)) canWin = true;
		if (num2 != y && !game(!turn, x, num2)) canWin = true;
	}
	//=========================
	//change both
	if (x > 1 && y > 1){
		int g = __gcd(x, y);
		FOR(int, i, 1, g){
			if (i * i > g) break;
			if (g % i) continue;
			int num1 = i, num2 = g / i;
			if (num1 != 1 && !game(!turn, x / num1, y / num1)) canWin = true;
			if (num2 != 1 && !game(!turn, x / num2, y / num2)) canWin = true;
		}
	}
	//=========================
	win[x][y][turn] = canWin;
	return canWin;
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> x >> y;
	FOR(int, i, 1, x)
		FOR(int, j, 1, y)
			win[i][j][A] = win[i][j][B] = -1;
	cout << (game(A, x, y) ? "A" : "B") << '\n';
}