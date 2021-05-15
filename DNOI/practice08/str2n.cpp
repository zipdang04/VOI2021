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

struct Node{
	set<int> pos;
	Node *parent = nullptr;
	Node *child[26] = {};
} *root = new Node;

typedef pair<pii, Node*> Data;

int n;
string str[MAX];
Data ptr[MAX];
bool done[MAX];

void add(string s, int pos){
	Node *curr = root; int len = s.length();
	FOR(int, i, 0, len - 1){
		char c = s[i] - 'a';
		if (curr -> child[c] == nullptr)
			curr -> child[c] = new Node;
		curr -> child[c] -> parent = curr;
		curr = curr -> child[c];
	}
	curr -> pos.insert(pos);
	ptr[pos] = {{len, pos}, curr};
} 

bool cmp(Data a, Data b){
	return a.fi > b.fi;
}

void goUp(Node *node, int pos){
	done[pos] = true;
	while (true){
		if (node -> pos.size()){
			int child = *(node -> pos.begin());
			node -> pos.erase(node -> pos.begin());
			
			done[child] = true;
			cout << child << ' ' << pos << '\n';
			break;
		} else node = node -> parent;
	}
}
main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n; n *= 2;
	int maLen = 0;
	FOR(int, _, 1, n){
		cin >> str[_];
		add(str[_], _);
	}
	sort(ptr + 1, ptr + n + 1, cmp);
	FOR(int, _, 1, n){
		Data curr = ptr[_];
		int pos = curr.fi.se; Node *node = curr.se;
		if (done[pos]) continue;
		node -> pos.erase(node -> pos.find(pos));
		goUp(node, pos);
	}
}