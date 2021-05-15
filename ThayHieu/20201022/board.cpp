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

#define MAX 2010
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

struct Point {int x, y;};
struct HCN {Point dl, ur;};

Point operator + (Point a, Point b){return {a.x + b.x, a.y + b.y};}
const Point direc[4] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

int w, h, n;
HCN hcn[MAX];
int table[MAX][MAX] = {};

//for compress
int listX[MAX], listY[MAX];
int lenX, lenY;
mii valX, valY;

void nen(int *list, int &len, mii &val){
	sort(list + 1, list + 1 + len);
	int tmp = 0;
	FOR(int, i, 1, len){
		int curr = list[i];
		if (val[curr] == 0)
			val[curr] = ++tmp;
	}
}

bool check(Point p){
	if (p.x < 1 || p.x > w) return false;
	if (p.y < 1 || p.y > h) return false;
	return true;
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> w >> h >> n;
	FOR(int, i, 1, n){
		int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
		x1++, y1++, x2++, y2++;
		
		hcn[i] = {{x1, y1}, {x2, y2}};
		listX[++lenX] = x1; listX[++lenX] = x2;
		listY[++lenY] = y1; listY[++lenY] = y2;
	}
	
	listX[++lenX] = 1; listY[++lenY] = 1;
	listX[++lenX] = w; listY[++lenY] = h;
	nen(listX, lenX, valX); nen(listY, lenY, valY);
	w = valX[w], h = valY[h];
	FOR(int, i, 1, n)
		hcn[i].dl.x = valX[hcn[i].dl.x],
		hcn[i].ur.x = valX[hcn[i].ur.x],
		hcn[i].dl.y = valY[hcn[i].dl.y],
		hcn[i].ur.y = valY[hcn[i].ur.y];
	
	FOR(int, i, 1, n){
		int x1 = hcn[i].dl.x, x2 = hcn[i].ur.x;
		int y1 = hcn[i].dl.y, y2 = hcn[i].ur.y;
		table[x1][y1] += 1;
		table[x1][y2] += -1;	
		table[x2][y1] += -1;
		table[x2][y2] += 1;
	}

	FOR(int, i, 1, w)
		FOR(int, j, 1, h)
			table[i][j] += table[i - 1][j] + table[i][j - 1] - table[i - 1][j - 1];

	int ans = 0;
	FOR(int, i, 1, w)
		FOR(int, j, 1, h){
			if (table[i][j]) continue;
			ans++; queue<Point> q;
			table[i][j] = -1; q.push({i, j});

			while (!q.empty()){
				Point curr = q.front(); q.pop();

				for (Point d: direc){
					Point now = curr + d;
					if (!check(now)) continue;
					if (table[now.x][now.y]) continue;
					
					table[now.x][now.y] = -1; q.push(now);
				}
			}
		}
	cout << ans;
}