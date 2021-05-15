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

#define MAX 300005
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

struct Query{bool eat = false; int t = 0, c = 0;};

int theta, q, k;
Query qList[MAX];
int t[MAX], c[MAX];

mii nenTmp;
void nen(int *arr){
	nenTmp.clear();
	FOR(int, i, 1, q)
		nenTmp[arr[i]] = true;
	
	int num = 0;
	for (pii i: nenTmp)
		nenTmp[i.fi] = num++;
	
	FOR(int, i, 1, q)
		arr[i] = nenTmp[arr[i]];
}

class SegmentTree{
	private:
		const int len = 300000;
		int cntDish[MAX * 4] = {};
		ll highCal[MAX * 4] = {};
		ll sumDeli[MAX * 4] = {};

		void update(int ind, int left, int right, int pos, ll deli, ll cal){
			cntDish[ind]++;
			sumDeli[ind] += deli;
			highCal[ind] = max(highCal[ind], cal);

			if (left == right) return;
			int y = ind << 1, mid = (left + right) >> 1;
			if (pos <= mid)
				update(y, left, mid, pos, deli, cal);
			else
				update(y + 1, mid + 1, right, pos, deli, cal);
		}
		void delBest(int ind, int left, int right){
			if (left == right){
				cntDish[ind] = highCal[ind] = sumDeli[ind] = 0;
				return;
			}

			int y = ind << 1, mid = (left + right) >> 1;
			if (highCal[y] > highCal[y + 1])
				delBest(y, left, mid);
			else
				delBest(y + 1, mid + 1, right);
			
			cntDish[ind] = cntDish[y] + cntDish[y + 1];
			sumDeli[ind] = sumDeli[y] + sumDeli[y + 1];
			highCal[ind] = max(highCal[y], highCal[y + 1]);
			return;
		}
		ll get(int ind, int left, int right, int amount){
			if (cntDish[ind] <= amount) return sumDeli[ind];
			int y = ind << 1, mid = (left + right) >> 1;
			if (cntDish[y + 1] >= amount)
				return get(y + 1, mid + 1, right, amount);
			else
				return sumDeli[y + 1] + get(y, left, mid, amount - cntDish[y + 1]);
		}
	public:
		SegmentTree(){
			memset(cntDish, 0, sizeof(cntDish));
			memset(highCal, 0, sizeof(highCal));
			memset(sumDeli, 0, sizeof(sumDeli));
		}
	//=================basic query==================================
		void update(int pos, int deli, int cal){
			update(1, 1, len, pos, deli, cal);
		}
		void delBest(){
			delBest(1, 1, len);
		}
		ll get(int amount){
			return get(1, 1, len, amount);
		}
	//====================main query================================
		ll show(int pos, int t, int c){
			update(pos, t, c);
			return get(k);
		}
		ll eat(){
			delBest();
			return get(k);
		}
};
SegmentTree segTree;
main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	// ==========================================
	cin >> theta >> q >> k;
	FOR(int, i, 1, q){
		string s; cin >> s;
		if (s == "show"){
			cin >> t[i] >> c[i];
			qList[i] = {false, t[i], c[i]};
		} else
			qList[i] = {true, 0, 0};
	}
	// ==========================================
	nen(t);
	FOR(int, _, 1, q){
		Query curr = qList[_];
		if (curr.eat) cout << segTree.eat() << ' ';
		else cout << segTree.show(t[_], curr.t, curr.c) << ' ';
	}
	// ==========================================
}