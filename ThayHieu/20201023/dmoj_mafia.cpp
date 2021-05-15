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

#define MAX 202
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

bool blockOut[MAX];
bool blockAns[MAX];

int n, m, a, b;
int c[MAX];
vi graph[MAX];

void readInput(){
	inp >> n >> m >> a >> b;
	FOR(int, i, 1, n) cin >> c[i];
	FOR(int, i, 1, m) {
		int u, v; cin >> u >> v;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
}

void readOutput(){
	int node;
	while (out >> node){
		if (blockOut[node]){cout << "Lap dinh."; exit(1);}
		blockOut[node] = true;
	}
}

void readAnswer(){
	int node;
	while (ans >> node){
		if (blockAns[node]){cout << "Lap dinh."; exit(1);}
		blockAns[node] = true;
	}
}

int main(int argc, char** argv)
{
	//make input, output, answer
    inp = ifstream(argv[1]);
    out = ifstream(argv[2]);
    ans = ifstream(argv[3]);
	//=========================
	//read
	readInput();
	readOutput();
	// 
	//=========================
    return 0;
}