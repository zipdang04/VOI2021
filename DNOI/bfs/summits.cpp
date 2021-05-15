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

int h, w, d;
int value[MAX][MAX];

bool check(Point p){return p.x >= 1 && p.y >= 1 && p.x <= h && p.y <= w;}

bool bfs(Point root){
	bool visited[MAX][MAX] = {};
	queue<Point> q;

	q.push(root); visited[root.x][root.y] = true;
	int rootVal = value[root.x][root.y], thres = rootVal - d;
	// cerr << "check: " << root.x << ' ' << root.y << '|' << rootVal << ' ' << thres<< '\n';
	while (!q.empty()){
		Point node = q.front(); q.pop();
		int currValue = value[node.x][node.y];
		// cerr << "   curr: " << node.x << ' ' << node.y << '\n';

		for (Point d: direc){
			Point now = node + d;
			if (!check(now)) continue;
			if (visited[now.x][now.y]) continue;
			int nowVal = value[now.x][now.y];
			if (nowVal <= thres) continue;
			
			if (nowVal > rootVal) return false;
			q.push(now); visited[now.x][now.y] = true;
		}
	}
	// cerr << "fail\n";
	return true;
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> h >> w >> d;
	FOR(int, i, 1, h)
		FOR(int, j, 1, w)
			cin >> value[i][j];
	int answer = 0;
	FOR(int, i, 1, h)
		FOR(int, j, 1, w){
			answer += (value[i][j] < d) ? 0 : bfs({i, j});
		}
	cout << answer;
}