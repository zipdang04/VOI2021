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

#define MAX 100001
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
vi savePos[MAX];
vi multi[MAX];

ll dsu[MAX];
ll ans = 0;

ll findRoot(ll node){
	if (dsu[node] < 0) return node;
	dsu[node] = findRoot(dsu[node]);
	return dsu[node];
}

void join(ll u, ll v, ll val){
	u = findRoot(u), v = findRoot(v);
	if (u == v) return;
	
	ans += val;
	if (dsu[u] > dsu[v]) swap(u, v);
	dsu[u] += dsu[v]; dsu[v] = u;
}

void init(){
	FOR(ll, i, 1, MAX - 1){
		ll num = 0;
		FOR(ll, j, 1, MAX){
			num += i;
			if (num >= MAX) break;
			multi[i].push_back(i * j);
		}
	}
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	//input && init
	cin >> n;  
	FOR(ll, i, 1, n) {ll num;  cin >> num; savePos[num].push_back(i);}
	
	FOR(ll, i, 1, n) dsu[i] = -1;
	init();
	//=========================
	FORR(ll, div, MAX - 1, 1){
		vi curr;
		for (ll num: multi[div]){
			for (ll pos: savePos[num]){
				curr.push_back(pos);
			}
		}
		if (curr.empty()) continue;
		ll currRoot = curr[0];
		for (ll pos: curr){
			join(pos, currRoot, div);
		}
	}
	cout << 123456ll * (n - 1) - ans;
}