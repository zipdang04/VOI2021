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
int m, n;
vi work[MAX];
vi hAble[MAX];

int quanOut, quanAns;
int assOut[MAX], assAns[MAX];

void readInput(){
	inp >> m >> n;
	int h, w;
	while (inp >> h >> w){
		work[h].push_back(w);
		hAble[w].push_back(h);
	}
}

void readOutput(){
	out >> quanOut;
	FOR(int, i, 1, n) out >> assOut[i];
}

void readAnswer(){
	ans >> quanAns;
	FOR(int, i, 1, n) ans >> assAns[i];
}

bool human[MAX] = {};
void check(){
	if (quanAns != quanOut){
		cout << "Khac so luong so voi dap an.";
		exit(1);
	}
	
	int cnt = 0;
	FOR(int, job, 1, n){
		int h = assOut[job];
		if (!h) continue;
		if (h < 1 || h > m){
			cout << "Chi so cua nguoi nam ngoai gioi han.";
			exit(1);
		}
		if (human[h]){
			cout << "Mot nguoi khong the co qua hai viec.";
			exit(1);
		}

		bool okay = false;
		for (int person: hAble[job])
			if (person == h){
				okay = true; break;
			}
		if (!okay){
			cout << "Nguoi " << h << " khong biet lam viec " << job << ".\n";
			exit(1);
		}
		human[h] = true; cnt++;
	}
	
	if (cnt != quanOut){
		cout << "Gian doi! Biet dap an nhung khong truy vet duoc, ga` qua!";
		exit(1);
	}
	return;
}

int main(int argc, char** argv)
{
	//prepare
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