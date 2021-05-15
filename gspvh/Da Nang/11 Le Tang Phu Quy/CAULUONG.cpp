#include<bits/stdc++.h>
using namespace std;

typedef long long Int;
#define task "CAULUONG"

const int INF = 1e9;
const int MAX = 5000;
const int MOD = 998244353;

template<typename type> bool minimize(type& var, const type& val) {
	if (val < var) { var = val; return true; } return false;
}

int num_nodes, num_edges;
int from[MAX], to[MAX], edge[MAX];

struct Arc {
	int to, weight;
	Arc(int to = 0, int weight = 0) : to(to), weight(weight) {
	}
};
//vector<Arc> adj[MAX]; is separated for each subtask
 
struct State {
	int pos, weight;
	State(int pos, int weight) : pos(pos), weight(weight) {
	}
	bool operator< (const State& other) const {
		return other.weight < weight;
	}
};

class Subtask3 {
public : 
	vector<Arc> adj[MAX];
	Subtask3() { for (int i = 1; i <= num_nodes; i++) adj[i].clear(); }
	
	vector<int> dist[MAX], cnt[MAX];
	
	void find_shortest_paths(int st, vector<int>& dist, vector<int>& cnt) {
		dist.assign(num_nodes + 1, INF);
		cnt.assign(num_nodes + 1, 0);
		
		dist[st] = 0, cnt[st] = 1;
		priority_queue<State> heap;
		heap.push(State(st, 0));	
		
		while (!heap.empty()) {
			State cur = heap.top(); heap.pop();
			if (dist[cur.pos] != cur.weight) continue;
			
			for (auto arc : adj[cur.pos]) {
				int relax = cur.weight + arc.weight;
				if (minimize(dist[arc.to], relax)) {
					cnt[arc.to] = cnt[cur.pos];
					heap.push(State(arc.to, relax));
				}
				else if (dist[arc.to] == relax) cnt[arc.to] += cnt[cur.pos];
			}
		}
	}
	
	void solve() {
		for (int i = 1; i <= num_edges; i++)
			adj[from[i]].push_back(Arc(to[i], edge[i]));	
		
		for (int i = 1; i <= num_nodes; i++) find_shortest_paths(i, dist[i], cnt[i]);
		for (int i = 1; i <= num_edges; i++) {
			Int answer = 0;
			for (int u = 1; u <= num_nodes; u++)
				for (int v = 1; v <= num_nodes; v++) 
					if (dist[u][from[i]] + edge[i] + dist[to[i]][v] == dist[u][v])
						answer += ((Int) cnt[u][from[i]] * cnt[to[i]][v]) % MOD,
						answer %= MOD;
			cout << answer << '\n';
		}
	}
};

class Subtask2 {
public : 
	vector<Arc> adj[MAX];
	Subtask2() { for (int i = 1; i <= num_nodes; i++) adj[i].clear(); }
	
	int cnt[MAX], ans[MAX];

	void cal_dp(int u, int height) {
		cnt[u] = 1;
		for (auto arc : adj[u]) {
			cal_dp(arc.to, height + 1);
			cnt[u] += cnt[arc.to];
			ans[arc.weight] = ((Int) height * cnt[arc.to]) % MOD;
		}
	}
	
	void solve() {
		for (int i = 1; i <= num_edges; i++) 
			adj[from[i]].push_back(Arc(to[i], i));
		cal_dp(1, 1);
		for (int i = 1; i <= num_edges; i++) cout << ans[i] << '\n';
	}
};

class Subtask4 {
public : 
	vector<Arc> adj[MAX];
	Subtask4() { for (int i = 1; i <= num_nodes; i++) adj[i].clear(); }
	
	vector<int> dist[MAX], cnt[MAX];
	
	void find_shortest_paths(int st, vector<int>& dist, vector<int>& cnt) {
		dist.assign(num_nodes + 1, INF);
		cnt.assign(num_nodes + 1, 0);
		
		dist[st] = 0, cnt[st] = 1;
		priority_queue<State> heap;
		heap.push(State(st, 0));	
		
		while (!heap.empty()) {
			State cur = heap.top(); heap.pop();
			if (dist[cur.pos] != cur.weight) continue;
			
			for (auto arc : adj[cur.pos]) {
				int relax = cur.weight + arc.weight;
				if (minimize(dist[arc.to], relax)) {
					cnt[arc.to] = cnt[cur.pos];
					heap.push(State(arc.to, relax));
				}
				else if (dist[arc.to] == relax) cnt[arc.to] += cnt[cur.pos];
			}
		}
	}
	
	int cnt_to[MAX], cnt_from[MAX];
	void solve() {
		for (int i = 1; i <= num_edges; i++) 
			adj[from[i]].push_back(Arc(to[i], edge[i]));
			
		for (int u = 1; u <= num_nodes; u++) {
			find_shortest_paths(u, dist[u], cnt[u]);
			for (int v = 1; v <= num_nodes; v++) 
				(cnt_from[u] += cnt[u][v]) %= MOD,
				(cnt_to[u] += cnt[u][v]) %= MOD;
		} 
		
		for (int i = 1; i <= num_edges; i++) {
			int answer = ((Int) cnt_to[from[i]] * cnt_from[to[i]]) % MOD;
			cout << answer << '\n';
		}
	}
};

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l, int r) {
	return uniform_int_distribution<int>(l, r) (rng);
}

void proof_of_correctness() {
	int num_tests = 1;
	for (int ttcv = 1; ttcv <= num_tests; ttcv++) {
		num_nodes = rand_int(2, 10);
		num_edges = rand_int(1, 10);
		for (int i = 1; i <= num_edges; i++) {
			from[i] = rand_int(1, num_nodes);
			do {
				to[i] = rand_int(1, num_nodes);
			} while (to[i] == from[i]);
			if (from[i] > to[i]) swap(from[i], to[i]);
			edge[i] = rand_int(1, (int) 100);
		} 
		cerr << "Input : " << num_nodes << ',' << num_edges << '\n';
		for (int i = 1; i <= num_edges; i++) cerr << from[i] << ' ' << to[i] << ' ' << edge[i] << '\n'; 
		Subtask4().solve();
		cerr << "That is subtask4\n";
		Subtask3().solve();
		cerr << "End for test " << ttcv << '\n'; 
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
//	proof_of_correctness();
	
	freopen(task".inp", "r", stdin);
	freopen(task".out", "w",stdout);

	int theta; cin >> theta;
	cin >> num_nodes >> num_edges;
	for (int i = 1; i <= num_edges; i++) cin >> from[i] >> to[i] >> edge[i];

	if (theta == 1 or theta == 3) Subtask3().solve(); else
	if (theta == 2) Subtask2().solve(); else 
	if (theta == 4) Subtask4().solve(); else; //subtask4 is wrong
}

