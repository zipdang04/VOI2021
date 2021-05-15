#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

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

int blSize = 315;
struct Query{int l, r, k;};
bool operator < (Query a, Query b){
	int blA = a.l / blSize, blB = b.l / blSize;
	if (blA < blB) return true;
	if (blA > blB) return false;
	return (blA & 1) ? (a.r < b.r) : (a.r > b.r);
}

int n, q; 
int a[MAX];
pair<Query, int> query[MAX];
int bit[MAX];
int ans[MAX];

int match[MAX], num;

void add(int ind, int val){
	while (ind < MAX)
		bit[ind] += val, ind += ind & -ind;		
}

int get(int ind){
	int ans = 0;
	while (ind)
		ans += bit[ind], ind -= ind & -ind;		
	return ans;
}

void changeLeft(int prev, int curr){
	if (prev <= curr)
		FOR(int, i, prev, curr - 1) add(a[i], -1);
	else
		FOR(int, i, curr, prev - 1) add(a[i], 1);
}

void changeRight(int prev, int curr){
	if (prev >= curr)
		FOR(int, i, curr + 1, prev) add(a[i], -1);
	else
		FOR(int, i, prev + 1, curr) add(a[i], 1);
}

void nen(){
	pii save[MAX];
	FOR(int, i, 1, n) save[i] = {a[i], i};
	sort (save + 1, save + 1 + n);
	num = 1;
	FOR(int, i, 1, n){
		if (i != 1 && save[i].fi != save[i - 1].fi) num++;
		match[num] = save[i].fi;
		a[save[i].se] = num;
	}
}



main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	//input & process
	cin >> n; FOR(int, i, 1, n) cin >> a[i]; nen();
	cin >> q;
	FOR(int, i, 1, q) {
		int l, r, k; cin >> l >> r >> k;
		query[i] = {{l, r, k}, i};
	}
	sort(query + 1, query + 1 + q);
	//=========================
	//sqrt decomposition
	Query prev = {1, n, -1}; 
	FOR(int, i, 1, n) add(a[i], 1);

	FOR(int, i, 1, q){
		Query curr = query[i].fi; int pos = query[i].se;
		if (curr.l <= prev.r){
			changeLeft(prev.l, curr.l);
			changeRight(prev.r, curr.r);
		} else {
			changeRight(prev.r, curr.r);
			changeLeft(prev.l, curr.l);
		}

		int left = 1, right = n, tmp = n;
		while (left <= right){
			int mid = (left + right) >> 1;
			if (get(mid) >= curr.k) tmp = mid, right = mid - 1;
			else left = mid + 1;
		}
		ans[pos] = match[tmp];

		prev = curr;
	}
	//=========================
	FOR(int, i, 1, q) cout << ans[i] << '\n';
	
}