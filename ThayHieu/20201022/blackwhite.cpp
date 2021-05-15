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

#define MAX 100003

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

const ll amount = 4;
const ll bas = 2;

randomize;
const ll MOD[5] = {1000000007, 1000002277, 1000005277, 1000008277, 1000004119};
struct Hash{ll hash[bas][amount] = {};};
bool operator < (Hash a, Hash b){
	FOR(ll, tmp, 0, bas - 1)
		FOR(ll, _, 0, amount - 1){
			if (a.hash[tmp][_] < b.hash[tmp][_]) return true;
			if (a.hash[tmp][_] > b.hash[tmp][_]) return false;
		}
	return false;
}

ll n, t; string dummy;
ll state[MAX];
ll base[bas][MAX];
map<Hash, bool> check;
Hash curr;
set<pll> s;

void createBase(){
	FOR(ll, _, 0, bas - 1)
		FOR(ll, i, 1, n + 2)
			base[_][i] = mt() % 500000000 + 500000000;
}

void createHash(){
	FOR(ll, b, 0, bas - 1){
		FOR(ll, _, 0, amount - 1){
			curr.hash[b][_] = 0;
			FOR(ll, i, 1, n + 2)
				curr.hash[b][_] += (state[i] * base[b][i]) % MOD[_], curr.hash[b][_] %= MOD[_];
		}
	}
}

void del(ll pos){
	FOR(ll, b, 0, bas - 1)
		FOR(ll, _, 0, amount - 1)
			curr.hash[b][_] += MOD[_] - (state[pos] * base[b][pos]) % MOD[_], curr.hash[b][_] %= MOD[_];
}

void add(ll pos){
	FOR(ll, b, 0, bas - 1)
		FOR(ll, _, 0, amount - 1)
			curr.hash[b][_] += (state[pos] * base[b][pos]) % MOD[_], curr.hash[b][_] %= MOD[_];
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	//input
	cin >> n >> t >> dummy;
	if (dummy == "black"){
		n++;
		FOR(ll, i, 2, n) cin >> state[i];
	} else 
		FOR(ll, i, 1, n) cin >> state[i];
	if (n & 1) n++;
	//=========================
	
	createBase();
	createHash();
	check[curr] = true;
	FOR(ll, i, 1, n)
		s.insert({state[i], -i});

	ll currTime = 0;
	while (currTime < t){
		currTime++;

		pll dat = *s.rbegin();
		ll value = dat.fi, p1 = -dat.se, p2;
		if (p1 & 1) p2 = p1 + 1; else p2 = p1 - 1;
		ll valueR = state[p2];
		
		del(p1), del(p2);
		s.erase({state[p1], -p1});
		s.erase({state[p2], -p2});

		ll tmp = value / 2;
		state[p1] -= tmp, state[p2] += tmp;
		
		add(p1), add(p2);
		s.insert({state[p1], -p1});
		s.insert({state[p2], -p2});
		
		if (check[curr]) break;
		else check[curr] = true;
	}
	cout << currTime;
	
}