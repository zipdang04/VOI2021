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

#define MAX 2001
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

const pii direc[4] = {{1, 1}, {-1, -1}, {1, -1}, {-1, 1}};
pii operator + (pii a, pii b){return {a.fi + b.fi, a.se + b.se};}

#define NO {cout << -1; return 0;}

ll m, n, k, sum, thres;
ll mar[MAX][MAX];

bool check(pii pos){
	if (pos.fi < 1 || pos.se < 1) return false;
	if (pos.fi > m || pos.se > n) return false;
	return true;
}

pair<ll, pll> bfs(pii pos){
	ll visited[m + 1][n + 1] = {};
	FOR(ll, i, 1, m)
		FOR(ll, j, 1, n)
			visited[i][j] = -1;
	queue<pii> q;
	q.push(pos), visited[pos.fi][pos.se] = 0;
	while (!q.empty()){
		pii curr = q.front(); q.pop();
		ll len = visited[curr.fi][curr.se] + 1;
		for (pii d: direc){
			pii now = curr + d;
			
			if (!check(now)) continue;
			if (visited[now.fi][now.se] != -1) continue;
			
			visited[now.fi][now.se] = len;
			q.push(now);
			
			if (mar[now.fi][now.se] > thres)
				return {len, now};
		}
	}
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> m >> n >> k;
	sum = 0;
	FOR(ll, _, 1, k){
		ll x, y, a; cin >> x >> y >> a;
		mar[x][y] += a; sum += a;
	}

	if (sum % (m * n)) NO;
	thres = sum / (m * n);

	ll ans = 0;
	FOR(ll, row, 1, m)
		FOR(ll, col, 1, n){
			// cerr << row << '/' << col << '\n';
			ll &value = mar[row][col];
			if (value >= thres) continue;
			while (value < thres){
				// cerr << "  " << value << ' ' << thres << '\n';
				pair<ll, pll> curr = bfs({row, col});
				ll length = curr.fi; pll pos = curr.se;
				// cerr << "  " << pos.fi << '/' << pos.se << ' ' << length << '\n';

				ll need = thres - value, remain = mar[pos.fi][pos.se] - thres;
				ll choose = min(need, remain);
				
				value += choose, mar[pos.fi][pos.se] -= choose;
				ans += choose * length;
			}
			// cerr << "after bfs:" << '\n';
			// FOR(ll, row, 1, m){FOR(ll, col, 1, n) cerr << mar[row][col] << '|';cerr << '\n';}
		}
	cout << ans << '\n';
}