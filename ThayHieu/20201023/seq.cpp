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
ll a[MAX];
ll app[MAX], cnt = 0;

void nen(){
	pii save[n + 1];
	FOR(ll, i, 1, n)
		save[i] = {a[i], i};
	sort(save + 1, save + 1 + n);
	ll tmp = 0;
	FOR(ll, i, 1, n){
		if (i == 1 || save[i].fi != save[i - 1].fi) tmp++;
		a[save[i].se] = tmp;
	}
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m; FOR(ll, i, 1, n) cin >> a[i]; nen();
		
	ll left = 1, ans = 1;
	FOR(ll, i, 1, n){
		ll num = a[i];
		if (!app[num]) cnt++; app[num]++;
		while (cnt > m){
			ll tmp = a[left]; left++;
			app[num]--; if (!app[num]) cnt--;
		}
		ans = max(ans, i - left + 1);
	}
	cout << ans;
}