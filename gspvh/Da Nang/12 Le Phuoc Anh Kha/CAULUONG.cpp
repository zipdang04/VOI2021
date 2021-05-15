#include <bits/stdc++.h>
using namespace std;

const long long MOD = 998244353;
const long long INF = 1e18;

struct Edge
{
    int u, v;
    long long c;
};

struct Dijkstra {
    typedef pair<long long, long long> II;
    typedef pair<long long, II> III;
    int n, m;
    vector<vector<II>> adj;
    vector<long long> d;
    vector<long long> cnt;

    Dijkstra(int n, int m): n(n), m(m) {
        adj.resize(n + 1);
        d.resize(n + 1);
        cnt.resize(n + 1);
    }

    void addEdge(int u, int v, long long c) {
        adj[u].push_back({v, c});
    }

    void dijkstra(int a) {
        priority_queue<III, vector<III>, greater<III>> pq;

        for (int i = 1; i <= n; i++) {
            d[i] = INF;
        }

        for (int i = 1; i <= m; i++) {
            cnt[i] = 1;
        }

        // d[a] = 0;
        // pq.push({0, 1, a});
        // while (!pq.empty()) {
        //     long long du = pq.top().first;
        //     int u 
        // }
    }
};

vector<int> adj[2005];
int cnt[1505][1505];
long long minEdge[1505][1505];

int main() {
    freopen("CAULUONG.INP", "r", stdin);
    freopen("CAULUONG.OUT", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(NULL);
    
    int test;
    cin >> test;

    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            minEdge[i][j] = 1e18;
        }
    }

    vector<Edge> edges;
    for (int i = 1; i <= m; i++) {
        int u, v;
        long long c;
        cin >> u >> v >> c;

        adj[u].push_back(v);
        edges.push_back({u, v, c});

        if (minEdge[u][v] > c) {
            minEdge[u][v] = c;
            cnt[u][v] = 1;
        }
        else if (minEdge[u][v] == c) {
            cnt[u][v]++;
        }
    }

    if (test == 2) {
        for (auto e: edges) {
            if (e.c != minEdge[e.u][e.v]) cout << 0 << "\n";
            else {
                cout << n - 1 - cnt[e.u][e.v] + 1 << '\n';
            }
        }
    }
    else {
        for (int i = 1; i <= m; i++) {
            cout << n - 1 << ' ';
        }
    }

    return 0;
}