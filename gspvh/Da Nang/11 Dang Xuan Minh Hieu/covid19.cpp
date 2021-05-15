#include <bits/stdc++.h>
using namespace std;
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<ll, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
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

#define MAX 500005
#define MOD 998244353

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

ll theta, n, k, q;

ll power[MAX];
ll sumPow[MAX];
void init(){
	power[0] = sumPow[0] = 1;
	FOR(ll, i, 1, MAX - 1)
		power[i] = (power[i - 1] * (n + 1)) % MOD,
		sumPow[i] = (sumPow[i - 1] + power[i]) % MOD;
}
ll getSum(ll p1, ll p2){
	return (sumPow[p2] + MOD - sumPow[p1 - 1]) % MOD;
}

class SegTree{
	struct Data{
		ll val, sum; bool stop;
		Data(){val = sum = stop = 0;}
		Data(ll val, ll sum, bool stop): val(val), sum(sum), stop(stop){}
	};
	
	private:
		ll answer = 0;

		ll len = 0;
		Data it[MAX * 4];

		void update(ll ind, ll left, ll right, const ll posL, const ll posR, const ll value){
			if (right < posL || posR < left) return;

			Data &node = it[ind];
			if (posL <= left && right <= posR){
				if (node.val < value){
					if (node.stop || left == right) return;
				} else {
					answer += MOD - node.sum, answer %= MOD;
					node = {value, (value * getSum(left, right)) % MOD, true};
					answer += node.sum, answer %= MOD;
					return;
				}
			}

			ll y = ind << 1, mid = (left + right) >> 1;
			Data &childL = it[y], &childR = it[y + 1];
			if (node.stop){
				childL = childR = node;
				childL.sum = node.val * getSum(left, mid) % MOD;
				childR.sum = node.val * getSum(mid + 1, right) % MOD;
				node.stop = false;
			}

			update(y, left, mid, posL, posR, value);
			update(y + 1, mid + 1, right, posL, posR, value);
			
			node.val = min(childL.val, childR.val);
			node.sum = childL.sum + childR.sum;
		}

		ll get(ll ind, ll left, ll right, const ll posL, const ll posR){
			if (right < posL || posR < left) return INT64_MAX;
			if (posL <= left && right <= posR)
				return it[ind].val;
			
			ll y = ind << 1, mid = (left + right) >> 1;
			return min(
				get(y, left, mid, posL, posR),
				get(y + 1, mid + 1, right, posL, posR)
			);
		}
	public:
		SegTree(ll len): len(len){
			FOR(ll, i, 1, len * 4)
				it[i] = {MOD - 1, (MOD - 1) * getSum(i, i) % MOD, true};
			answer = (MOD - 1) * ((sumPow[len] + MOD - sumPow[0]) % MOD);
		}

		void update(ll posL, ll posR, ll value){
			update(1, 1, len, posL, posR, value);
		}

		ll get(ll posL, ll posR){
			return get(1, 1, len, posL, posR);
		}
//=============================================================================
		ll getAns(){return answer;}

		void D(ll u, ll v){
			ll valU = get(u, u), valV = get(v, v);
			if (valU > valV) swap(u, v), swap(valU, valV);
			if (valU == valV) return;
			update(v, v, valU + 1);
		}

		void P(ll l, ll r){
			ll mini = get(l, r);
			update(l, r, mini + 1);
		}
};

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	freopen("covid19.inp", "r", stdin);
	freopen("covid19.out", "w", stdout);
	cin >> theta >> n >> k >> q;
	init();
	SegTree seg(n); 
	FOR(int, i, 1, k){
		int pos; cin >> pos;
		seg.update(pos, pos, 0);
	}
	cout << seg.getAns() << '\n';
	FOR(int, _, 1, q){
		char d; int u, v; cin >> d >> u >> v;
		if (d == 'D') seg.D(u, v);
		else seg.P(u, v);
		cout << seg.getAns() << '\n';
	}
}