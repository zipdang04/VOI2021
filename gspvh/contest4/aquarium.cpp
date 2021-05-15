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

#define MAX 4000006
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

struct DSU{
	int n;
	int dsu[MAX];

	int findRoot(int u){
		if (dsu[u] < 0) return u;
		return dsu[u] = findRoot(dsu[u]);
	}

	bool join(int u, int v){
		u = findRoot(u), v = findRoot(v);
		if (u == v) return false;

		if (dsu[u] > dsu[v]) swap(u, v);
		dsu[u] += dsu[v], dsu[v] = u;
		return true;
	}

	DSU(int n): n(n){
		FOR(int, i, 1, n) dsu[i] = -1;
	}
} *dsu;

int r, c;
char **brf;
int **val;

int getNum(int row, int col, int dir){
	int num = (row - 1) * c + (col - 1);
	return ((num << 2) | dir) + 1;
}


void input(){
	cin >> r >> c;
	brf = new char*[r + 2];
	val = new int*[r + 2];
	FOR(int, i, 1, r){
		brf[i] = new char[c + 2];
		cin >> brf[i] + 1;
	}
	FOR(int, i, 1, r){
		val[i] = new int[c + 2];
		FOR(int, j, 1, c) cin >> val[i][j];
	}
	dsu = new DSU(r * c * 4);
}

pair<int, pii> edge[MAX]; int eLen = 0;
void init(){
	FOR(int, row, 1, r)
	FOR(int, col, 1, c){
		if (col < c)
			dsu -> join(getNum(row, col, 3), getNum(row, col + 1, 1));
		if (row < r)
			dsu -> join(getNum(row, col, 2), getNum(row + 1, col, 0));
		if (brf[row][col] == '/')
			dsu -> join(getNum(row, col, 0), getNum(row, col, 1)),
			dsu -> join(getNum(row, col, 2), getNum(row, col, 3));
		else 
			dsu -> join(getNum(row, col, 0), getNum(row, col, 3)),
			dsu -> join(getNum(row, col, 2), getNum(row, col, 1));
		edge[++eLen] = {val[row][col], {getNum(row, col, 1), getNum(row, col, 3)}};
	}
}

pii getSq(ll num){
	num >>= 2;
	pii ans;
	ans.se = num % c + 1,
	ans.fi = num / c + 1;
	return ans;
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	// #ifndef ONLINE_JUDGE
	freopen("aquarium.inp", "r", stdin);
	freopen("aquarium.out", "w", stdout);
	// #endif
	input();
	init();
	sort(edge + 1, edge + 1 + eLen);
	ll answer = 0;
	FOR(int, _, 1, eLen){
		pair<int, pii> curr = edge[_];
		if (dsu -> join(curr.se.fi, curr.se.se)){
			answer += curr.fi;
			pii pos = getSq(curr.se.fi);
			brf[pos.fi][pos.se] = '.';
		}
	}
	cout << answer << '\n';
	FOR(int, i, 1, r){
		FOR(int, j, 1, c) cout <<brf[i][j];
		cout << '\n';
	}
}