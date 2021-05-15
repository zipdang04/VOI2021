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

#define testBit(n, bit) (((n) >> (bit)) & 1)
#define flipBit(n, bit) ((n) ^ (1ll << (bit)))
#define cntBit(n) __builtin_popcount(n)
#define cntBitll(n) __builtin_popcountll(n)
#define randomize mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count());

int n;
pii a[MAX];

int f[MAX];
int len[MAX];
int trace[MAX];

vi group[MAX];
priority_queue<pii, vector<pii>, greater<pii>> pq;
void trau(){
	sort(a + 1, a + 1 + n, greater<pii>());
	
	int ptr = 1, ans = 0;
	while (ptr <= n){
		pii curr = a[ptr];
		int need = curr.fi, pos = curr.se;
		int remain = n - ptr + 1;

		if (need > remain) break;
		ans++; pq.push({ans, need});
		FOR(int, i, 0, need - 1){
			group[ans].push_back(a[ptr].se);
			ptr++;
		}
	}
	FOR(int, i, ptr, n){
		pii curr = pq.top(); pq.pop();
		curr.fi++; group[curr.se].push_back(i);
		pq.push(curr);
	}
	cout << ans << '\n';
	FOR(int, i, 1, ans){
		cout << group[i].size() << ' ';
		for (int num: group[i])
			cout << num << ' ';
		cout << '\n';
	}
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	FOR(int, i, 1, n){
		int x; cin >> x;
		a[i] = {x, i};
	}
	if (n > 5000){
		trau();
		return 0;
	}
	sort(a + 1, a + 1 + n);
	FOR(int, i, 1, n){
		pii curr = a[i];
		int num = a[i].fi;
		if (num > i) continue;
		if (num == i){
			f[i] = 1, len[i] = i;
			continue;
		}

		FORR(int, j, i - num, 1){
			int newF = f[j] + 1;
			int newLen = max(len[j], i - j);
			if (newF > f[i] || (newF == f[i] && newLen < len[i])){
				f[i] = newF, len[i] = newLen, trace[i] = j;
			}
		}
	}
	cout << f[n] << '\n';
	int pos = n;
	while (pos){
		int t = trace[pos];
		cout << pos - t << ' ';
		FOR(int, i, t + 1, pos)
			cout << a[i].se << ' ';
		cout << '\n';
		pos = t;
	}
	
}