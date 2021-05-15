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

#define MAX 902
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

int changeX[4] = {-1, 0, 1, 0};
int changeY[4] = {0, -1, 0, 1};

int m, n;
int mat[MAX][MAX], len = 0;

#define pos(i, j) ((i - 1) * n + j)

bool check(int row, int col){
	if (row < 1 || row > m) return false;
	if (col < 1 || col > n) return false;
	return true;
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> m >> n;
	int finalCol = m * n + 1;
	FOR(int, row, 1, m)
		FOR(int, col, 1, n){
			int num; cin >> num;
			if (num == -1) continue;
			
			len++; mat[len][m * n + 1] = finalCol;
			FOR(int, i, 0, 3){
				int nearRow = row + changeX[i];
				int nearCol = col + changeY[i];
				if (!check(nearRow, nearCol)) continue;

				mat[len][pos(nearRow, nearCol)] = 1;
				
			}
		}
}