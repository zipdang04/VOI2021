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

#define testBit(n, bit) ((n >> bit) & 1)
#define flipBit(n, bit) (n ^ (1ll << bit))
#define cntBit(n) __builtin_popcount(n)
#define cntBitll(n) __builtin_popcountll(n)
#define randomize mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count());

ifstream inp, out, ans;
int cnt;
int boardSize[10] = {};
vi initPos[10] = {};
vi ansPos[10] = {};

void readInput(){
	int n;
	while (inp >> n){
		boardSize[++cnt] = n;
		initPos[cnt].push_back(0);
		FOR(int, i, 1, n){
			int p; inp >> p;
			initPos[cnt].push_back(p);
		}
	}
	FOR(int, i, 1, cnt){
		// cerr << boardSize[i] << ":";
		// // FOR(int, j, 1, boardSize[i]) cerr << initPos[i][j] << ' '; cerr << '\n';
	}
}

void readOutput(){
	FOR(int, _, 1, cnt){
		ansPos[_].push_back(0);
		FOR(int, i, 1, boardSize[_]){
			int p; out >> p;
			ansPos[_].push_back(p);
		}
		// // FOR(int, j, 1, boardSize[_]) cerr << ansPos[_][j] << ' '; cerr << '\n';
	}
}

void readAnswer(){
}

void checkBoard(int boardNo){
	int size = boardSize[boardNo];
	bool done[size + 1][size + 1] = {};
	FOR(int, i, 1, size){
		if (initPos[boardNo][i] && ansPos[boardNo][i] != initPos[boardNo][i]){
			cout << "Sao lai doi???" << endl;
			exit(1);
		}
		int row = i, col = ansPos[boardNo][i];
		if (done[row][col]){
			cout << "Checkmate!!!" << endl;
			exit(1);
		}

		int x = row, y = col;
		while (x <= size && y <= size){
			done[x][y] = true;
			x++, y++;
		}
		x = row, y = col;
		while (x <= size && y >= 1){
			done[x][y] = true;
			x++, y--;
		}
		x = row, y = col;
		while (x >= 1 && y <= size){
			done[x][y] = true;
			x--, y++;
		}
		x = row, y = col;
		while (x >= 1 && y >= 1){
			done[x][y] = true;
			x--, y--;
		}
	}
}

void check(){
	FOR(int, _, 1, cnt){
		checkBoard(_);
	}
}

int main(int argc, char** argv)
{
	//prepare
	// inp = ifstream("nqueen2.inp");
	// out = ifstream("nqueen2.out");
	// cerr << cnt << ' ' << "done\n";
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