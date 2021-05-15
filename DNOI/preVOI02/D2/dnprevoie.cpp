#include <bits/stdc++.h>
using namespace std;
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<ll, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
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

// /*
struct Node
{
	int node, idx, b, l;
	Node() {node = idx = b = l = 0;}
	Node(int node, int idx, int b, int l) {
		this -> node = node, 
		this -> idx = idx, 
		this -> b = b;
		this -> l = l;
	}
};
typedef vector<Node> vg;
// */

#define MAX 500005
#define MOD 998244353

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

ll theta, n, m;
vg fow[MAX], bak[MAX];

//========================sub 1 + 2======================================
vi graph[MAX];
ll f[MAX];
void makeGraph(){
	FOR(ll, node, 1, n)
		for (Node c1: bak[node])
			for (Node c2: fow[node]){
				if (c1.b >= c2.b || c1.l >= c2.l) continue;
				graph[c1.idx].push_back(c2.idx);
			}
}
ll dp(ll node){
	ll &ans = f[node];
	if (ans != -1) return f[node];
	
	ans = 0;
	for (ll child: graph[node]){
		ans += dp(child) + 1;
		ans %= MOD;
	}
	return ans;
}
void sub12(){
	makeGraph();
	FOR(ll, i, 1, m) f[i] = -1;
	ll answer = m;
	FOR(ll, i, 1, m){
		answer += dp(i);
		answer %= MOD;
	}
	cout << answer;
}
//=======================================================================
//=======================================================================
//=======================================================================
//========================sub 5==========================================
//=========================init graph//
struct Edge{
	ll from, to, b, l;
	Edge() {from = to = b = l = 0;}
	Edge(ll from, ll to, ll b, ll l) {
		this -> from = from, 
		this -> to = to, 
		this -> b = b;
		this -> l = l;
	}
};
bool cmp(Edge a, Edge b){
	if (a.b < b.b) return true;
	if (a.b > b.b) return false;
	return a.l < b.l;
}

Edge edgeList[MAX];
set<ll> save[MAX];
vi valList[MAX];
vi bit[MAX];
void init(){
	ll tmp = 0;
	FOR(ll, node, 1, n)
		for (Node child: fow[node]){
			edgeList[++tmp] = {node, child.node, child.b, child.l};
			save[child.node].insert(child.l);
		}
	sort(edgeList + 1, edgeList + 1 + m, cmp);
	FOR(ll, node, 1, n) {
		valList[node].push_back(0);
		valList[node].insert(valList[node].end(), save[node].begin(), save[node].end());
		bit[node] = vi(valList[node].size(), 0);
	}
}
//=========================BIT//
void update(ll node, ll pos, ll val){
	ll ind = ll(upper_bound(valList[node].begin(), valList[node].end(), pos) - valList[node].begin()) - 1;
	ll sz = bit[node].size();
	while (ind < sz)
		bit[node][ind] += val,
		bit[node][ind] %= MOD,
		ind += ind & -ind;
}
ll get(ll node, ll pos){
	ll ind = ll(upper_bound(valList[node].begin(), valList[node].end(), pos) - valList[node].begin()) - 1;
	ll ans = 0;
	while (ind){
		ans += bit[node][ind],
		ind -= ind & -ind;
	}
	return ans % MOD;
}
//=========================main//
stack<pair<pii, ll>> st; // buffer
void flushStack(){
	while (!st.empty()){
		pair<pii, ll> curr = st.top(); st.pop();
		ll node = curr.fi.fi, currL = curr.fi.se; ll val = curr.se;
		update(node, currL, val);
	}
}
void sub5(){
	init();
	Edge prev = {0, 0, 0, 0};
	ll answer = 0;
	FOR(ll, _, 1, m){
		Edge curr = edgeList[_];
		if (curr.b != prev.b) flushStack();
		prev = curr;

		ll currGet = get(curr.from, curr.l - 1);
		ll currAns = currGet + 1;
		answer += currAns; answer %= MOD;
		st.push({{curr.to, curr.l}, currAns});
	}
	cout << answer << '\n';
}
//=======================================================================

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> theta >> n >> m;
	FOR(ll, _, 1, m){
		ll u, v, b, l; cin >> u >> v >> b >> l;
		fow[u].push_back({v, _, b, l});
		bak[v].push_back({u, _, b, l});
	}

	if (theta <= 2) sub12();
	else sub5();

}