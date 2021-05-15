#include<bits/stdc++.h>
using namespace std;

typedef long long Int;
const int MOD = 2004010501;//>2e9

#define task "MILITARY"
const int MAX = (int) 1e5 + 500;
int num_nodes, num_camps;
int camps[MAX];

vector<int> adj[MAX];

int height[MAX];
void dfs(int u, int par) {
	height[u] = height[par] + 1;
	for (int v : adj[u]) if (v != par and height[v] == 0) dfs(v, u);
}

namespace Subtask1 {
	int dist[MAX], cnt[MAX];
	
	void solve() {
		queue<int> bfs;
		vector<int> result;
		for (int u = 1; u <= num_nodes; u++) {
			
			for (int v = 1; v <= num_nodes; v++) dist[v] = -1;
			dist[u] = 0;
			
			bfs.push(u);
			while (!bfs.empty()) {
				int cur = bfs.front(); bfs.pop();
				for (int nxt : adj[cur]) if (dist[nxt] == -1) {
					dist[nxt] = dist[cur] + 1; bfs.push(nxt);
				}
			}
 				
 			for (int i = 1; i <= num_camps; i++) ++cnt[dist[camps[i]]];
 			
			bool check = true;
 			for (int d = 1; d <= num_nodes; d++) check &= cnt[d] <= 1;
 			if (check) result.push_back(u);
 			
 			for (int i = 1; i <= num_camps; i++) cnt[dist[camps[i]]] = 0;
		}	
		cout << (int) result.size() << '\n';
		for (int node : result) cout << node << ' ';
	}
}

const int INF = 1e9;
namespace Subtask2 {
	
	int euler[2 * MAX], walk_count = 0;
	int appear[MAX];
	void re_dfs(int u) {
		appear[u] = ++walk_count;
		euler[walk_count] = height[u];
//		cerr << "At node " << u << ", height = " << height[u] << '\n';
//		cerr << "He appears at " << appear[u] << '\n'; 
		
		for (int v : adj[u]) if (height[v] == height[u] + 1) {
			re_dfs(v);
			euler[++walk_count] = height[u];
		}
	}
	
	const int MLOG = 19;
	int POW2[MLOG], LOG2[1 << (MLOG + 1)] = {}; 
	int Min[MLOG][2 * MAX];
	
	void build_rmq() {
		POW2[0] = 1;
		for (int d = 1; d < MLOG; d++) POW2[d] = 2 * POW2[d - 1];	
		for (int d = 0; d < MLOG; d++) LOG2[POW2[d]] = d;
		for (int i = 1; i <= walk_count; i++) 
			LOG2[i] = max(LOG2[i], LOG2[i - 1]);
		
		for (int i = 1; i <= walk_count; i++) Min[0][i] = euler[i];
		
		for (int tier = 1; tier < MLOG; tier++) {
			for (int i = 1; i <= walk_count; i++) Min[tier][i] = INF;
			for (int i = 1, j = POW2[tier]; j <= walk_count; j++, i++) 
				Min[tier][i] = min(Min[tier - 1][i], Min[tier - 1][i + POW2[tier - 1]]);
		}
	}
	
	int query_rmq(int l, int r) {
		int tier = LOG2[r - l + 1];
		return min(Min[tier][l], Min[tier][r - POW2[tier] + 1]);
	}
	
	int root_to_lca(int u, int v) {
		int Left = appear[u], Right = appear[v];
		if (Left > Right) swap(Left, Right);
		return query_rmq(Left, Right);
	}
	
	int dist(int u, int v) {
		return height[u] + height[v] - 2 * root_to_lca(u, v);
	}
	
	int cnt[MAX];
	void solve() {
		re_dfs(1);
		build_rmq();
//		for (int i = 1; i <= walk_count; i++) cerr << euler[i]; cerr << "\n That's the euler path\n";
		
		vector<int> result;
		for (int u = 1; u <= num_nodes; u++) {
			int brk = num_camps;
			bool check = true;
			
			for (int i = 1; i <= num_camps; i++) {
				int get = dist(u, camps[i]);
				++cnt[get];
				if (cnt[get] > 1) { check = false; brk = i; break; }
			}
			
			if (check) result.push_back(u);
			
			for (int i = 1; i <= brk; i++) {
				int get = dist(u, camps[i]); 
				--cnt[get];
			}
		}
		
		cout << (int) result.size() << '\n';
		for (int node : result) cout << node << ' ';
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	freopen(task".inp", "r", stdin);
	freopen(task".out", "w", stdout);

	cin >> num_nodes >> num_camps;
	for (int i = 1; i <= num_camps; i++) cin >> camps[i];
	
	for (int u, v, i = 1; i < num_nodes; i++) {
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}	
	
	dfs(1, 0);
	
	if (num_nodes <= 500) Subtask1 :: solve(); else
	Subtask2 :: solve();
}
