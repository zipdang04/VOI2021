#include <bits/stdc++.h>
using namespace std;

#define FOR(type, ind, a, b) for (type ind = (a); ind <= (b); ind++)
#define FORD(type, ind, a, b) for (type ind = (a); ind >= (b); ind--)
#define testBit(n, bit) (((n) >> (bit)) & 1)

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;

const int MAX = 200005;
const int BIT = 18;

int n, m;
vi graph[MAX];
int num[MAX], low[MAX], ti = 0;
int listNode[MAX];
bool joint[MAX];

void tarjan(int node, int parent){
	num[node] = low[node] = ++ti;
	listNode[ti] = node;
	int numOfChild = 0;
	for (int child: graph[node]){
		if (num[child])
			low[node] = min(low[node], num[child]);
		else{
			numOfChild++;
			tarjan(child, node);
			low[node] = min(low[node], low[child]);

			if (node == parent){
				if (numOfChild > 1) joint[node] = true;
			} else {
				if (low[child] >= num[node])
					joint[node] = true;
			}
		}
	}
}

int u;
int v[MAX], k;
int par[MAX];
int lvl[MAX];
int rmq[BIT + 1][MAX];
void buildTree(){
	FOR(int, i, 1, n)
		par[i] = listNode[low[i]];
}
int calLvl(int node){
	if (lvl[node]) return lvl[node];
	return calLvl(par[node]) + 1;
}
void initRMQ(){
	FOR(int, i, 1, n)
		rmq[0][i] = par[i];
	FOR(int, bit, 1, BIT)
		FOR(int, i, 1, n)
			rmq[bit][i] = rmq[bit - 1][rmq[bit - 1][i]];
}
void init(){
	tarjan(1, 1);
	buildTree(); 
	
	par[1] = 0; lvl[1] = 1;
	FOR(int, i, 2, n)
		lvl[i] = calLvl(i);
	
	initRMQ();
}

int jump(int node, int dist){
	FOR(int, bit, 0, BIT){
		if (dist & 1) node = rmq[bit][node];
		dist >>= 1;
	}
	return node;
}

int jumpToHeight(int node, int h){
	int currH = lvl[node];
	if (currH <= h) return node;
	return jump(node, currH - h);
}

main(){
	freopen("cities.inp", "r", stdin);
	freopen("cities.out", "w", stdout);
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	
	cin >> n >> m;
	FOR(int, _, 1, m){
		int u, v; cin >> u >> v;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}

	init();
	int q; cin >> q;
	FOR(int, _, 1, q){
		cin >> u >> k;
		FOR(int, i, 1, k) cin >> v[i];
		if (!joint[u]) {cout << "Yes\n"; continue;}
		
		if (u == 1){
			FOR(int, i, 1, k)
				v[i] = jumpToHeight(v[i], 2);
			sort(v + 1, v + 1 + k);
			bool same = true;
			FOR(int, i, 2, k)
				if (v[i] != v[i - 1])
					same = false;
			cout << (same ? "Yes\n" : "No\n");
		} else {
			int jointH = lvl[u];
			bool flag = true;
			FOR(int, i, 1, k){
				int tmp = jumpToHeight(v[i], jointH);
				if (tmp == u){
					flag = false; break;
				}
			}

			cout << (flag ? "Yes\n" : "No\n");
		}
	}
}