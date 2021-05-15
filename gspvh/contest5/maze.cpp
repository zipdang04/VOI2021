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

#define testBit(n, bit) (((n) >> (bit)) & 1)
#define flipBit(n, bit) ((n) ^ (1ll << (bit)))
#define cntBit(n) __builtin_popcount(n)
#define cntBitll(n) __builtin_popcountll(n)
#define randomize mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count());

const char ROCK = '#', START = '*', EXIT = 'X';
const char DOOR[5] = "YRGB";
const char KEY[5] = "yrgb";
const int NaN = -1;

struct Point{int x, y;};
typedef pair<Point, int> Data;
Point operator + (Point a, Point b){return {a.x + b.x, a.y + b.y};}
Point operator - (Point a, Point b){return {a.x - b.x, a.y - b.y};}
bool operator == (Point a, Point b){return a.x == b.x && a.y == b.y;}
bool operator != (Point a, Point b){return !(a == b);}
const Point direc[4] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

int r, c;
char maze[MAX][MAX];
int f[MAX][MAX][16];
Point st, ex;

void input(){
	cin >> r >> c;
	FOR(int, i, 1, r) {
		cin >> maze[i] + 1;
		FOR(int, j, 1, c){
			FOR(int, m1, 0, 15)
				f[i][j][m1] = NaN;
			if (maze[i][j] == START)
				st = {i, j};
			else if (maze[i][j] == EXIT)
				ex = {i, j};
		}
	}
}

bool check(Point p){
	return p.x >= 1 && p.x <= r && p.y >= 1 && p.y <= c;
}
int isDoor(char c){
	FOR(int, i, 0, 3)
		if (c == DOOR[i]) return i;
	return NaN;
}
int isKey(char c){
	FOR(int, i, 0, 3)
		if (c == KEY[i]) return i;
	return NaN;
}

queue<Data> q;
main()
{
	#ifndef HIEU
	freopen("maze.inp", "r", stdin);
	freopen("maze.out", "w", stdout);
	#endif
	ios_base::sync_with_stdio(0); cin.tie(0);
	input();
	#define get(pos, key) f[pos.x][pos.y][key]
	get(st, 0) = 0; q.push({st, 0});
	while (!q.empty()){
		Data curr = q.front(); q.pop();
		Point currPos = curr.fi; int maskKey = curr.se;
		// cerr << maze[currPos.x][currPos.y] << ' ' << currPos.x << '/' << currPos.y << ' ' << bitset<4>(maskKey) << '\n';
		int step = get(currPos, maskKey) + 1;

		for (Point d: direc){
			Point nowPos = currPos + d;
			if (!check(nowPos)) continue;
			char c = maze[nowPos.x][nowPos.y];

			if (c == ROCK) continue;
			if (c == EXIT){cout << "Escape possible in " << step << " steps."; return 0;}
			
			int tmp = isKey(c);
			if (tmp != NaN){
				int newKey = maskKey | (1 << tmp);
				if (get(nowPos, newKey) == NaN)
					get(nowPos, newKey) = step, q.push({nowPos, newKey});
				continue;
			}

			tmp = isDoor(c);
			if (tmp != NaN){
				if (testBit(maskKey, tmp) && get(nowPos, maskKey) == NaN)
					get(nowPos, maskKey) = step, q.push({nowPos, maskKey}); 
				continue;
			}

			if (get(nowPos, maskKey) == NaN)
				get(nowPos, maskKey) = step, q.push({nowPos, maskKey}); 
		}
	}
	cout << "The poor student is trapped!";
}