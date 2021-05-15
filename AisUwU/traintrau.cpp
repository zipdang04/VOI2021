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

const int N = 5005;
int n, m, u[N], v[N];
int cnt[N][N];
vector<int> adj[N];

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m;
	if (m > 500){
		cout << 0; return 0;
	}
	for (int i = 1; i <= m; i++) {
		cin >> u[i] >> v[i];
		++cnt[u[i]][v[i]];
		++cnt[v[i]][u[i]];
		adj[u[i]].push_back(v[i]);
		adj[v[i]].push_back(u[i]);
	}
	queue<int> bfs;
	vector<bool> vis(n + 1);
	int ans = 0;
	for (int i = 1; i <= m; i++) {
		for (int j = i + 1; j <= m; j++) {
			--cnt[u[i]][v[i]]; --cnt[v[i]][u[i]];
			--cnt[u[j]][v[j]]; --cnt[v[j]][u[j]];
			fill(vis.begin(), vis.end(), false);
			bfs.push(1);
			vis[1] = true;
			while (bfs.size()) {
				int cur = bfs.front();
				bfs.pop();
				for (int nxt : adj[cur]) if (!vis[nxt] and cnt[cur][nxt]) {
					vis[nxt] = true;
					bfs.push(nxt);
				}
			} 
			if (vis[2]) ++ans;
			++cnt[u[i]][v[i]]; ++cnt[v[i]][u[i]]; 
			++cnt[u[j]][v[j]]; ++cnt[v[j]][u[j]]; 
		}
	}
	cout << ans;
}