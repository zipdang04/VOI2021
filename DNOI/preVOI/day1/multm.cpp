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

#define MAX 200001
#define MOD 1000000007

#define fi first
#define se second
#define pf push_front
#define pb push_back

#define FOR(type, i, a, b) for(type i = (a); i <= (b); i++)
#define FORR(type, i, b, a) for(type i = (b); i >= (a); i--)

#define testBit(n, bit) ((n >> bit) & 1)
#define flipBit(n, bit) ((n) ^ (1ll << (bit)))
#define cntBit(n) __builtin_popcount(n)
#define cntBitll(n) __builtin_popcountll(n)
#define randomize mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count());

ll n, P;
ll a[MAX];

ll sub1(){
	mll save;
	FOR(ll, i, 1, n)
		save[a[i]]++;
	return save.size();
}

ll sub2(){
	ll cnt[21] = {};
	FOR(ll, i, 1, n)
		cnt[a[i]]++;
	
	ll answer = 0;
	FOR(ll, _, 1, (1 << 20) - 1){
		ll mask = _ << 1;
		//checkMask
		bool valid = true;
		FOR(ll, i, 1, 20 / P)
			if (testBit(mask, i) && testBit(mask, (i * P))){
				valid = false; break;
			}
		if (!valid) continue;
		//=========================
		ll curr = 0;
		FOR(ll, i, 1, 20)
			if (testBit(mask, i))
				curr += cnt[i];
		answer = max(answer, curr);
	}
	return answer;
}

mll save; 
ll value[MAX], cnt[MAX];
bool visited[MAX];
ll arr[MAX], f[MAX], len = 0;
void init(){
	FOR(ll, i, 1, n)
		save[a[i]]++;
	n = 0;
	for (pii i: save){
		n++;
		value[n] = i.fi, cnt[n] = i.se;
	}
}
ll find(ll num){
	ll left = 1, right = n;
	while (left <= right){
		ll mid = (left + right) >> 1;
		ll curr = value[mid];
		if (curr == num)
			return mid;
		else if (curr < num)
			left = mid + 1;
		else
			right = mid - 1;
	}
	return 0;
}
ll qhd(){
	f[1] = arr[1];
	FOR(ll, i, 2, len)
		f[i] = max(f[i - 1], arr[i] + f[i - 2]);
	return f[len];
}
ll sub3(){
	init();
	ll ans = 0;
	FORR(ll, i, n, 1){
		if (visited[i]) continue;
		ll currVal = value[i];
		while (currVal){
			ll pos = find(currVal);
			if (pos == -1) break;
			
			visited[pos] = true;
			arr[++len] = cnt[pos];

			if (currVal % P) break;
			currVal /= P;
		}
		ans += qhd(); len = 0;
	}
	return ans;
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	// #ifndef ONLINE_JUDGE
	// freopen("multm.inp", "r", stdin);
	// freopen("multm.out", "w", stdout);
	// #endif
	//input
	cin >> n >> P;
	FOR(ll, i, 1, n) cin >> a[i];
	//=========================
	//get sub
	if (P == 1) cout << sub1();
	else {
		bool isSub2 = P <= 20;
		FOR(ll, i, 1, n)
			if (a[i] > 20) isSub2 = false;

		if (isSub2) cout << sub2();
		else cout << sub3();
	}
	//=========================
}