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

int n;
int dsu[MAX];
int maxi[MAX];

int findRoot(int node){
	if (dsu[node] < 0) return node;
	return dsu[node] = findRoot(dsu[node]);
}
int join(int u, int v){
	if (dsu[u] > dsu[v]) swap(u, v);
	dsu[u] += dsu[v], dsu[v] = u;
	return u;
}

int hard[MAX];
vi graph[MAX];
pii save[MAX];

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	FOR(int, i, 1, n) {
		cin >> hard[i]; 

		dsu[i] = -1;
		maxi[i] = hard[i]; 
		save[i] = {hard[i], i};
	}
	FOR(int, _, 1, n - 1)
	{
		int u, v; cin >> u >> v;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}

	sort(save + 1, save + 1 + n);
	ll answer = 0;
	FOR(int, _, 2, n){
		int node = save[_].se, val = save[_].fi;
		int part = node;
		for (int child: graph[node]){
			if (hard[child] > val) continue;
			int cPart = findRoot(child);
			if (cPart == part) continue;

			answer += maxi[part] + maxi[cPart];
			int same = join(part, cPart); 
			maxi[same] = max(maxi[part], maxi[cPart]);
			part = same;
		}
	}
	cout << answer;
}