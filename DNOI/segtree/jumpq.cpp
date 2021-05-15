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

int n;
int x[MAX], y[MAX];
pii point[MAX];

pii bit[MAX];
const pii NON = {0, 0};

void nen(int *arr){
	pii save[MAX];
	FOR(int, i, 1, n) save[i] = {arr[i], i};
	sort (save + 1, save + 1 + n);
	int num = 1;
	FOR(int, i, 1, n){
		if (i != 1 && save[i].fi != save[i - 1].fi) num++;
		arr[save[i].se] = num;
	}
}

pii process(pii a, pii b){
	if (a == NON) return b;
	if (b == NON) return a;
	if (a.fi > b.fi) return a;
	if (b.fi > a.fi) return b;
	return {a.fi, (a.se + b.se) % MOD};
}

void update(int ind, pii val){
	while (ind <= n)
		bit[ind] = process(bit[ind], val), ind += ind & -ind;
}

pii get(int ind){
	pii ans = NON;
	while (ind)
		ans = process(bit[ind], ans), ind -= ind & -ind;
	return ans;
}

pii finalAns = NON;
main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	FOR(int, i, 1, n) cin >> x[i] >> y[i];
	
	nen(x), nen(y);
	FOR(int, i, 1, n) point[i] = {x[i], y[i]};
	sort(point + 1, point + 1 + n);

	stack<pair<int, pii>> st;
	int prevX = -1;
	FOR(int, i, 1, n){
		int currX = point[i].fi, currY = point[i].se;
		if (prevX != currX){
			while (!st.empty()){
				pair<int, pii> tmp = st.top(); st.pop();
				update(tmp.fi, tmp.se);
			}
		}
		pii curr = get(point[i].se - 1);
		
		if (curr == NON) curr = {1, 1};
		else curr.fi++;
		finalAns = process(finalAns, curr);

		st.push({currY, curr});
		prevX = currX;
	}
	cout << finalAns.fi << '\n' << finalAns.se;
}