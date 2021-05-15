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

/*
struct Node
{
	int node, len;
	Node() {node = len = 0;}
	Node(int node, int len) {this -> node = node, this -> len = len;}
};
typedef vector<Node> vg;
*/

#define MAX 100005
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

ll n, m;
ll a[MAX];
ll hold[MAX];
ll choose[MAX], len = 0;

void make(){
	ll highCol = 1;
	FOR(ll, i, 2, n)
		if (a[i] > a[highCol]) highCol = i;
	
	stack<ll> st;
	st.push(highCol);
	FOR(ll, i, highCol + 1, n){
		ll num = a[i];
		while (num > a[st.top()]) st.pop();
		st.push(i);
	}
	while (st.size() > 1)
		choose[++len] = st.top(), st.pop();
	
	FORR(ll, i, highCol - 1, 1){
		ll num = a[i];
		while (num > a[st.top()]) st.pop();
		st.push(i);
	}
	while (!st.empty())
		choose[++len] = st.top(), st.pop();
	
	sort(choose + 1, choose + len + 1);
}

void drop(){
	FOR(ll, i, 1, len - 1){
		ll left = choose[i], right = choose[i + 1];
		ll maxWater = min(a[left], a[right]);
		FOR(ll, pos, left + 1, right - 1)
			hold[pos] = maxWater - a[pos];
	}
	// FOR(ll, i, 1, n) cerr << a[i] << ' '; cerr << '\n';
	// // FOR(ll, i, 1, n) cerr << hold[i] << ' '; cerr << '\n';
}

bool check(ll h){
	ll water = 0;
	FOR(ll, i, 1, n)
		if (!hold[i]) continue;
		else if (a[i] < h)
			water += max(0ll, a[i] + hold[i] - h);
		else
			water += hold[i];
	// cerr << h << ' ' << water << '\n';
	return water >= m;
}

ll bs(){
	ll left = 1, right = 2000000000, ans = -1;
	while (left <= right){
		ll mid = (left + right) >> 1;
		if (check(mid)) ans = mid, left = mid + 1;
		else right = mid - 1;
	}
	return ans;
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m;
	FOR(ll, i, 1, n) cin >> a[i];
	make(); drop();
	cout << bs();
}