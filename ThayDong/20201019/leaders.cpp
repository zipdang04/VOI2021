#pragma GCC optimize("Ofast")  
#pragma GCC target("avx,avx2,fma")
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

#define testBit(n, bit) ((n >> bit) & 1)
#define flipBit(n, bit) (n ^ (1ll << bit))
#define cntBit(n) __builtin_popcount(n)
#define cntBitll(n) __builtin_popcountll(n)
#define randomize mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count());

ll n, m;
vl group[MAX];
ll quantity[MAX];
ll sum[MAX];
ll ans = INT64_MAX;

ll captain[MAX], cSum = 0;
bool check(){
	ll tmp1[MAX], tmp2[MAX];
	FOR(ll, i, 1, m)
		tmp1[i] = sum[i], tmp2[i] = captain[i];
	sort(tmp1 + 1, tmp1 + 1 + m);
	sort(tmp2 + 1, tmp2 + 1 + m);
	FOR(ll, i, 1, m)
		if (tmp1[i] > tmp2[i]) return false;
	return true;
}

void dqql(ll pos){
	if (pos > m){
		if (check())
			ans = min(ans, cSum);
		return;
	}
	FOR(ll, i, 0, quantity[pos] - 1){
		sum[pos] -= group[pos][i];
		captain[pos] = group[pos][i];
		cSum += captain[pos];
		dqql(pos + 1);
		cSum -= captain[pos];
		sum[pos] += group[pos][i];
	}
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> m >> n;
	FOR(ll, i, 1, m){
		cin >> quantity[i];
		FOR(ll, j, 1, quantity[i]){
			ll num; cin >> num;
			sum[i] += num; group[i].push_back(num);
		}
	}
	dqql(1);
	if (ans == INT64_MAX) ans = -1;
	cout << ans;
}