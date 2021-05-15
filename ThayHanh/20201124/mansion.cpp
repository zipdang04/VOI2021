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

#define MAX 1000001
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
int m, n, k;
vector<pii> nodeX[MAX], nodeY[MAX];
vi vert[MAX], hori[MAX];
#define VERT true
#define HORI false
int f[MAX][2];
main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> m >> n >> k;
	FOR(int, i, 1, k){
		int x, y; cin >> x >> y;
		nodeX[x].push_back({y, i});
		nodeY[y].push_back({x, i});
	}
	nodeX[1].push_back({1, 0});
	nodeX[m].push_back({n, k + 1});
	nodeY[n].push_back({m, k + 1});
	cerr << k + 1 << '\n';
	FOR(int, i, 1, 100000){
		sort(nodeX[i].begin(), nodeX[i].end());
		sort(nodeY[i].begin(), nodeY[i].end());
		int sizeX = nodeX[i].size();
		FOR(int, j, 1, sizeX - 1){
			int u = nodeX[i][j].se, v = nodeX[i][j - 1].se;
			cerr << u << '.' << v << '\n';
			vert[u].push_back(v),
			vert[v].push_back(u);
		}
		int sizeY = nodeY[i].size();
		FOR(int, j, 1, sizeY - 1){
			int u = nodeY[i][j].se, v = nodeY[i][j - 1].se;
			cerr << u << '_' << v << '\n';
			hori[u].push_back(v),
			hori[v].push_back(u);
		}
	}

	queue<pii> q;
	f[0][VERT] = 1; q.push({0, VERT});
	while (!q.empty()){
		pii curr = q.front(); q.pop();
		int currVal = f[curr.fi][curr.se];
		cerr << curr.fi << '/' << curr.se << ' ' << currVal << '\n';

		if (curr.fi && !f[curr.fi][!curr.se])
			f[curr.fi][!curr.se] = currVal + 1,
			q.push({curr.fi, !curr.se});
		
		if (curr.se == VERT){
			for (int child: vert[curr.fi]){
				if (f[child][VERT]) continue;
				f[child][VERT] = currVal + 1;
				q.push({child, VERT});
			}
		} else {
			for (int child: hori[curr.fi]){
				if (f[child][HORI]) continue;
				f[child][HORI] = currVal + 1;
				q.push({child, HORI});
			}

		}
	}
	int ans = INT32_MAX;
	if (f[k + 1][VERT])
		ans = min(ans, f[k + 1][VERT] - 1);
	if (f[k + 1][HORI])
		ans = min(ans, f[k + 1][HORI] - 1);
	if (ans == INT32_MAX)
		ans = -1;
	cout << ans;
}