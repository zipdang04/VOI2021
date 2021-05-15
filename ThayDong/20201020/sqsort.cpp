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

#define testBit(n, bit) ((n >> bit) & 1)
#define flipBit(n, bit) (n ^ (1ll << bit))
#define cntBit(n) __builtin_popcount(n)
#define cntBitll(n) __builtin_popcountll(n)
#define randomize mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count());

int n, k;
int a[MAX];
int ans[1 << 22] = {}, ansLen;

void nen(int *arr, int len){
	pii save[len + 1];
	FOR(int, i, 1, len)
		save[i] = {arr[i], i};
	sort(save + 1, save +  1 + len);

	int tmp = 0;
	FOR(int, i, 1, len){
		if (i > 1 && (save[i].fi != save[i - 1].fi)) tmp++;
		arr[save[i].se] = tmp;
	}
}

void process(int *arr, int len, int bit, int pos){
	if (bit < 0) return;
	int s[len + 1] = {}, sLen = 0;
	int q[len + 1] = {}, qLen = 0;
	FOR(int, i, 1, len){
		int num = arr[i];
		if (testBit(num, bit)){
			s[++sLen] = num;
			ans[++ansLen] = pos * 2 - 1;
		} else {
			q[++qLen] = num;
			ans[++ansLen] = pos * 2 - 1;
			ans[++ansLen] = pos * 2;
		}
	}
	process(q, qLen, bit - 1, pos + 1);
	qLen = sLen;
	FOR(int, i, 1, qLen){
		ans[++ansLen] = pos * 2;
		q[qLen - i + 1] = s[i];
	}
	process(q, qLen, bit - 1, pos + 1);
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n >> k; FOR(int, i, 1, k) cin >> a[i]; nen(a, k);
	process(a, k, n - 1, 1);
	cout << ansLen << '\n';
	FOR(int, i, 1, ansLen)
		cout << ans[i] << ' ';
}