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

#define MAX 400001
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

int theta, m, f;
pii bLo[MAX], bHi[MAX], gLo[MAX], gHi[MAX];
int bL = 0, bH = 0, gL = 0, gH = 0;

pii match[MAX]; int cntMatch = 0;
void process(pii *lo, pii *hi, int lenLo, int lenHi, bool sw){
	int j = 1; pii currHi = hi[j];
	FOR(int, i, 1, lenLo){
		pii currLo = lo[i];
		if (currLo.fi > currHi.fi){
			if (sw)
				match[++cntMatch] = {currHi.se, currLo.se};
			else
				match[++cntMatch] = {currLo.se, currHi.se};
			j++; 
			if (j > lenHi) break; 
			else currHi = hi[j];
		}
	}
}
main()
{
	freopen("couples.inp", "r", stdin);
	freopen("couples.out", "w", stdout);
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> theta;
	cin >> m; FOR(int, i, 1, m){
		int b; cin >> b;
		if (b < 0) 
			bLo[++bL] = {-b, i};
		else
			bHi[++bH] = {b, i};
	}
	cin >> f; FOR(int, i, 1, f){
		int g; cin >> g;
		if (g < 0) 
			gLo[++gL] = {-g, i};
		else
			gHi[++gH] = {g, i};
	}

	sort(bLo + 1, bLo + bL + 1);
	sort(bHi + 1, bHi + bH + 1);
	sort(gLo + 1, gLo + gL + 1);
	sort(gHi + 1, gHi + gH + 1);
	process(bLo, gHi, bL, gH, false);
	process(gLo, bHi, gL, bH, true);
	cout << cntMatch << '\n';
	FOR(int, i,1 , cntMatch)
		cout << match[i].fi << ' ' << match[i].se << '\n';
}