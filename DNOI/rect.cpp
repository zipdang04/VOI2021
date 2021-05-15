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

#define MAX 505
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

ll m, n;
ll a[MAX][MAX];
ll mini[MAX][MAX];
ll sum[MAX][MAX];
main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	//input
	cin >> m >> n;
	FOR(int, i, 1, m)
		FOR(int, j, 1, n)
			cin >> a[i][j];
	//=========================
	FOR(int, width, 1, n){
		FOR(int, row, 1, m){
			deque<int> dq;
			int currSum = 0;
			FOR(int, col, 1, n){
				int currVal = a[row][col];
				currSum += a[row][col];
				
				while (!dq.empty() && a[row][dq.front()] >= currVal) dq.pop_front();
				
				if (col >= width){
					currSum -= a[row][col - width];
					if (dq.back() + width <= col) dq.pop_back();
					sum[row][col - width + 1] = currSum;
					mini[row][col - width + 1] = a[row][dq.back()];
				} 
			}

			FOR(int, col, 1, n - width + 1){
				
			}
		}
	}

}