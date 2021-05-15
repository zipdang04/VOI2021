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

string str;
int n;

bool check(string &s, int len){
	int rank[len] = {};
	
	pii save[len];
	FOR(int, i, 0, len - 1)
		save[i] = {s[i], i};
	sort(save, save + len);

	int rk = 1;
	FOR(int, i, 0, len - 1){
		if (i && save[i].fi != save[i - 1].fi) rk++;
		rank[save[i].se] = rk;
	}

	FOR(int, _, 1, 8){
		pair<pii, int> save[len];
		FOR(int, i, 0, len - 1)
			save[i] = {{rank[i], rank[(i + (1 << (_ - 1))) % len]}, i};
		sort(save, save + len);

		int rk = 1;
		FOR(int, i, 0, len - 1){
			if (i && save[i].fi != save[i - 1].fi) rk++;
			rank[save[i].se] = rk;
		}
	}
	// cerr << "input: " << s << '\n';
	// // // cerr << "ranking:"; FOR(int, i, 0, len - 1) cerr << rank[i] << ' '; cerr << '\n';
	return rank[0] == 1;
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> str; n = str.length();

	int answer = 0;
	FOR(int, i, 0, n - 1){
		string curr;
		int len = 0;
		FOR(int, j, i, n - 1){
			curr += str[j]; len++;
			if (len >= 5)
				answer += check(curr, len);
		}
	}
	cout << answer;
}