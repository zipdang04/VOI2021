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

#define MAX 501
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

ll n;
ll mat[MAX][MAX];
ll model[MAX];
ll save[MAX];

void dijkstra(ll *f){
	FOR(ll, i, 1, n) f[i] = INT64_MAX;
	priority_queue<pii, vector<pii>, greater<pii>> pq;
	f[1] = 0; pq.push({0, 1});
	
	while (!pq.empty()){
		pii curr = pq.top(); pq.pop();
		ll cost = curr.fi, node = curr.se;
		if (cost != f[node]) continue;

		FOR(ll, i, 1, n){
			if (i == node) continue;
			if (mat[node][i] == -1) continue;

			ll newCost = cost + mat[node][i];
			if (newCost < f[i]){
				f[i] = newCost;
				pq.push({newCost, i});
			}
		}
	}
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	FOR(ll, i, 1, n)
		FOR(ll, j, 1, n) 
			cin >> mat[i][j];
	
	dijkstra(model);
	ll answer = 0;
	FOR(ll, i, 1, n)
		FOR(ll, j, 1, n){
			if (i == j) continue;
			ll tmp = mat[i][j];
			if (tmp == -1) continue;
			
			mat[i][j] = -1; dijkstra(save);
			ll cnt = 0;
			FOR(ll, i, 1, n){
				cnt += model[i] < save[i];
			}
			answer = max(answer, cnt);

			mat[i][j] = tmp;
		}

	cout << answer << '\n';
}