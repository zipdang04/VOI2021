#include<bits/stdc++.h>
using namespace std;

typedef long long Int;
#define task "MOJI"

const int MAX = 3e5 + 500;
int num_nodes, num_shops;
vector<int> shops;

struct Graph {
	int num_edges;
	int from[MAX], to[MAX], weight[MAX];
	Graph() {}
	void input() {
		cin >> num_edges;
		for (int i = 0; i < num_edges; i++) cin >> from[i] >> to[i] >> weight[i];
	}
};
Graph original, plan;

void Subtask1() {
	int sum = original.num_edges + plan.num_edges;
	Int ans = 2e18;
	vector<int> i_org, i_pla;
	
	for (int msk = 0; msk < (1 << sum); msk++) {
		Int cost = 0;
		vector<int> j_org, j_pla;
		vector<int> adj[num_nodes + 1];
		
		for (int i = 0; i < sum; i++) {
			int bit = (msk >> i) & 1;
			if (i < original.num_edges) {
				if (bit) {
					cost += original.weight[i];
					j_org.push_back(i + 1);	
				}
				else {
					adj[original.from[i]].push_back(original.to[i]);
					adj[original.to[i]].push_back(original.from[i]);
				}
			}
			else {
				if (bit) {
					int j = i - original.num_edges;
					cost += plan.weight[j];
					j_pla.push_back(j + 1);
					adj[plan.from[j]].push_back(plan.to[j]);
					adj[plan.to[j]].push_back(plan.from[j]);
				}
			}
		}
		
		bool check = true;
		int cnt_vis = 0;
		vector<bool> vis(num_nodes + 1);
		for (int u : shops) if (!vis[u]) {
			queue<int> bfs;
			vis[u] = true; bfs.push(u);
			int cnt_edges = 0, cc_force = 0;
			while (bfs.size()) {
				int cur = bfs.front(); bfs.pop();
				++cc_force;
				for (int nxt : adj[cur]) {
					++cnt_edges;	
					if (!vis[nxt]) { vis[nxt] = true; bfs.push(nxt); }
				}
			}
			check &= 2 * (cc_force - 1) == cnt_edges;
			cnt_vis += cc_force;
		} else check = false; //each shop must be in a separate connected component
		check &= cnt_vis == num_nodes;
		
		if (check and cost < ans) {
			ans = cost;
			i_org = j_org, i_pla = j_pla;
		}
	}
	
	cout << ans << '\n';
	cout << i_org.size() << '\n';
	for (int i : i_org) cout << i << ' '; cout << '\n';
	cout << i_pla.size() << '\n';
	for (int i : i_pla) cout << i << ' '; cout << '\n';
}

//SUBTASK 2
struct cmp1 {
	bool operator() (int id_a, int id_b)  {
		return (plan.weight[id_a] == plan.weight[id_b]) ? id_a < id_b : (plan.weight[id_a] < plan.weight[id_b]);
	}
};

int root[MAX], rnk[MAX];
int find_root(int u) {
	return (u == root[u]) ? u : root[u] = find_root(root[u]);
}

bool merge_set(int u, int v) {
	u = find_root(u), v = find_root(v);
	if (u == v) return false;
	if (rnk[u] < rnk[v]) swap(u, v);
	root[v] = u;
	rnk[u] += (rnk[u] == rnk[v]);
	return true;
}

void Subtask2() {
	vector<int> indices;
	indices.resize(plan.num_edges);
	iota(indices.begin(), indices.end(), 0);
	sort(indices.begin(), indices.end(), cmp1());
	
	for (int i = 1; i <= num_nodes; i++) root[i] = i, rnk[i] = 0;
	
	Int answer = 0;
	vector<int> pick;
	
	for (int i : indices)
		if (merge_set(plan.from[i], plan.to[i])) {
			pick.push_back(i + 1);	
			answer += plan.weight[i];
		}
	cout << answer << "\n0\n\n";
	cout << (int) pick.size() << '\n';
	for (int id : pick) cout << id << ' ';
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	freopen(task".inp", "r", stdin);
	freopen(task".out", "w",stdout);

	int theta; cin >> theta;
	cin >> num_nodes;
	
	cin >> num_shops;
	shops.resize(num_shops);
	for (int i = 0; i < num_shops; i++) cin >> shops[i];
	
	original.input();
	plan.input();
	
//	if (theta == 1) Subtask1(); else
//	if (theta == 2) Subtask2(); else ;
//	Subtask2();
}

