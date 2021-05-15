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

ifstream inp, out, ans;

int n;
int a[MAX];

int cntOut, bestOut = 0;
int cntAns, bestAns = 0;

void readInput(){
	inp >> n;
	FOR(int, i, 1, n) inp >> a[i];
}

bool done[MAX] = {};
void readOutput(){
	memset(done, false, sizeof(done));

	out >> cntOut;
	FOR(int, _, 1, cntOut){
		int k; out >> k;
		bestOut = max(bestOut, k);

		FOR(int, i, 1, k){
			int pos; out >> pos;
			if (done[pos]){cout << "Trung vi tri!" << endl; exit(1);}
			done[pos] = true;

			if (a[pos] > bestOut){cout << "Khong hop dieu kien cua de!" << endl; exit(1);}
		}
	}
}

void readAnswer(){
	memset(done, false, sizeof(done));

	ans >> cntAns >> bestAns;
}

void check(){
	if (cntOut < cntAns) {cout << "Khong toi uu!" << endl; exit(1);}
	if (cntOut == cntAns && bestOut > bestAns) {cout << "Khong toi uu!" << endl; exit(1);}
}

int main(int argc, char** argv)
{
    // inp = ifstream("teams.inp");
    // out = ifstream("teams.out");
    // ans = ifstream("teams.ans");
    inp = ifstream(argv[1]);
    out = ifstream(argv[2]);
    ans = ifstream(argv[3]);
	//=========================
	//input
	readInput();
	readOutput();
	readAnswer();
	//=========================
	check();
    return 0;
}