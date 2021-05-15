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

pii operator + (pii a, pii b){return {a.fi + b.fi, a.se + b.se};}
const pii direc[4] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

int invade[MAX][MAX];
int r, c, n;
queue<pii> q;

bool check(pii p){
	return p.fi >= 1 && p.fi <= r && p.se >= 1 && p.se <= c;
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	#ifndef HIEU
	freopen("nazi.inp", "r", stdin);
	freopen("nazi.out", "w", stdout);
	#endif
	cin >> r >> c >> n;
	FOR(int, _, 1, n){
		int x, y; cin >> x >> y;
		invade[x][y] = 1; q.push({x, y});
	}

	int ans = 1;
	while (!q.empty()){
		pii curr = q.front(); q.pop();
		int val = invade[curr.fi][curr.se];
		
		for (pii d: direc){
			pii now = curr + d;
			if (!check(now)) continue;
			if (invade[now.fi][now.se]) continue;

			invade[now.fi][now.se] = val + 1; q.push(now); 
			ans = max(ans, val + 1);
		}
	}
	cout << ans;
}