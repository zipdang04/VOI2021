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

#define MAX 2001
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

ll n, a, b;
ll y[MAX], sum[MAX];

struct Sub1{
	ll ans = INT64_MAX;
	void test(int pos, int cnt, ll num){
		if (pos > n){
			if (a <= cnt && cnt <= b)
				ans = min(ans, num);
			return;
		}
		ll sum = 0;
		FOR(int, i, pos, n){
			sum += y[i];
			test(i + 1, cnt + 1, num | sum);
		}
	}

	Sub1(){
		test(1, 0, 0);
		cout << ans << '\n';
	}
};

struct Sub2{
	struct Data{int pos, group, num;};
	bool occur[51][51][501] = {};

	void bfs(){
		queue<Data> q;
		occur[0][0][0] = true; q.push({0, 0, 0});
		while (!q.empty()){
			Data curr = q.front(); q.pop();
			int currSum = 0;
			FOR(int, i, curr.pos + 1, n){
				currSum += y[i];
				bool &dm = occur[i][curr.group + 1][curr.num | currSum];
				if (dm) continue;
				
				dm = true;
				q.push({i, curr.group + 1, curr.num | currSum});
			}
		}
	}

	Sub2(){
		bfs();
		int ans = INT32_MAX;
		FOR(int, gr, a, b)
			FOR(int, val, 1, 2001){
				if (occur[n][gr][val]) {ans = min(ans, val); break;}
			}
		cout << ans << '\n';
	}
};

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	#ifndef ONLINE_JUDGE
	freopen("bali.inp", "r", stdin);
	freopen("bali.out", "w", stdout);
	#endif
	cin >> n >> a >> b;
	FOR(int, i, 1, n){
		cin >> y[i]; sum[i] = sum[i - 1] + y[i];
	}	

	if (n <= 20){
		Sub1 sub1 = Sub1();
	} else if (n <= 50){
		Sub2 sub2 = Sub2();
	}
}