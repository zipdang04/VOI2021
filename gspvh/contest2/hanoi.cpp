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

#define MAX 1001
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

struct Point {int x, y;};
Point operator + (Point a, Point b){return {a.x + b.x, a.y + b.y};}
Point operator - (Point a, Point b){return {a.x - b.x, a.y - b.y};}
bool operator < (Point a, Point b){
	return a.x < b.x || (a.x == b.x && a.y < b.y);
}
const Point direc[4] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

int r, c, k;
char s[MAX][MAX];
bool visited[MAX][MAX] = {};

bool check(Point p){
	return (p.x >= 1) && (p.y >= 1) && (p.x <= r) && (p.y <= c);
}

int bfs(Point root){
	int ans = 1;
	queue<Point> q;

	visited[root.x][root.y] = true; q.push(root);
	while (!q.empty()){
		Point curr = q.front(); q.pop();

		for (Point d: direc){
			Point now = curr + d;
			if (!check(now)) continue;
			if (visited[now.x][now.y]) continue;
			if (s[now.x][now.y] == '#') continue;
			
			ans++;
			visited[now.x][now.y] = true;
			q.push(now);
		}
	}
	return ans;
}

pair<int, Point> sub[MAX * MAX]; int cntSub = 0;

void fillIn(Point root){
	queue<Point> q;
	s[root.x][root.y] = '#'; q.push(root);
	while (!q.empty()){
		Point curr = q.front(); q.pop();
		
		for (Point d: direc){
			Point now = curr + d;
			if (!check(now)) continue;
			if (s[now.x][now.y] == '#') continue;
			
			s[now.x][now.y] = '#'; q.push(now);
		}
	}
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	// #ifndef ONLINE_JUDGE
	freopen("hanoi.inp", "r", stdin);
	freopen("hanoi.out", "w", stdout);
	// #endif
	cin >> r >> c >> k;
	FOR(int, i, 1, r) cin >> s[i] + 1;

	FOR(int, i, 1, r) {
		if (s[i][1] == '.')
			bfs({i, 1}); 
		if (s[i][c] == '.')
			bfs({i, c});
	}
	FOR(int, i, 1, c) {
		if (s[1][i] == '.')
			bfs({1, i});
		if (s[r][i] == '.')
			bfs({r, i});
	}

	FOR(int, i, 2, r - 1)
		FOR(int, j, 2, c - 1){
			if (visited[i][j]) continue;
			if (s[i][j] == '#') continue;
			sub[++cntSub] = {bfs({i, j}), {i, j}};
		}
	sort(sub + 1, sub + cntSub + 1);
	int ans = 0;
	FOR(int, i, 1, cntSub - k){
		ans += sub[i].fi;
		fillIn(sub[i].se);
	}
	cout << ans << '\n';
	FOR(int, i, 1, r) {
		FOR(int, j, 1, c)
			cout << s[i][j];
		cout << '\n';
	}
}