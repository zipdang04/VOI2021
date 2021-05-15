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

#define MAX 1003
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

int w, l, h, m, n, k;
int red[MAX][MAX];

int get(int x1, int y1, int x2, int y2){
	return red[x2][y2] - red[x2][y1 - 1] - red[x1 - 1][y2] + red[x1 - 1][y1 - 1];
}
//================================================================================

//================================================================================
#define LAT true
#define DAY false
#define LEFT 0
#define UP 1
#define RIGHT 2
#define DOWN 3
// 	0	1	2	3	4	5
// 	wlh whl lwh lhw hwl hlw
int *addW, *addL, *addH;
int oChange[6][2] = {
	{1, 5},
	{0, 3},
	{3, 4},
	{2, 1},
	{5, 2},
	{4, 0},
};
void init(){
	addW = new int[6]{w, w, l, l, h, h};
	addL = new int[6]{l, h, w, h, w, l};
	addH = new int[6]{h, l, h, w, l, w};
}

struct Point{ll x, y;};
const Point direc[4] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
Point operator + (Point a, Point b) {return {a.x + b.x, a.y + b.y};}
Point operator - (Point a, Point b) {return {a.x - b.x, a.y - b.y};}
Point operator * (Point a, ll b) {return {a.x * b, a.y * b};}

struct Data{Point p; int o;};
Data change(Data dat, bool act, int direction){
	if (act == DAY)
		return {dat.p + direc[direction], dat.o};
	else {
		int currW = addW[dat.o];
		int currL = addL[dat.o];
		int currH = addH[dat.o];
		if (direction == 0)
			return {dat.p + direc[direction] * currH, oChange[dat.o][0]};
		else if (direction == 1)
			return {dat.p + direc[direction] * currH, oChange[dat.o][1]};
		else if (direction == 2)
			return {dat.p + direc[direction] * currL, oChange[dat.o][0]};
		else
			return {dat.p + direc[direction] * currW, oChange[dat.o][1]};
	}
}
bool check(Data dat){
	Point p = dat.p; int currW = addW[dat.o], currL = addL[dat.o];
	Point p2 = {p.x + currW - 1, p.y + currL - 1};
	return (p.x >= 1) 
		&& (p.y >= 1) 
		&& (p2.x <= m) 
		&& (p2.y <= n) 
		&& (get(p.x, p.y, p2.x, p2.y) == 0);
}
// 
bool okay[MAX][MAX][6];
int green[MAX][MAX];
void turnOn(Data dat){
	Point p1 = dat.p; int currW = addW[dat.o], currL = addL[dat.o];
	Point add = {currW, currL};
	Point p2 = p1 + add;
	green[p1.x][p1.y] += 1;
	green[p2.x][p1.y] += -1;
	green[p1.x][p2.y] += -1;
	green[p2.x][p2.y] += 1;
}

queue<Data> q;
void add(Data dat){
	okay[dat.p.x][dat.p.y][dat.o] = true;
	q.push(dat), turnOn(dat);
}
int sub34(){
	init();
	
	add({1, 1, 0});
	while (!q.empty()){
		Data curr = q.front(); q.pop();

		FOR(int, action, DAY, LAT){
			FOR(int, d, 0, 3){
				Data now = change(curr, action, d);
				if (!check(now)) continue;
				if (okay[now.p.x][now.p.y][now.o]) continue;
				add(now);
			}
		}
	}
	
	int answer = 0;
	FOR(int, i, 1, m){
		FOR(int, j, 1, n){
			green[i][j] += green[i - 1][j] + green[i][j - 1] - green[i - 1][j - 1];
			if (green[i][j]) answer++;
		}
	}
	return answer;
}
main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	// #ifndef ONLINE_JUDGE
	freopen("blgame.inp", "r", stdin);
	freopen("blgame.out", "w", stdout);
	// #endif
	//init
	cin >> w >> l >> h >> m >> n >> k;
	FOR(int, i, 1, k){
		int x, y; cin >> x >> y;
		red[x][y] = true;
	}
	FOR(int, i, 1, m)
		FOR(int, j, 1, n)
			red[i][j] += red[i - 1][j] + red[i][j - 1] - red[i - 1][j - 1];
	//=========================
	// if (w == l && l == h) cout << sub12();
	 cout << sub34();
}