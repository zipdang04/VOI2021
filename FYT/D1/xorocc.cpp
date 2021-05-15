#pragma GCC optimize("Ofast")  
#pragma GCC target("avx,avx2,fma") 

#include <bits/stdc++.h>
using namespace std;
// /*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
// */

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

#define MAX 100001
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

randomize;
struct chash { 
    const uint64_t C = ll(2e18)+71; 
    const int RANDOM = mt(); 
    ll operator()(ll x) const {
        return __builtin_bswap64((x^RANDOM)*C);
    }
};

gp_hash_table<int, int, chash> cnt[MAX];

const int blSize = 320;
int n, q;
int a[MAX];
int tmp[MAX];
// umii cnt[MAX];

void del(int block, int left, int right){
	FOR(int, i, left, right){
		int num = a[i];
		// if (cnt[block][num] == 1) cnt[block].erase(num);
		// else cnt[block][num]--;
		cnt[block][num]--;
	}
}

void add(int block, int left, int right, int tmp){
	FOR(int, i, left, right){
		a[i] ^= tmp;
		cnt[block][a[i]]++;
	}
}

int get(int block, int left, int right, int num){
	int ans = 0;
	FOR(int, i, left, right)
		ans += a[i] == num;
	return ans;
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n >> q;
	FOR(int, i, 1, n) {
		cin >> a[i];
		cnt[i / blSize][a[i]]++;
	}
	FOR(int, _, 1, q){
		int type, l, r, x; cin >> type >> l >> r >> x;
		int blockL = l / blSize, blockR = r / blSize;
		if (type == 1){
			if (blockL == blockR){
				int block = blockL;
				del(block, l, r);
				add(block, l, r, x);

			} else {
				int begin = l, end = (blockL + 1) * blSize - 1;
				del(blockL, begin, end);
				add(blockL, begin, end, x);

				begin = blockR * blSize, end = r;
				del(blockR, begin, end);
				add(blockR, begin, end, x);

				FOR(int, i, blockL + 1, blockR - 1) tmp[i] ^= x;
			}
		} else {
			int ans = 0;
			if (blockL == blockR){
				int block = blockL;
				ans = get(block, l, r, x ^ tmp[block]);
			} else {
				int begin = l, end = (blockL + 1) * blSize - 1;
				ans += get(blockL, begin, end, x ^ tmp[blockL]);
				begin = blockR * blSize, end = r;
				ans += get(blockR, begin, end, x ^ tmp[blockR]);
				
				FOR(int, block, blockL + 1, blockR - 1)
					ans += cnt[block][x ^ tmp[block]];
			}
			cout << ans << '\n';
		}
	}
}