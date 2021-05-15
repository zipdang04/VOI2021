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

#define MAX 505
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

struct Point {ll x, y;};
const Point direc[4] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
Point operator + (Point a, Point b){return {a.x + b.x, a.y + b.y};}
Point operator - (Point a, Point b){return {a.x - b.x, a.y - b.y};}
bool operator == (Point a, Point b){return a.x == b.x && a.y == b.y;}

int h, w, d;
int value[MAX][MAX];

bool check(Point p){return p.x >= 1 && p.y >= 1 && p.x <= h && p.y <= w;}

int dsu[MAX][MAX];
Point root[MAX][MAX];
int maxVal[MAX][MAX];

Point findRoot(Point p){
	if (root[p.x][p.y] == p) 
		return p;
	else 
		return root[p.x][p.y] = findRoot(root[p.x][p.y]);
}

void join(Point u, Point v){
	u = findRoot(u), v = findRoot(v);
	if (u == v) return;

	if (dsu[u.x][u.y] < dsu[v.x][v.y]) swap(u, v);
	dsu[u.x][u.y] += dsu[v.x][v.y];
	maxVal[u.x][u.y] = max(maxVal[u.x][u.y], maxVal[v.x][v.y]);
	root[v.x][v.y] = u;
}

pair<int, pii> save[MAX * MAX]; int len = 0;

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> h >> w >> d;
	FOR(int, i, 1, h)
		FOR(int, j, 1, w){
			cin >> value[i][j];
			dsu[i][j] = 1;
			root[i][j] = {i, j};
			maxVal[i][j] = value[i][j];

			save[++len] = {value[i][j], {i, j}};
		}
	sort(save + 1, save + 1 + len, greater<pair<int, pii>>());
	int ptr = 1;
	int ans = 0;
	FOR(int, _, 1, len){
		pair<int, pii> curr = save[_];
		int val = curr.fi; Point pos = {curr.se.fi, curr.se.se};
		int thres = val - d;

		while (ptr <= len){
			pair<int, pii> tmp = save[ptr];
			int tmpVal = tmp.fi; Point tmpPos = {tmp.se.fi, tmp.se.se};
			if (tmpVal <= thres) break; ptr++;

			for (Point d: direc){
				Point now = tmpPos + d;
				if (!check(now)) continue;
				if (value[now.x][now.y] > thres)
					join(tmpPos, now);
			}
		}
		
		Point currRoot = findRoot(pos);
		if (maxVal[currRoot.x][currRoot.y] > val);
		else ans++;
	}
	cout << ans;
}