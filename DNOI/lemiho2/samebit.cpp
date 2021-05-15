#include <bits/stdc++.h>
using namespace std;

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

// struct Node
// {
// 	int node, len;
// 	Node() {node = len = 0;}
// 	Node(int node, int len) {this -> node = node, this -> len = len;}
// };
// typedef vector<Node> vg;

#define MAX 1000001
#define MOD 123456789

#define fi first
#define se second
#define pf push_front
#define pb push_back

#define FOR(type, i, a, b) for(type i = a; i <= b; i++)
#define FORR(type, i, b, a) for(type i = b; i >= a; i--)

#define testBit(n, bit) ((n >> bit) & 1)
#define flipBit(n, bit) (n ^ (1ll << bit))
#define randomize mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count());

struct Mat{
	ll f[2][2] = {};
	Mat(){
		FOR(int, i, 0, 1)
			FOR(int, j, 0, 1)
				f[i][j] = 0;
	}
};

Mat operator * (Mat a, Mat b){
	Mat ans; 
	FOR(int, k, 0, 1)
		FOR(int, i, 0, 1)
			FOR(int, j, 0, 1)
				ans.f[i][j] += a.f[i][k] * b.f[k][j],
				ans.f[i][j] %= MOD;
	return ans;
}

Mat operator ^ (Mat a, ll n){
	if (n == 1) return a;
	Mat ans = a ^ (n >> 1);
	ans = ans * ans;
	if (n & 1) ans = ans * a;
	return ans;
}

ll n;

main()
{
	Mat a, mul;
	FOR(int, i, 0, 1)
		FOR(int, j, 0, 1)
			a.f[i][j] = 0;
	a.f[0][1] = 1;
	mul.f[0][0] = 4;
	mul.f[0][1] = 0;
	mul.f[1][0] = 1;
	mul.f[1][1] = 1;
	int t; cin >> t;
	FOR(int, _, 1, t){
		cin >> n;
		if (n == 1) {
			cout << 0 << '\n'; continue;
		}
		Mat ans = a * (mul ^ (n >> 1));
		if (n & 1) ans.f[0][0] = (ans.f[0][0] * 2) % MOD;
		cout << ans.f[0][0] << '\n';
	}
}