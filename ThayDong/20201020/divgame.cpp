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

#define MAX 1500
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

int X, Y, G;
int f[MAX][MAX];
int divX[MAX], divY[MAX], divG[MAX];
int lenX = 0, lenY = 0, lenG = 0;
vi gX[MAX], gY[MAX], gG[MAX];

// ll startTime = chrono::steady_clock::now().time_since_epoch().count();

void makeDiv(int num, int *div, int &len, vi *graph){
	FOR(int, i, 1, num){
		if (i * i > num) break;
		if (num % i) continue;

		int d1 = i, d2 = num / i;
		div[++len] = d1;
		if (d2 != d1) div[++len] = d2;
	}
	sort(div + 1, div + 1 + len);

	FOR(int, i, 1, len)
		FOR(int, j, 1, i)
			if (div[i] % div[j] == 0)
				graph[i].push_back(div[j]);
}

int findInd(int num, int *div, int &len){
	int left = 1, right = len, ans;
	while (left <= right){
		int mid = (left + right) >> 1;
		int curr = div[mid];
		if (curr == num){ans = mid; break;}
		else if (curr > num) right = mid - 1;
		else left = mid + 1;
	}
	return ans;
}

#define A true
#define B false
#define WIN 1
#define LOSE 2
int dp(int x, int y){
	// ll endTime = chrono::steady_clock::now().time_since_epoch().count();
	// if (endTime - startTime > 1500000000) {
	// 	cout << "A"; exit(0);
	// }
	int posX = findInd(x, divX, lenX), posY = findInd(y, divY, lenY);
	if (x == 1 && y == 1) {f[posX][posY] = LOSE; return LOSE;}
	if (f[posX][posY]) return f[posX][posY];
	int g = __gcd(x, y); int posG = findInd(g, divG, lenG);

	for (int i: gX[posX]){
		if (i * i > x) break;
		if (x % i) continue;

		int d1 = i, d2 = x / i;
		if (d1 != 1){
			int numX = x / d1;
			if (dp(numX, y) == LOSE) {f[posX][posY] = WIN; return WIN;}
		}
		if (d2 != 1){
			int numX = x / d2;
			if (dp(numX, y) == LOSE) {f[posX][posY] = WIN; return WIN;}
		}
	}
	
	for (int i: gY[posY]){
		if (i * i > y) break;
		if (y % i) continue;

		int d1 = i, d2 = y / i;
		if (d1 != 1){
			int numY = y / d1;
			if (dp(x, numY) == LOSE) {f[posX][posY] = WIN; return WIN;}
		}
		if (d2 != 1){
			int numY = y / d2;
			if (dp(x, numY) == LOSE) {f[posX][posY] = WIN; return WIN;}
		}
	}
	
	for (int i: gG[posG]){
		if (i * i > g) break;
		if (g % i) continue;

		int d1 = i, d2 = g / i;
		if (d1 != 1){
			int numX = x / d1, numY = y / d1;
			if (dp(numX, numY) == LOSE) {f[posX][posY] = WIN; return WIN;}
		}
		if (d2 != 1){
			int numX = x / d2, numY = y / d2;
			if (dp(numX, numY) == LOSE) {f[posX][posY] = WIN; return WIN;}
		}
	}
	f[posX][posY] = LOSE; return LOSE;
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> X >> Y;
	makeDiv(X, divX, lenX, gX);
	makeDiv(Y, divY, lenY, gY);
	makeDiv(__gcd(X, Y), divG, lenG, gG);
	cout << ((dp(X, Y) == WIN) ? "A" : "B");
}