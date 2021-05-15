#include<bits/stdc++.h>
using namespace std;

#define pii pair<long long , long long>
#define pll pair<long long , pii>

//Variables
const int mxN = 1e6 + 5;
const int MOD = 1e9 + 7;
const long long oo = 1e18;
const int d4i[4] = {-1 , 0 , 1 , 0} , d4j[4] = {0 , 1 , 0 , -1};
const int d8i[8] = {-1 , -1 , 0 , 1 , 1 , 1 , 0 , -1} , d8j[8] = {0 , 1 , 1 , 1 , 0 , -1 , -1 , -1};

int TestCase , SubTask;
int n , q , x , y , u , v;
long long a[4][mxN] , cost[4][mxN] , dp[4][mxN];

void dijkstra(int u , int v) {
	for (int i = 1; i <= 3; i++) {
		for (int j = 1; j <= n; j++) {
			cost[i][j] = oo;
			dp[i][j] = -oo;
		}
 	}
	dp[u][v] = a[u][v];
	cost[u][v] = 0;
	priority_queue<pll , vector<pll> , greater<pll>> pq;
	
	pq.push(make_pair(cost[u][v] , make_pair(u , v)));
	long long x , y , cp;
	while (!pq.empty()) {
        pll p = pq.top();
        pq.pop();
		cp = p.first;
		u = p.second.first;
		v = p.second.second;
		if (cost[u][v] != cp) continue;
		for (int e = 0; e < 4; e++) {
			x = u + d4i[e];
			y = v + d4j[e];
			if (x < 1 || y < 1 || x > 3 || y > n) continue;
			if (cost[x][y] == cost[u][v] + 1 && dp[x][y] < dp[u][v] + a[x][y]) {
				dp[x][y] = dp[u][v] + a[x][y];
				pq.push(make_pair(cost[x][y] , make_pair(x , y)));
			}
			if (cost[x][y] > cost[u][v] + 1) {
				cost[x][y] = cost[u][v] + 1;
				dp[x][y] = dp[u][v] + a[x][y];
				pq.push(make_pair(cost[x][y] , make_pair(x , y)));
			}
		}		
    }	
}

void Solve() {
//	cin >> SubTask;
	cin >> n >> q;
	for (int i = 1; i <= 3; i++) {
		for (int j = 1; j <= n; j++) cin >> a[i][j];
	}
	while (q--) {
		cin >> u >> v >> x >> y;
		dijkstra(u , v);
		cout << dp[x][y] << "\n";
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	freopen("BONUS3ROWS.INP" , "r" , stdin);
	freopen("BONUS3ROWS.OUT" , "w" , stdout);
//	cin >> TestCase;
	TestCase = 1;
	while(TestCase--)
		Solve();
	return 0;
}



