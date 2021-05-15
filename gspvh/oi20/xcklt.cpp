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

#define MAX 501
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

string a, b, c;
int lenA, lenB, lenC;
int f[MAX][MAX][MAX];
int pick[MAX][MAX][MAX];
bool tC[MAX][MAX][MAX];

void initData(){
	FOR(int, i, 0, MAX - 1)
		FOR(int, j, 0, MAX - 1)
			FOR(int, k, 0, MAX - 1)
				f[i][j][k] = INT32_MAX;
}

bool minimize(int &a, int b){
	if (a <= b) return false;
	a = b; return true;
}


main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	freopen("xcklt.inp", "r", stdin);
	freopen("xcklt.out", "w", stdout);
	
	cin >> a >> b >> c;
	lenA = a.length(), lenB = b.length(), lenC = c.length();
	a = ' ' + a + ' ', b = ' ' + b + ' ', c = ' ' + c + ' ';

	initData();

	f[0][0][0] = 0;
	FOR(int, i, 0, lenA)
		FOR(int, j, 0, lenB){
			FOR(int, k, 0, lenC - 1){
				if (f[i][j][k] == INT32_MAX) continue;
				char chA = a[i + 1], chB = b[j + 1], chC = c[k + 1];

				if (i < lenA){
					int newK = k; bool tmp = false;
					if (chA == chC) newK++, tmp = true;
					if (minimize(f[i + 1][j][newK], f[i][j][k] + 1))
						pick[i + 1][j][newK] = 1,
						tC[i + 1][j][newK] = tmp;
				}
				if (j < lenB){
					int newK = k; bool tmp = false;
					if (chB == chC) newK++, tmp = true;
					if (minimize(f[i][j + 1][newK], f[i][j][k] + 1))
						pick[i][j + 1][newK] = 2,
						tC[i][j + 1][newK] = tmp;
				}
				if (i < lenA && j < lenB && chA == chB){
					int newK = k; bool tmp = false;
					if (chA == chC) newK++, tmp = true;
					if (minimize(f[i + 1][j + 1][newK], f[i][j][k] + 1))
						pick[i + 1][j][newK] = 3,
						tC[i + 1][j][newK] = tmp;
				}
			}
		}
	
	int ans = INT32_MAX;
	int same = 0;
	FOR(int, k, 0, lenC - 1)
		if (f[lenA][lenB][k] < ans)
			ans = f[lenA][lenB][k], same = k;
	if (ans == INT32_MAX) {cout << "TRETRAU"; return 0;}
	
	cout << ans << '\n';
	string sAns = "";
	int x = lenA, y = lenB;
	while (x || y){
		int des = pick[x][y][same]; bool nxtC = tC[x][y][same];
		if (des == 1)
			sAns = a[x] + sAns, x--;
		else if (des == 2)
			sAns = b[y] + sAns, y--;
		else
			sAns = b[y] + sAns, x--, y--;
		same -= nxtC;
	}
	cout << sAns;
}