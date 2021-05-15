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
typedef pair<bool, bool> pbb;
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

#define testBit(n, bit) ((n >> bit) & 1)
#define flipBit(n, bit) (n ^ (1ll << bit))
#define cntBit(n) __builtin_popcount(n)
#define cntBitll(n) __builtin_popcountll(n)
#define randomize mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count());

#define HORI true
#define VERT false

struct Point{
	int x = 0, y = 0;
	Point(){x = y = 0;}
	Point(int _x, int _y){x = _x, y = _y;}
};
const Point direction[4] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
Point operator + (Point a, Point b){return {a.x + b.x, a.y + b.y};}

int n;
bool grid[MAX][MAX];
Point start, finish;

int forw[MAX][MAX][2][2]; //x, y, hori/vert, flag
bool visF[MAX][MAX][2][2]; 
int back[MAX][MAX][2]; //w/o flag
bool visB[MAX][MAX][2]; 

typedef pair<Point, pbb> Data;
deque<Data> dq;

bool check(Point &p){
	if (p.x < 1 || p.y < 1 || p.x > n || p.y > n) return false;
	return true;
}

#define getF(arr, pos, hv, flag) arr[pos.x][pos.y][hv][flag]
#define addF(pos, hv, flag, val) getF(forw, pos, hv, flag) = val, dq.push_front({pos, {hv, flag}})
#define addB(pos, hv, flag, val) getF(forw, pos, hv, flag) = val, dq.push_back({pos, {hv, flag}})
void bfsForward(){
	addF(start, HORI, false, 0);
	addF(start, VERT, false, 0);
	while (!dq.empty()){
		Data curr = dq.front(); dq.pop_front();
		Point currPos = curr.fi; bool isHori = curr.se.fi, crossed = curr.se.se;
		
		if (getF(visF, currPos, isHori, crossed)) continue;
		getF(visF, currPos, isHori, crossed) = true;
		int currValue = getF(forw, currPos, isHori, crossed);
		
		FOR(int, i, 0, 3){
			Point nowPos = currPos + direction[i];
			if (!check(nowPos)) continue;

			bool nowHori = i & 1;

			bool nowCross = grid[nowPos.x][nowPos.y];
			if (crossed && nowCross) continue;
			nowCross |= crossed;
			
			bool tmp = isHori ^ nowHori;
			int nowValue = currValue + tmp;
			if (nowValue < getF(forw, nowPos, nowHori, nowCross)){
				if (grid[nowPos.x][nowPos.y] && nowValue < getF(forw, nowPos, nowHori, false)){
					getF(forw, nowPos, nowHori, false) = nowValue;
				}
				if (!tmp) 
					addF(nowPos, nowHori, nowCross, nowValue);
				else 
					addB(nowPos, nowHori, nowCross, nowValue);
			}
		}
	}
}

#define getB(arr, pos, hv) arr[pos.x][pos.y][hv]
#define addf(pos, hv, val) getB(back, pos, hv) = val, dq.push_front({pos, {hv, false}})
#define addb(pos, hv, val) getB(back, pos, hv) = val, dq.push_back({pos, {hv, false}})
void bfsBackward(){
	addf(finish, HORI, 0);
	addf(finish, VERT, 0);
	while (!dq.empty()){
		Data curr = dq.front(); dq.pop_front();
		Point currPos = curr.fi; bool isHori = curr.se.fi;
		
		if (getB(visB, currPos, isHori)) continue;
		getB(visB, currPos, isHori) = true;
		int currValue = getB(back, currPos, isHori);
		// cerr << currPos.x << '/' << currPos.y << ' ' << isHori << '=' << currValue << '\n';
		
		FOR(int, i, 0, 3){
			Point nowPos = currPos + direction[i];
			if (!check(nowPos)) continue;

			bool nowHori = i & 1;
			
			// cerr << "///" << nowPos.x << '/' << nowPos.y << ' ' << isHori << '=' << currValue << '\n';
			bool tmp = isHori ^ nowHori;
			int nowValue = currValue + tmp;
			if (nowValue < getB(back, nowPos, nowHori)){
				getB(back, nowPos, nowHori) = nowValue;
				if (!grid[nowPos.x][nowPos.y]){
					if (!tmp) 
						dq.push_front({nowPos, {nowHori, nowValue}});
					else 
						dq.push_back({nowPos, {nowHori, nowValue}});
				}
			}
		}
	}
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	#ifndef ONLINE_JUDGE
	freopen("robot.inp", "r", stdin);
	freopen("robot.out", "w", stdout);
	#endif
	cin >> n;
	FOR(int, i, 1, n) FOR(int, j, 1, n) cin >> grid[i][j];
	cin >> start.x >> start.y >> finish.x >> finish.y;

	FOR(int, i, 1, n) FOR(int, j, 1, n) 
		forw[i][j][0][0] = forw[i][j][0][1] 
		= forw[i][j][1][0] = forw[i][j][1][1] 
		= back[i][j][0] = back[i][j][1] = INT32_MAX;

	bfsForward();
	bfsBackward();
	int ans1 = min(getF(forw, finish, HORI, false), getF(forw, finish, VERT, false));
	int ans2 = ans1, ans3 = 0;
	int cntSharp = 0;
	FOR(int, i, 1, n)
		FOR(int, j, 1, n){
			if (!grid[i][j]) continue;
			cntSharp++;
			bool okie = false;
			// cerr << i << ' ' << j << '\n';
			FOR(int, i1, 0, 1){
				FOR(int, j1, 0, 1){
					if (forw[i][j][i1][true] == INT32_MAX) continue;
					if (back[i][j][j1] == INT32_MAX) continue;
					// cerr << "//" << i1 << '|' << j1 << ' ' << forw[i][j][i1][true] << '&' << back[i][j][j1] << '=' << forw[i][j][i1][true] + back[i][j][j1] + (i1 ^ j1) << '\n';
					int val = forw[i][j][i1][true] + back[i][j][j1] + (i1 ^ j1);
					if (val < ans2) okie = true, ans2 = val, ans3 = 1;
					else if (val == ans2 && !okie) ans3++, okie = true;
				}
			}
			// cerr << "------\n";
		}
	if (ans1 == ans2) ans3 = cntSharp;
	cout << ans1 << ' ' << ans2 << ' ' << ans3;
}