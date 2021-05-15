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

#define MAX 502
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

int n, m;
char forest[MAX][MAX];
Point posi, home;
Point tree[MAX * MAX]; int cntTree = 0;
int dist[MAX][MAX];

const int oo = INT32_MAX;

bool check(Point p){return (p.x >= 1) && (p.y >= 1) && (p.x <= n) && (p.y <= m);}

void bfs(){
	queue<Point> q;
	FOR(int, i, 1, cntTree){
		Point currTree = tree[i];
		
		dist[currTree.x][currTree.y] = 0;
		q.push(currTree);
	}

	while (!q.empty()){
		Point curr = q.front(); q.pop();
		int currDist = dist[curr.x][curr.y];

		for (Point d: direc){
			Point now = curr + d;
			if (!check(now)) continue;
			if (dist[now.x][now.y] != oo) continue;

			dist[now.x][now.y] = currDist + 1;
			q.push(now);
		}
	}
}

bool test(int thres){
	bool visited[MAX][MAX] = {};
	queue<Point> q;

	q.push(posi); visited[posi.x][posi.y] = true;
	while (!q.empty()){
		Point curr = q.front(); q.pop();

		for (Point d: direc){
			Point now = curr + d;
			if (!check(now)) continue;
			if (visited[now.x][now.y]) continue;
			if (dist[now.x][now.y] < thres) continue;
			
			q.push(now); visited[now.x][now.y] = true;
		}
	}
	return visited[home.x][home.y];
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	//input && init
	cin >> n >> m;
	FOR(int, i, 1, n){
		cin >> forest[i] + 1;
		FOR(int, j, 1, m){
			dist[i][j] = oo;
			switch(forest[i][j]){
				case '+':
					tree[++cntTree] = {i, j}; break;
				case 'V':
					posi = {i, j}; break;
				case 'J':
					home = {i, j}; break;
				default: break;
			}
		}
	}
	//=========================
	//do something
	bfs();
	int l = 0, r = min(dist[posi.x][posi.y], dist[home.x][home.y]), ans = r;
	while (l <= r){
		int mid = (l + r) >> 1;
		if (test(mid)) ans = mid, l = mid + 1;
		else r = mid - 1;
	}
	cout << ans;
	//=========================
}