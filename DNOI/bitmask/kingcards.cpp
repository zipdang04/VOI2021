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

#define MAX 401
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

const pii oo = {-1, -1};

pii f[401][401][16][16];
string s; 
int lenS;

#define BIN false
#define ALG true

pii bestBin(pii a, pii b){
	if (a == oo) return b;
	if (b == oo) return a;
	if (a.fi - a.se > b.fi - b.se) return a;
	if (a.fi - a.se < b.fi - b.se) return b;
	if (a.fi > a.se) return a;
	return b;
}
pii bestAlg(pii a, pii b){
	if (a == oo) return b;
	if (b == oo) return a;
	if (a.se - a.fi > b.se - b.fi) return a;
	if (a.se - a.fi < b.se - b.fi) return b;
	if (a.se > a.fi) return a;
	return b;
}
pii dp(bool flag, int left, int right, int keyBin, int keyAlg){
	if (right < left) return {0, 0};
	if (f[left][right][keyBin][keyAlg] != oo) return f[left][right][keyBin][keyAlg];

	char cL = s[left], cR = s[right];
	
	pii currAns = oo;
	//left choice
	if (cL == '#'){
		if (flag == BIN)
			currAns = bestBin(currAns, dp(!flag, left + 1, right, keyBin, keyAlg));
		else
			currAns = bestAlg(currAns, dp(!flag, left + 1, right, keyBin, keyAlg));
	}
	else if (isdigit(cL)){
		int value = cL - '0';
		if (flag == BIN){
			pii ansLeft = dp(!flag, left + 1, right, keyBin, keyAlg); ansLeft.fi += value;
			currAns = bestBin(currAns, ansLeft);
		} else{
			pii ansLeft = dp(!flag, left + 1, right, keyBin, keyAlg); ansLeft.se += value;
			currAns = bestAlg(currAns, ansLeft);
		}

	}
	else if (isupper(cL)){
		int type;
		switch (cL){
			case 'G': type = 0; break;
			case 'R': type = 1; break;
			case 'P': type = 2; break;
			case 'Y': type = 3; break;
			default: break;
		}

		if (flag == BIN){ // bin turns
			pii ansLeft = dp(!flag, left + 1, right, keyBin | (1 << type), keyAlg);
			currAns = bestBin(currAns, ansLeft);
		}
		else{ // alg turns
			pii ansLeft = dp(!flag, left + 1, right, keyBin, keyAlg | (1 << type));
			currAns = bestAlg(currAns, ansLeft);
		}
	} 
	else if (islower(cL)){
		int type;
		switch (cL){
			case 'g': type = 0; break;
			case 'r': type = 1; break;
			case 'p': type = 2; break;
			case 'y': type = 3; break;
			default: break;
		}
		if (flag == BIN){
			if (testBit(keyBin, type)){
				pii ansLeft = dp(!flag, left + 1, right, keyBin, keyAlg);
				currAns = bestBin(currAns, ansLeft);
			}
		} else {
			if (testBit(keyAlg, type)){
				pii ansLeft = dp(!flag, left + 1, right, keyBin, keyAlg);
				currAns = bestAlg(currAns, ansLeft);
			}
		}
	}
	//=========================
	//right choice
	if (cR == '#'){
		if (flag == BIN)
			currAns = bestBin(currAns, dp(!flag, left, right - 1, keyBin, keyAlg));
		else
			currAns = bestAlg(currAns, dp(!flag, left, right - 1, keyBin, keyAlg));
	}
	else if (isdigit(cR)){
		int value = cR - '0';
		if (flag == BIN){
			pii ansLeft = dp(!flag, left, right - 1, keyBin, keyAlg); ansLeft.fi += value;
			currAns = bestBin(currAns, ansLeft);
		} else{
			pii ansLeft = dp(!flag, left, right - 1, keyBin, keyAlg); ansLeft.se += value;
			currAns = bestAlg(currAns, ansLeft);
		}

	}
	else if (isupper(cR)){
		int type;
		switch (cR){
			case 'G': type = 0; break;
			case 'R': type = 1; break;
			case 'P': type = 2; break;
			case 'Y': type = 3; break;
			default: break;
		}

		if (flag == BIN){ // bin turns
			pii ansLeft = dp(!flag, left, right - 1, keyBin | (1 << type), keyAlg);
			currAns = bestBin(currAns, ansLeft);
		}
		else{ // alg turns
			pii ansLeft = dp(!flag, left, right - 1, keyBin, keyAlg | (1 << type));
			currAns = bestAlg(currAns, ansLeft);
		}
	} 
	else if (islower(cR)){
		int type;
		switch (cR){
			case 'g': type = 0; break;
			case 'r': type = 1; break;
			case 'p': type = 2; break;
			case 'y': type = 3; break;
			default: break;
		}
		if (flag == BIN){
			if (testBit(keyBin, type)){
				pii ansLeft = dp(!flag, left, right - 1, keyBin, keyAlg);
				currAns = bestBin(currAns, ansLeft);
			}
		} else {
			if (testBit(keyAlg, type)){
				pii ansLeft = dp(!flag, left, right - 1, keyBin, keyAlg);
				currAns = bestAlg(currAns, ansLeft);
			}
		}
	}
	//=========================
	if (currAns == oo) currAns = {0, 0};
	f[left][right][keyBin][keyAlg] = currAns;
	return currAns;
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	//input & init
	cin >> s; lenS = s.length(); s = ' ' + s;
	FOR(int, i, 1, lenS)
		FOR(int, j, i, lenS)
			FOR(int, k, 0, 15)
				FOR(int, l, 0, 15)
					f[i][j][k][l] = {-1, -1};
	//=========================
	pii ans = dp(BIN, 1, lenS, 0, 0);
	if (ans.fi > ans.se) cout << "bin9638\n";
	else if (ans.fi == ans.se) cout << "draw\n";
	else cout << "algorit\n";
	cout << ans.fi - ans.se;
}