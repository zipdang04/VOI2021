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
typedef pair<pii, bool> State;

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

#define MAX 305
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

const pii mov[2] = {{0, 1}, {1, 0}};
pii operator + (pii a, pii b){return {a.fi + b.fi, a.se + b.se};}
pii operator - (pii a, pii b){return {a.fi - b.fi, a.se - b.se};}

int n, m;
char road[MAX][MAX];
bool poss[MAX][MAX][2]; // = possible
int none[MAX][MAX][2];

#define HORI false
#define VERT true

void init(){
	// horizontal - 0
	FOR(int, i, 1, n){
		int tmp = 0;
		FORR(int, j, m, 1){
			if (road[i][j] == '#') tmp = 0;
			else tmp++;
			none[i][j][HORI] = tmp;
		}
	}
	// vertical - 1
	FOR(int, j, 1, m){
		int tmp = 0;
		FORR(int, i, n, 1){
			if (road[i][j] == '#') tmp = 0;
			else tmp++;
			none[i][j][VERT] = tmp;
		}
	}
}

bool check(pii a){
	if (a.fi < 1 || a.se < 1) return false;
	if (a.fi > n || a.se > m) return false;
	return true;
}
#define recog(position, type) poss[position.fi][position.se][type] = true, q.push({position, type})
#define condi(position, type) (check(position) && !poss[position.fi][position.se][type] && none[position.fi][position.se][type] >= bambooLen)
bool bfs(int bambooLen){
	memset(poss, false, sizeof(poss));
	queue<State> q;
	FOR(int, i, 1, n)
		if (none[i][1][VERT] >= bambooLen)
			poss[i][1][VERT] = true, q.push({{i, 1}, VERT});
	while (!q.empty()){
		State curr = q.front(); q.pop();
		pii pos = curr.fi;
		if (curr.se == HORI){
			//no change in direction
			pii pos1 = pos + mov[HORI];
			pii pos2 = pos - mov[HORI];
			if (condi(pos1, HORI)) recog(pos1, HORI);
			if (condi(pos2, HORI)) recog(pos2, HORI);
			// change
			pos1 = pos, pos2 = {pos.fi - bambooLen + 1, pos.se};
			if (condi(pos1, VERT)) recog(pos1, VERT);
			if (condi(pos2, VERT)) recog(pos2, VERT);
			pos1.se += bambooLen - 1, pos2.se += bambooLen - 1;
			if (condi(pos1, VERT)) recog(pos1, VERT);
			if (condi(pos2, VERT)) recog(pos2, VERT);
		} else {
			//no change in direction
			pii pos1 = pos + mov[VERT];
			pii pos2 = pos - mov[VERT];
			if (condi(pos1, VERT)) recog(pos1, VERT);
			if (condi(pos2, VERT)) recog(pos2, VERT);
			// change
			pos1 = pos, pos2 = {pos.fi, pos.se - bambooLen + 1};
			if (condi(pos1, HORI)) recog(pos1, HORI);
			if (condi(pos2, HORI)) recog(pos2, HORI);
			pos1.fi += bambooLen - 1, pos2.fi += bambooLen - 1;
			if (condi(pos1, HORI)) recog(pos1, HORI);
			if (condi(pos2, HORI)) recog(pos2, VERT);
		}
	}
	FOR(int, i, 1, n)
		if (poss[i][m][VERT]) return true;
	return false;
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m;
	FOR(int, i, 1, n) cin >> road[i] + 1;
	init();

	int l = 1, r = min(n, m), ans = 0;
	while (l <= r){
		int mid = (l + r) >> 1;
		if (bfs(mid)) ans = mid, l = mid + 1;
		else r = mid - 1;
	}
	cout << ans << '\n';
}