#include <bits/stdc++.h>
using namespace std;
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
*/

typedef long long ll;
typedef long double ld;
typedef vector<ll> vi;
typedef vector<ll> vl;
typedef pair<ll, ll> pii;
typedef pair<ll, ll> pll;
typedef map<ll, ll> mii;
typedef unordered_map<ll, ll> umii;
typedef map<ll, ll> mll;
typedef unordered_map<ll, ll> umll;

/*
struct Node
{
	ll node, len;
	Node() {node = len = 0;}
	Node(ll node, ll len) {this -> node = node, this -> len = len;}
};
typedef vector<Node> vg;
*/

#define MAX 1000001
#define MOD 111539786

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
string p; ll len;
bool bitState[15];
ll pi[15];

void kmp(){
	pi[1] = 0;
	ll k = 0;
	FOR(ll, i, 2, len){
		while (k && bitState[i] != bitState[k + 1]) k = pi[k];
		if (bitState[k + 1] == bitState[i]) k++;
		pi[i] = k;
	}
}

ll sub1(){
	ll currBit[MAX] = {};
	ll answer = 0;
	FOR(ll, _, 0, (1 << n) - 1){
		ll mask = _;
		FORR(ll, i, n, 1)
			currBit[i] = mask & 1, mask >>= 1;
		
		ll k = 0; bool okay = true;
		FOR(ll, i, 1, n){
			while (k && bitState[k + 1] != currBit[i]) k = pi[k];
			// cerr << currBit[i] << '/' << k << '\t';
			if (bitState[k + 1] == currBit[i]) k++;
			if (k == len) okay = false;
		}
		// cerr << '\n';
		
		answer += okay;
	}
	return answer;
}

ll f[MAX][10];
ll sub2(){
	memset(f, false, sizeof(f));
	f[0][0] = 1;
	FOR(ll, pos, 0, n - 1){
		FOR(ll, sameLen, 0, len - 1){
			ll &curr = f[pos][sameLen];
			if (curr == 0) continue;

			// case same
			if (sameLen + 1 < len)
				f[pos + 1][sameLen + 1] += curr, f[pos + 1][sameLen + 1] %= MOD;
			
			// case diff
			ll k = sameLen; bool nextChar = !bitState[k + 1];
			
			while (k && bitState[k + 1] != nextChar) k = pi[k];
			if (bitState[k + 1] == nextChar) k++;

			f[pos + 1][k] += curr, f[pos + 1][k] %= MOD;
		}
	}
	ll answer = 0;
	FOR(ll, sameLen, 0, len - 1)
		answer += f[n][sameLen], answer %= MOD;
	return answer;
}

struct Matrix{
	ll len;
	ll mat[10][10] = {};
	Matrix(ll len){this -> len = len;}
};
Matrix operator * (Matrix a, Matrix b){
	ll len = a.len;
	Matrix ans(len);
	FOR(ll, k, 0, len - 1)
		FOR(ll, i, 0, len - 1)
			FOR(ll, j, 0, len - 1){
				ans.mat[i][j] += (a.mat[i][k] * b.mat[k][j]) % MOD,
				ans.mat[i][j] %= MOD;
			}
	return ans;
}

Matrix operator ^ (Matrix a, ll n){
	if (n == 1) return a;
	Matrix ans = a ^ (n >> 1);
	ans = ans * ans;
	if (n & 1) return ans * a;
	return ans;
}

ll sub3(){
	Matrix init(len), mul(len);
	init.mat[0][0] = 1;

	FOR(ll, i, 0, len - 1){
		if (i + 1 < len)
			mul.mat[i][i + 1] = 1;
		
		ll k = i; bool nextChar = !bitState[k + 1];
		while (k && bitState[k + 1] != nextChar) k = pi[k];
		if (bitState[k + 1] == nextChar) k++;

		mul.mat[i][k] = 1;
	}
	init = init * (mul ^ n);
	ll answer = 0;
	FOR(ll, i, 0, len - 1)
		answer += init.mat[0][i], answer %= MOD;
	return answer;
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	while (cin >> n >> p){
		len = p.length(); p = ' ' + p;
		FOR(ll, i, 1, len) bitState[i] = p[i] - '0';
		kmp();
		
		if (n <= 10) cout << sub1();	
		else if (n <= 100000) cout << sub2();
		else cout << sub3();
		cout << '\n';
	}
}