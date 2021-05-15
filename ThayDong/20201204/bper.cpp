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

#define MAX 100
#define MOD 1000000007
#define M11 11

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

struct Sub1{
	bool done[MAX] = {};
	int answer = 0;
	void test(int pos, int num){
		if (pos > n){
			answer += !(num % M11);
			return;
		}

		FOR(int, i, 1, n){
			if (done[i]) continue;
			done[i] = true;

			int newProd = num;
			if (i >= 10) newProd *= 100; else newProd *= 10;
			newProd += i; newProd %= M11;
			test(pos + 1, newProd);

			done[i] = false;
		}
	}

	int solve(){
		test(1, 0);
		return answer;
	}

};

struct Sub2{
	int f[1 << 20][11] = {};

	int solve(){
		f[0][0] = 1;
		FOR(int, msk, 0, (1 << n) - 2){
			FOR(int, m, 0, M11 - 1){
				if (!f[msk][m]) continue;
				FOR(int, num, 1, n){
					if (testBit(msk, num - 1)) continue;
					int newMsk = flipBit(msk, num - 1);
					int newNum = m; 
					if (num >= 10) 
						newNum = (newNum * 100 + num) % M11;
					else
						newNum = (newNum * 10 + num) % M11;
					
					f[newMsk][newNum] += f[msk][m];
					f[newMsk][newNum] %= MOD;
				}
			}
		}
		return f[(1 << n) - 1][0];
	}
};

struct Sub3{
	ll f[MAX][M11][MAX] = {};

	bool done[MAX] = {};
	void test(int pos, int num){
		if (pos > 9){
			// cerr << num << '\n';
			f[9][num][5]++;
			return;
		}

		FOR(int, i, 1, 9){
			if (done[i]) continue;
			done[i] = true;

			int newProd = (num * 10 + i) % M11;
			test(pos + 1, newProd);

			done[i] = false;
		}
	}

	int dp(){
		FOR(int, i, 9, n - 1){
			int nxt = i + 1;
			int a = nxt / 10, b = nxt % 10;
			FOR(int, du, 0, M11 - 1){
				FOR(int, odP, 5, i){
					ll add = f[i][du][odP];
					if (!add) continue;

					f[i + 1][(du + a - b + 11) % M11][odP + 1] += add * odP;
					f[i + 1][(du + a - b + 11) % M11][odP + 1] %= MOD;
					
					f[i + 1][(du + b - a + 11) % M11][odP] += add * (i + 1 - odP);
					f[i + 1][(du + b - a + 11) % M11][odP] %= MOD;
				}
			}
		}

		ll ans = 0;
		FOR(int, odp, 5, n)
			ans += f[n][0][odp], ans %= MOD;
		return ans;
	}

	int solve(){
		test(1, 0);
		return dp();
	}
};

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	// #ifndef ONLINE_JUDGE
	// freopen("bper.inp", "r", stdin);
	// freopen("bper.out", "w", stdout);
	// #endif
	cin >> n;
	if (n <= 10){
		Sub1 sub1;
		cout << sub1.solve();
	} else if (n <= 20){
		Sub2 sub2;
		cout << sub2.solve();
	} else {
		Sub3 sub3;
		cout << sub3.solve();
	}
}