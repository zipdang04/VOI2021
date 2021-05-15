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

int theta, test;
randomize;

struct Query{
	bool isG; ll p1, p2, num;
} que[MAX];

ll n, q;

ll __lcm(ll a, ll b){
	return a / __gcd(a, b) * b;
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	freopen("gcdlcm.inp", "r", stdin);
	freopen("gcdlcm.out", "w", stdout);
	cin >> theta >> test;
	if (theta > 0){
		FOR(int, i, 1, test) cout << ((mt() & 1) ? "Y" : "N");
		return 0;
	}
	if (theta == 1){
		FOR(int, _, 1, test){
			cin >> n >> q;
			FOR(int, i, 1, q){
				string ss; int x, y, z;
				que[i] = {ss == "GCD", x, y, z};
			}
			int arr[4] = {}; bool okay = true;
			cerr << "//" << _ << '\n';
			FOR(int, x, 1, 100){
				FOR(int, y, 1, 100){
					FOR(int, z, 1, 100){
						arr[1] = x, arr[2] = y, arr[3] = z;
						FOR(int, i, 1 , q){
							cerr <<x << ' ' << y << ' ' << z << '\n';
							Query curr = que[i];
							if (curr.isG){
								if (__gcd(arr[curr.p1], arr[curr.p2]) != curr.num) okay = false;
							} else {
								if (__lcm(arr[curr.p1], arr[curr.p2]) != curr.num) okay = false;
							}
							if (!okay) break;
						}
					}
					if (!okay) break;
				}
				if (!okay) break;
			}
			cout << (okay ? "Y" : "N");
		}
	} else {

	}
}