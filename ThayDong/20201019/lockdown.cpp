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

#define MAX 505
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

const ll oo = ll(1e17);

ll n;
ll mat[MAX][MAX];
ll best[MAX];
ll curr[MAX];

void Dijkstra(ll *arr){
	FOR(ll, i, 1, n) arr[i] = oo;
	priority_queue<pll, vector<pll>, greater<pll>> pq;
	arr[1] = 0; pq.push(pll(0, 1));
	while (!pq.empty()){
		pll curr = pq.top(); pq.pop();
		ll currVal = curr.fi, node = curr.se;
		if (currVal > arr[node]) continue;

		FOR(ll, child, 1, n){
			if (node == child) continue;
			if (mat[node][child] == -1) continue;
			ll newVal = currVal + mat[node][child];
			if (arr[child] > newVal)
				arr[child] = newVal, pq.push(pll(newVal, child));
		}
	}
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n; FOR(ll, i, 1, n) FOR(ll, j, 1, n) cin >> mat[i][j];
	Dijkstra(best);
	
	ll ans = 0;
	FOR(ll, node, 2, n){
		ll nodeAff = 0; bool okay = true;

		FOR(ll, i, 1, n){
			if (i == node) continue;
			if (mat[i][node] == -1) continue;
			if (best[i] + mat[i][node] == best[node]){
				if (nodeAff){okay = false; break;}
				nodeAff = i;
			}
		}
		if (!okay) continue;
		if (!nodeAff) continue;
	
		ll tmp = mat[nodeAff][node]; mat[nodeAff][node] = -1; 
		Dijkstra(curr);
		mat[nodeAff][node] = tmp; 
		
		ll cnt = 0;
		FOR(ll, i, 1, n) cnt += best[i] != curr[i];
		// cerr << nodeAff << ' ' << node << ' ' << done << '\n';
		
		ans = max(ans, cnt);
	}
	cout << ans;
}