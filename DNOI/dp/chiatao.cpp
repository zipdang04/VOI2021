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

#define MAX 100001
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

ll n, m;
ll a[MAX];
ll sum[MAX];

class STLazy{
	private:
		ll len;
		ll ad[MAX * 4] = {};
		ll ma[MAX * 4] = {};

		void addSegment(ll ind, ll left, ll right, ll posL, ll posR, ll val){
			if (right < posL || posR < left) return;
			if (posL <= left && right <= posR){
				ad[ind] += val;

				if (ma[ind] == -1) ma[ind] = val;
				else ma[ind] += val;
				
				return;
			}

			ll y = ind << 1, mid = (left + right) >> 1;
			addSegment(y, left, mid, posL, posR, val);
			addSegment(y + 1, mid + 1, right, posL, posR, val);
			
			if (ma[y] == -1) ma[ind] = ad[ind] + ma[y + 1];
			else if (ma[y + 1] == -1) ma[ind] = ad[ind] + ma[y];
			else ma[ind] = ad[ind] + min(ma[y], ma[y + 1]);
		}

		ll getSegment(ll ind, ll left, ll right, ll posL, ll posR){
			if (right < posL || posR < left) return INT64_MAX;
			if (posL <= left && right <= posR) return ma[ind];

			ll y = ind << 1, mid = (left + right) >> 1;
			return ad[ind] + min(
				getSegment(y, left, mid, posL, posR),
				getSegment(y + 1, mid + 1, right, posL, posR)
			);
		}
	public:
		STLazy(ll len){
			this -> len = len;
			FOR(int, i, 0, len * 4)
				ma[i] = -1;
		}
		void addSegment(ll posL, ll posR, ll val){addSegment(1, 0, len, posL, posR, val);}
		ll getSegment(ll posL, ll posR){return getSegment(1, 0, len, posL, posR);}
};

STLazy *segTree;
stack<int> st;

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	//inpupt
	cin >> n >> m;
	FOR(ll, i, 1, n){
		cin >> a[i];
		sum[i] = sum[i - 1] + a[i];
	}
	segTree = new STLazy(n);
	//=========================
	
	segTree -> addSegment(0, 0, a[0]);
	st.push(0); a[0] = INT64_MAX;

	int ptr = 0;
	FOR(ll, i, 1, n){
		while (sum[i] - sum[ptr] > m) ptr++;
		ll num = a[i];
		
		int pos = i, prevNum = 0;
		while (!st.empty()){
			int fore = st.top();
			segTree -> addSegment(fore, pos - 1, num - prevNum);
			if (a[fore] < num)
				pos = fore, prevNum = a[fore], st.pop();
			else break;
		}
		st.push(i);
		
		ll ans = segTree -> getSegment(ptr, i - 1);
		segTree -> addSegment(i, i, ans);
		if (i == n) cout << sum[i] - ans;
	}
}