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

#define MAX 300005
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

ll n;
ll a[MAX];
ll stateAns[MAX];
///=======================================================
ll sub1(){
	ll ans = 0;
	ll pivot = a[2]; stateAns[2] = a[2];
	
	if (a[1] >= a[2])
		ans += a[1] - (a[2] - 1),
		stateAns[1] = a[2] - 1;
	else
		stateAns[1] = a[1];

	if (a[3] <= a[2])
		ans += a[2] + 1 - a[3],
		stateAns[3] = a[2] + 1;
	else
		stateAns[3] = a[3];
	return ans;
}
///=======================================================
ll f[305][605];
pll trace[305][605];
ll sub2(){
	FOR(ll, i, 1, 304)
		FOR(ll, j, 0, 604) f[i][j] = INT32_MAX;
	ll value[n + 1]; FOR(ll, i, 1, n) value[i] = a[i] + 301;
	
	FOR(ll, i, 1, n){
		FOR(ll, val, i, 604){
			f[i][val] = abs(val - value[i]) + f[i - 1][val - 1];
			trace[i][val] = {i - 1, val - 1};

			if (f[i][val - 1] < f[i][val])
				f[i][val] = f[i][val - 1], 
				trace[i][val] = {i, val - 1};
		}
	}
	ll answer = f[n][604];
	pii curr = {n, 604};
	while (curr.fi){
		pii nxt = trace[curr.fi][curr.se];
		if (nxt.fi != curr.fi)
			stateAns[curr.fi] = curr.se - 301;
		curr = nxt;
	}
	return f[n][604];
}
///=======================================================
ll dp[3001][3001];
ll midPoint[3001][3001];
#define START -1
#define END -2
ll cal(ll left, ll right){
	if (left > right) return 0;
	ll mini = a[left - 1], maxi = a[right + 1];
	
	ll &ans = dp[left][right];
	ll &posMid = midPoint[left][right];
	if (ans != INT64_MAX) return ans;
	if (left == right) {
		ll value = a[left];
		if (maxi <= value)
			posMid = END, ans = value - (maxi - 1);
		else if (value <= mini)
			posMid = START, ans = (mini + 1) - value;
		else
			posMid = left, ans = 0;
		return ans; 
	}
	
	ll costStart = 0, costEnd = 0;
	FOR(ll, mid, left, right){
		ll x1 = mini + (mid - left + 1), x2 = maxi - (right - mid + 1);
		costStart += abs(x1 - a[mid]), costEnd += abs(x2 - a[mid]);
		if (x1 <= a[mid] && a[mid] <= x2){
			ll cost = cal(left, mid - 1) + cal(mid + 1, right);
			if (cost < ans)
				ans = cost, posMid = mid;
		}
	}
	if (costStart < ans) ans = costStart, posMid = START;
	if (costEnd < ans) ans = costEnd, posMid = END;
	return ans;
}


void make(ll left, ll right){
	if (left > right) return;
	
	ll mid = midPoint[left][right];
	if (mid > 0){
		stateAns[mid] = a[mid];
		make(left, mid - 1), make(mid + 1, right);
	} else if (mid == START){
		ll beep = a[left - 1];
		FOR(ll, i, left, right)
			stateAns[i] = beep + (i - left + 1);
	} else {
		ll beep = a[right + 1];
		FOR(ll, i, left, right)
			stateAns[i] = beep - (right - i + 1);
	}
}

ll sub3(){
	FOR(ll, i, 1, n)
		FOR(ll, j, i, n) dp[i][j] = INT64_MAX;
	a[0] = -1e9, a[n + 1] = 2e9;
	ll answer = cal(1, n);
	make(1, n);
	return answer;
}
main()
{
	// #ifndef ONLINE_JUDGE
	freopen("sequence.inp", "r", stdin);
	freopen("sequence.out", "w", stdout);
	// #endif
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n; ll ma = 0; FOR(ll, i, 1, n) {cin >> a[i]; ma = max(ma, a[i]);}
	// cout << sub3() << '\n'; 
	if (n == 3) cout << sub1() << '\n';
	else if (n <= 300){
		if (ma <= 300) cout << sub2() << '\n';
	} else cout << sub3() << '\n';
	FOR(ll, i, 1, n) {
		cout << stateAns[i] << ' ';
	}
}