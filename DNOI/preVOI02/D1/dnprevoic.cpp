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

#define MAX 3000005
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

struct Point{int r, c;};
Point operator + (Point a, Point b){return {a.r + b.r, a.c + b.c};}
Point operator - (Point a, Point b){return {a.r - b.r, a.c - b.c};}
bool operator < (Point a, Point b){
	if (a.r < b.r) return true;
	if (a.r > b.r) return false;
	return a.c < b.c;
}
bool operator == (Point a, Point b){return (a.r == b.r && a.c == b.c);}
bool operator != (Point a, Point b){return !(a == b);}
//========================================================================
int theta, m, n;
vector<vi> a, dsu;
vector<vector<Point>> root;
vector<vector<Point>> minP;
bool check(Point p){
	return (p.r >= 1 & p.c >= 1 && p.r <= m && p.c <= n);
}
void initGrid(){
	a = vector<vi>(m + 1, vi(n + 1, 0));
	dsu = vector<vi>(m + 1, vi(n + 1, 1));
	root = minP = vector<vector<Point>>(m + 1, vector<Point>(n + 1, {0, 0}));
	FOR(int, i, 1, m)
		FOR(int, j, 1, n)
			root[i][j] = minP[i][j] = {i, j};
}
//========================================================================
Point findRoot(Point node){
	if (root[node.r][node.c] == node) return node;
	return root[node.r][node.c] = findRoot(root[node.r][node.c]);
}
int join(Point u, Point v){
	u = findRoot(u), v = findRoot(v);
	int &dU = dsu[u.r][u.c], &dV = dsu[v.r][v.c];
	if (u == v) return max(dU, dV);

	if (dU < dV) swap(dU, dV);
	dU += dV, root[v.r][v.c] = u, 
	minP[u.r][u.c] = min(minP[u.r][u.c], minP[v.r][v.c]);
	
	return dU;
}
//========================================================================
typedef pair<Point, Point> Edge;
bool cmp(pair<int, Edge> a, pair<int, Edge> b){return a.fi < b.fi;};

pair<int, Edge> save[MAX]; int cntEdge = 0;
vector<Edge> dist[MAX];
vector<Point> pList;
main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> theta >> m >> n;
	initGrid();
	FOR(int, i, 1, m)
		FOR(int, j, 1, n) cin >> a[i][j];
	// ===================================================================
	FOR(int, i, 1, m)
		FOR(int, j, 1, n){
			Point p = {i, j}, p1 = {i + 1, j}, p2 = {i, j + 1};
			if (check(p1))
				save[++cntEdge] = {abs(a[p.r][p.c] - a[p1.r][p1.c]), {p, p1}};
			if (check(p2))
				save[++cntEdge] = {abs(a[p.r][p.c] - a[p2.r][p2.c]), {p, p2}};
		}
	sort(save + 1, save + 1 + cntEdge);
	save[++cntEdge] = {INT32_MAX, {{0, 0}, {0, 0}}};
	// ===================================================================
	int ansK = 1, ansD = 0; Point ansP = {1, 1};
	int prevD = -1;
	FOR(int, _, 1, cntEdge){
		pair<int, Edge> curr = save[_];
		int currD = curr.fi; Edge currE = curr.se;
		if (currD != prevD){
			for (Point p: pList){
				Point pRoot = findRoot(p);
				int pK = dsu[pRoot.r][pRoot.c];
				if (pK > ansK)
					ansK = pK, ansD = prevD, ansP = p;
				else if (pK == ansK && prevD < ansD)
					ansD = prevD, ansP = p;
				else if (pK == ansK && prevD == ansD && p < ansP)
					ansP = p;
			}
			for (Point p: pList)
				dsu[p.r][p.c] = 1,
				root[p.r][p.c] = minP[p.r][p.c] = p;
			pList.clear();
			
			prevD = currD;
			if (prevD == INT32_MAX) break;
		}

		Point u = currE.fi, v = currE.se;
		join(u, v);
		pList.push_back(u), pList.push_back(v);
	}

	cout << ansK << ' ' << ansD << ' ' << ansP.r << ' ' << ansP.c << '\n';
}