#include<bits/stdc++.h>
using namespace std;

typedef long long Int;
const Int oo = 1e18;
const int MOD = 2004010501;//>2e9

#define task "MULTIGRAPH"
const int MAX = (int) 1e5 + 500;
int num_nodes;
int weight[MAX];

int num_queries;
int qutyp[MAX], param1[MAX], param2[MAX]; 

const int MIN = 505;
Int dist[MIN][MIN];

struct State {
	Int weight; int pos;
	State(Int weight, int pos) : weight(weight), pos(pos) {
	}
	bool operator < (const State& other) const {
		return other.weight < weight;
	}
};

priority_queue<State> heap;	
void dijkstra(int u) {
	for (int v = 0; v <= num_nodes; v++) dist[u][v] = (v == u) ? 0 : oo;
	heap.push(State(0, u));
	while (!heap.empty()) {
		State cur = heap.top(); heap.pop();
		if (dist[u][cur.pos] != cur.weight) continue;
		
		for (int nxt = 1; nxt <= num_nodes; nxt++) {
			int relax = cur.weight + (Int) weight[cur.pos] * weight[nxt];
			if (relax < dist[u][nxt]) {
				dist[u][nxt] = relax;
				heap.push(State(relax, nxt));
			}
		}
	}
}

void compute() {
	for (int u = 1; u <= num_nodes; u++) dijkstra(u);
}

void Subtask3() {
	compute();
	for (int q = 1; q <= num_queries; q++) {
		if (qutyp[q] == 1) {
			weight[param1[q]] = param2[q];
			compute();
		}
		else cout << dist[param1[q]][param2[q]] << '\n';
	}
}

void Subtask1() {
	for (int q = 1; q <= num_queries; q++) {
		if (qutyp[q] == 1) weight[param1[q]] = param2[q];
		else {
			dijkstra(param1[q]);
			cout << dist[param1[q]][param2[q]] << '\n';
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	freopen(task".inp", "r", stdin);
	freopen(task".out", "w", stdout);

	cin >> num_nodes >> num_queries;
	for (int u = 1; u <= num_nodes; u++) cin >> weight[u];
	
	for (int q = 1; q <= num_queries; q++) 
		cin >> qutyp[q] >> param1[q] >> param2[q];
		
	bool subtask1 = (num_nodes <= 100);
	
	int cnt_update_query = 0;
	for (int q = 1; q <= num_queries; q++) cnt_update_query += qutyp[q] == 1;
	
	bool subtask3 = subtask1 & (cnt_update_query <= 10);
	subtask1 &= num_queries <= 100;
	
	if (subtask3) Subtask3(); else
	if (subtask1) Subtask1();
}
