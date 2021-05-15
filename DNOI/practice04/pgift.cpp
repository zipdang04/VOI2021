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

pll a[5], arr[5];
bool visited[5];
ll ans = INT64_MAX;

ll getAns(pll *tmp, ll len){
	ll size1 = 0, size2 = 0;
	FOR(ll, i, 1, len)
		size1 += tmp[i].fi, size2 = max(tmp[i].se, size2);
	return size1 * size2;
}

void cal(pll *tmp, ll len){
	FOR(ll, mask, 0, (1 << len) - 1){
		ll size1 = tmp[1].fi, size2 = tmp[1].se;
		FOR(ll, pos, 2, len){
			if (testBit(mask, pos - 2))
				size1 += tmp[pos].fi, size2 = max(size2, tmp[pos].se);
			else
				size1 = max(size1, tmp[pos].fi), size2 += tmp[pos].se;
		}
		ans = min(ans, size1 * size2);
	}
}
ll p1111(){
	pll tmp[5];
	FOR(ll, i, 1, 4) tmp[i] = arr[i];
	cal(tmp, 4);

	cal(tmp, 4);
	return getAns(tmp, 4);
}
ll p112(){
	pll tmp[5];
	FOR(ll, i, 1, 4) tmp[i] = arr[i];
	cal(tmp, 4);
	tmp[3].fi = max(tmp[3].fi, tmp[4].fi), tmp[3].se += tmp[4].se;

	cal(tmp, 3);
	return getAns(tmp, 3);
}
ll p13(){
	pll tmp[5];
	FOR(ll, i, 1, 4) tmp[i] = arr[i];
	cal(tmp, 4);
	tmp[2].fi = max(tmp[2].fi, tmp[3].fi), tmp[2].se += tmp[3].se;
	tmp[2].fi = max(tmp[2].fi, tmp[4].fi), tmp[2].se += tmp[4].se;

	cal(tmp, 2);
	return getAns(tmp, 2);
}
ll p22(){
	pll tmp[5];
	FOR(ll, i, 1, 4) tmp[i] = arr[i];
	cal(tmp, 4);
	swap(tmp[2], tmp[3]);
	cal(tmp, 4);
	tmp[1].fi = max(tmp[1].fi, tmp[3].fi), tmp[1].se += tmp[3].se;
	tmp[2].fi = max(tmp[2].fi, tmp[4].fi), tmp[2].se += tmp[4].se;

	cal(tmp, 2);
	return getAns(tmp, 2);
}

void cal(pll *tmp){
	FOR(ll, mask, 0, 7){
		ll size1 = tmp[1].fi, size2 = tmp[1].se;
		FOR(ll, pos, 2, 4){
			if (testBit(mask, pos - 2))
				size1 += tmp[pos].fi, size2 = max(size2, tmp[pos].se);
			else
				size1 = max(size1, tmp[pos].fi), size2 += tmp[pos].se;
		}
		ans = min(ans, size1 * size2);
	}
}

void dqql(ll pos){
	if (pos > 4){
		cal(arr);
		ans = min(ans, min(min(p1111(), p112()), min(p13(), p22())));
		return;
	}
	FOR(ll, i, 1, 4){
		if (visited[i]) continue;
		visited[i] = true; arr[pos] = a[i];
		dqql(pos + 1);
		visited[i] = false;
	}
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	FOR(ll, i, 1, 4) cin >> a[i].fi >> a[i].se;
	FOR(ll, i, 0, 15){
		FOR(ll, bit, 1, 4)
			if (testBit(i, bit - 1)) swap(a[bit].fi, a[bit].se);
		// FOR(ll, bit, 1, 4) cerr << a[bit].fi << '/' << a[bit].se << ' '; cerr << '\n';
		dqql(1);
		FOR(ll, bit, 1, 4)
			if (testBit(i, bit - 1)) swap(a[bit].fi, a[bit].se);
	}
	cout << ans;
}