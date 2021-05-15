#include<bits/stdc++.h>
using namespace std;

//Variables
const int mxN = 1e5 + 5;
const int mxK = 2000 + 5;
const int MOD = 1e9 + 7;
const long long oo = 1e18;
const int d4i[4] = {-1 , 0 , 1 , 0} , d4j[4] = {0 , 1 , 0 , -1};
const int d8i[8] = {-1 , -1 , 0 , 1 , 1 , 1 , 0 , -1} , d8j[8] = {0 , 1 , 1 , 1 , 0 , -1 , -1 , -1};

int TestCase , SubTask;
int n , k;
int military[mxK] , p[mxN][20] , level[mxN] , save[mxN];
bool visited[mxN];
vector<int> path;
vector<int> adj[mxN];

void dfs(int node , int parents) {
	for (auto child : adj[node]) {
		if (child == parents) continue;
		p[child][0] = node;
		level[child] = level[node] + 1;
		dfs(child , node);
	}	
}

void precal() {
	level[1] = 1;
	dfs(1 , 0);
	for (int k = 1; k <= 19; k++) {
		for (int i = 1; i <= n; i++) {
			p[i][k] = p[p[i][k - 1]][k - 1];
		}
	}
}

int LCA(int x , int y) {
	for (int k = 19; k >= 0; k--)
		while (level[p[x][k]] >= level[y]) x = p[x][k]; 
	for (int k = 19; k >= 0; k--)
		while (level[p[y][k]] >= level[x]) y = p[y][k];
	for (int k = 19; k >= 0; k--) if (p[x][k] ^ p[y][k]) {
		x = p[x][k];
		y = p[y][k];
	}
	while (x ^ y) {
		x = p[x][0];
		y = p[y][0];
	}
	return x;
}

int dist(int x , int y) {
	int anc = LCA(x , y);
	return (level[x] + level[y] - 2 * level[anc]);
}

void sub1() {
	for (int i = 1; i <= n; i++) {
		bool tie = true;
		int len = 0;
		for (int j = 1; j <= k; j++) {
			int kc = dist(i , military[j]);
			if (visited[kc]) {
				tie = false;
				break;
			}
			save[++len] = kc;
			visited[kc] = true;
		}
		if (tie) path.push_back(i);
		for (int j = 1; j <= len; j++) visited[save[j]] = false;
	}
	cout << path.size() << "\n";
	for (auto res : path) cout << res << " ";
	exit(0);	
}

void Solve() {
//	cin >> SubTask;
	cin >> n >> k;
	for (int i = 1; i <= k; i++) cin >> military[i];
	for (int i = 1; i < n; i++) {
		int u , v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	precal();
	sub1();
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	freopen("MILITARY.INP" , "r" , stdin);
	freopen("MILITARY.OUT" , "w" , stdout);
//	cin >> TestCase;
	TestCase = 1;
	while(TestCase--)
		Solve();
	return 0;
}



