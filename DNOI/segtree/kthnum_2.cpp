#pragma GCC optimize("Ofast")  
#pragma GCC target("avx,avx2,fma") 
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
const ll MAXVAL = 2000000003;
const ll ADD = 1000000001;

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

int n, a[MAX];
int match[MAX], num;

void merge(vi &a, vi &b, vi &c){
	int aSize = a.size(), bSize = b.size();
	int indA = 0, indB = 0, indC = 0;

	while (indA < aSize && indB < bSize){
		if (a[indA] < b[indB]) c[indC++] = a[indA++];
		else c[indC++] = b[indB++];
	}

	while (indA < aSize) c[indC++] = a[indA++];
	while (indB < bSize) c[indC++] = b[indB++];

}

int get(vi &arr, int num){
	return upper_bound(arr.begin(), arr.end(), num) - arr.begin();
}

class SegTree{
	private:
		vi it[MAX * 4];
		int len = 0;

		void buildTree(int index, int left, int right){
			it[index].resize(right - left + 1);
			if (left == right){
				it[index][0] = a[left];
				return;
			}

			int y = index << 1, mid = (left + right) >> 1;
			buildTree(y, left, mid), buildTree(y + 1, mid + 1, right);
			merge(it[y], it[y + 1], it[index]); 
		}

		int getAns(int index, int left, int right, int posL, int posR, int value){
			if (right < posL || posR < left) return 0;
			if (posL <= left && right <= posR) return get(it[index], value);

			int y = index << 1, mid = (left + right)  >> 1;
			return getAns(y, left, mid, posL, posR, value)
				+ getAns(y + 1, mid + 1, right, posL, posR, value);
		}
	public:
		SegTree(int _len){
			len = _len;
			buildTree(1, 1, len);
		}
		int getAns(int _left, int _right, int _value){
			return getAns(1, 1, len, _left, _right, _value);
		}
};

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

// SegTree seg;

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	//input
	cin >> n; 
	FOR(int, i, 1, n) cin >> a[i];
	nen();
	//=========================
	//init
	SegTree seg(n);
	//=========================
	//queries
	int q; cin >> q;
	FOR(int, _, 1, q){
		int l, r, k; cin >> l >> r >> k;
		int left = 1, right = num, ans = num;
		while (left <= right){
			int mid = (left + right) / 2;
			if (seg.getAns(l, r, mid) >= k) 
				ans = mid, right = mid - 1;
			else
				left = mid + 1;
		}
		cout << match[ans] << '\n';
	}
	//=========================
	
}