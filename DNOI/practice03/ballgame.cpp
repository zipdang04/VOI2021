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

#define MAX 1010
#define MG 200
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

struct Point{int x, y;};
const Point direc[4] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
Point operator + (Point a, Point b) {return {a.x + b.x, a.y + b.y};}
ll calDist(Point a, Point b){return abs(a.x - b.x) + abs(a.y - b.y);}


int n, m;
Point ban[MAX + 1], ball[MAX + 1];
bool grid[MG + 1][MG + 1];
int dist[MAX + 1][MG + 1][MG + 1];

bool check(Point a){
	if (a.x < 1 || a.x > MG) return false;
	if (a.y < 1 || a.y > MG) return false;
	return true;
}

void bfs(int pos, Point root){
	queue<Point> q;
	dist[pos][root.x][root.y] = 0, q.push(root);
	while (!q.empty()){
		Point curr = q.front(); q.pop();
		int currVal = dist[pos][curr.x][curr.y];

		for (Point add: direc){
			Point next = curr + add;
			if (!check(next)) continue;
			if (grid[next.x][next.y]) continue;
			
			int &val = dist[pos][next.x][next.y];
			if (val != -1) continue;
			val = currVal + 1, q.push(next);
		}
	}
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	//input
	bool sub5 = false;
	cin >> n;
	FOR(int, i, 1, n) {
		cin >> ban[i].x >> ban[i].y;
		if (ban[i].x > 100 || ban[i].y > 100) sub5 = true;
	}
	cin >> m;
	FOR(int, i, 1, m){ 
		cin >> ball[i].x >> ball[i].y;
		if (ball[i].x > 100 || ball[i].y > 100) sub5 = true;
	}
	//=========================
	//chia sub
	if (!sub5){
		//init
		FOR(int, i, 1, n) ban[i].x += 50, ban[i].y += 50;
		FOR(int, i, 1, m) ball[i].x += 50, ball[i].y += 50;
		FOR(int, i, 1, n) grid[ban[i].x][ban[i].y] = true;
		FOR(int, i, 1, m)
			FOR(int, row, 1, MG)
				FOR(int, col, 1, MG)
					dist[i][row][col] = -1;
		//=========================
		//mainThing
		FOR(int, i, 1, m)
			bfs(i, ball[i]);
		//=========================
		ll answer = INT64_MAX;
		FOR(int, row, 1, MG)
			FOR(int, col, 1, MG){
				if (grid[row][col]);
				ll sum = 0; bool okay = true;
				FOR(int, i, 1, m){
					int &tmp = dist[i][row][col];
					if (tmp == -1){okay = false; break;}

					sum += tmp;
				}
				if (okay) answer = min(answer, sum);
			}
		if (answer == INT64_MAX) answer = -1;
		cout << answer;
	} else {
		int allX[MAX + 1], lenX; FOR(int, i, 1, m) allX[lenX++] = ball[i].x;
		int allY[MAX + 1], lenY; FOR(int, i, 1, m) allY[lenY++] = ball[i].y;
		sort(allX, allX + lenX);
		sort(allY, allY + lenY);

		ll answer = INT64_MAX;
		int midX = allX[lenX / 2], midY = allY[lenX / 2];
		FOR(int, row, midX - 51, midX + 51)
			FOR(int, col, midY - 51, midY + 51){
				bool okay = true;
				Point pivot = {row, col};

				ll sum = 0;
				FOR(int, i, 1, m){
					Point curr = ball[i];
					if (pivot.x == curr.x && pivot.y == curr.y){okay = false; break;}

					sum += calDist(pivot, curr);
				}

				if (okay) answer = min(answer, sum);
			}
		cout << answer;
	}
	//=========================
}