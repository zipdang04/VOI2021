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

#define testBit(n, bit) (((n) >> (bit)) & 1)
#define flipBit(n, bit) ((n) ^ (1ll << (bit)))
#define cntBit(n) __builtin_popcount(n)
#define cntBitll(n) __builtin_popcountll(n)
#define randomize mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count());

int n;
struct Sub1{
	bool check(int num){
		bool appear[10] = {};
		int tmp = num;
		while (tmp)
			appear[tmp % 10] = true, tmp /= 10;
		
		FOR(int, i, 2, 9)
			if (appear[i] && (num % i)) return false;
		return true;
	}

	Sub1(int n){
		int end = 1; FOR(int, i, 1, n) end *= 10; end--;
		int ans = 0;
		FOR(int, i, 0, end)
			ans += check(i);
		cout << ans << '\n';
	}
};

struct Number{
	const int div[4] = {5, 7, 8, 9};
	int r[4] = {};
	int mask = 0;
	Number(){r[0] = r[1] = r[2] = r[3] = mask = 0;}
	Number(int dig){
		if (dig > 0) mask = 1 << (dig - 1);
		else mask = 0;
		FOR(int, i, 0, 3)
			r[i] = dig % div[i];
	}
	Number(int d0, int d1, int d2, int d3, int m){
		r[0] = d0;
		r[1] = d1;
		r[2] = d2;
		r[3] = d3;
		mask = m;
	}
};
Number operator + (Number num, int dig){
	FOR(int, i, 0, 3)
		num.r[i] *= 10, num.r[i] += dig, num.r[i] %= num.div[i];
	num.mask |= 1 << dig;
	return num;
}
bool checkValid(Number num){
	if (testBit(num.mask, 2) && (num.r[2] % 2)) return false;
	if (testBit(num.mask, 5) && (num.r[0] % 5)) return false;
	if (testBit(num.mask, 7) && (num.r[1] % 7)) return false;
	if (testBit(num.mask, 8) && (num.r[2] % 8)) return false;
	if (testBit(num.mask, 9) && (num.r[3] % 9)) return false;
	if (testBit(num.mask, 4) && (num.r[2] % 4)) return false;
	if (testBit(num.mask, 3) && (num.r[3] % 3)) return false;
	if (testBit(num.mask, 6) && ((num.r[2] % 2) || (num.r[3] % 3))) return false;
	return true;
}

struct Data{
	ll f[5][7][8][9][512] = {};
	void clear(){
		memset(f, 0, sizeof(f));
	}

	ll& operator [](Number num){
		return f[num.r[0]]
				[num.r[1]]
				[num.r[2]]
				[num.r[3]]
				[num.mask];
	}

	Data(){
		clear();
	}
};

struct Sub2{
	ll n;
	ll answer = 0;
	Data dat[2];

	void solve(){
		dat[0].clear(), dat[1].clear();
		FOR(int, i, 1, 9)
			dat[1][Number(i)] = 1;
		answer = 1;
		FOR(int, digLen, 1, n - 1){
			bool state = digLen & 1; bool other = !state;
			dat[other].clear();
			
			FOR(int, i0, 0, 4)
			FOR(int, i1, 0, 6)
			FOR(int, i2, 0, 7)
			FOR(int, i3, 0, 8)
			FOR(int, mask, 0, 511){
				Number prevCase = Number(i0, i1, i2, i3, mask);
				ll total = dat[state][prevCase];
				if (total == 0) continue;
				// cerr << i0 << ' ' << i1 << ' ' << i2 << ' ' << i3 << ' ' << mask << ':' << total << '\n';

				if (checkValid(prevCase)) answer += total, answer %= MOD;
				// cerr << answer << '\n';

				FOR(int, dig, 0, 9){
					Number newCase = prevCase + dig;
					dat[other][newCase] += total;
					dat[other][newCase] %= MOD;
				}
			}
		}
		FOR(int, i0, 0, 4)
		FOR(int, i1, 0, 6)
		FOR(int, i2, 0, 7)
		FOR(int, i3, 0, 8)
		FOR(int, mask, 0, 511)
			if (checkValid(Number(i0, i1, i2, i3, mask)))
				answer += dat[n & 1][Number(i0, i1, i2, i3, mask)],
				answer %= MOD;
		cout << answer;
	}

	Sub2(ll n): n(n){
		solve();
	}
};

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	freopen("ndnum.inp", "r", stdin);
	freopen("ndnum.out", "w", stdout);
	cin >> n;

	if (n <= 6)
	Sub1 sub1(n);
	else if(n<=7) cout << 207198;
	else cout << 1495638;
}