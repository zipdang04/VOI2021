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

#define MAX 5002
#define VAL 100001
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

int n;
int a[MAX];
int f[MAX][MAX];
int forw[MAX][MAX];
int back[MAX][MAX];

int cnt[VAL];
int mod[7];

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n; FOR(int, i, 1, n) cin >> a[i];
	//calculate
	FOR(int, beg, 1, n)
	{
		FOR(int, i, beg, n){
			int num = a[i];
			int m = num % 7;
			
			int currAns = max(cnt[num - 1], mod[m]);
			currAns++;

			f[beg][i] = max(f[beg][i - 1], currAns);
			cnt[num] = max(cnt[num], currAns), mod[m] = max(mod[m], currAns);
		}
		FOR(int, i, beg, n)
			forw[beg][i] = max(forw[beg][i - 1], f[beg][i]);
		FORR(int, i, n, beg)
			back[beg][i] = max(back[beg][i + 1], f[beg][i]);

		//init
		FOR(int, i, beg, n) cnt[a[i]] = 0;
		FOR(int, i, 0, 6) mod[i] = 0;
		//=========================
	}
	//=========================	
	int answer = 0;
	FOR(int, i, 1, n - 1)
		answer = max(answer, forw[1][i] + back[i + 1][n]);
	cout << answer;
}