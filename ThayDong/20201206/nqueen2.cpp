
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

#define MAX 501
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
int state[MAX];
int ans[MAX];

int occupy[MAX][MAX] = {};
int stillFree[MAX] = {};
bool found;

void open(int x, int y, int value){
	if (occupy[x][y]) return;
	occupy[x][y] = value;
	stillFree[x]--;
}
void close(int x, int y, int value){
	if (occupy[x][y] != value) return;
	occupy[x][y] = 0;
	stillFree[x]++;
}

void add(int row, int col, int value){
	FOR(int, i, 1, n)
		open(row, i, value),
		open(i, col, value);
	int x = row, y = col;
	while (x <= n && y <= n){
		open(x, y, value);
		x++, y++;
	}
	x = row, y = col;
	while (x <= n && y >= 1){
		open(x, y, value);
		x++, y--;
	}
	x = row, y = col;
	while (x >= 1 && y <= n){
		open(x, y, value);
		x--, y++;
	}
	x = row, y = col;
	while (x >= 1 && y >= 1){
		open(x, y, value);
		x--, y--;
	}
}

void del(int row, int col, int value){
	FOR(int, i, 1, n)
		close(row, i, value),
		close(i, col, value);
	int x = row, y = col;
	while (x <= n && y <= n){
		close(x, y, value);
		x++, y++;
	}
	x = row, y = col;
	while (x <= n && y >= 1){
		close(x, y, value);
		x++, y--;
	}
	x = row, y = col;
	while (x >= 1 && y <= n){
		close(x, y, value);
		x--, y++;
	}
	x = row, y = col;
	while (x >= 1 && y >= 1){
		close(x, y, value);
		x--, y--;
	}
}

void dqql(int turn){
	if (turn > n){
		found = true; return;
	}

	int row = 0, mi = INT32_MAX;
	FOR(int, i, 1, n){
		if (ans[i]) continue;
		if (stillFree[i] < mi)
			mi = stillFree[i], row = i;
	}

	if (state[row]){
		ans[row] = state[row];
		add(row, ans[row], turn);
		dqql(turn + 1);
		del(row, ans[row], turn);
		if (!found) ans[row] = 0;
		return;
	}
	FOR(int, col, 1, n){
		if (occupy[row][col]) continue;
		ans[row] = col;
		add(row, col, turn);
		dqql(turn + 1);
		del(row, col, turn);
		if (!found) ans[row] = 0;
		else return;
	}
}

main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	while (cin >> n){
		FOR(int, i, 1, n) stillFree[i] = n;
		FOR(int, i, 1, n) {
			cin >> state[i];
			if (state[i]) stillFree[i] = 1;
		}
		dqql(1);
		FOR(int, i, 1, n) cout << ans[i] << ' '; cout << '\n';

		memset(occupy, 0, sizeof(occupy));
		memset(stillFree, 0, sizeof(stillFree));
		memset(ans, 0, sizeof(ans));
		found = false;
	}
}