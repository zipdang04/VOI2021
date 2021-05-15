#include<bits/stdc++.h>
using namespace std;

const long long INF = 1e18;

struct Dijkstra {
    typedef pair<long long, long long> II;
    vector<vector<II>> adj;
    vector<long long> d;
    int n;

    Dijkstra(int n): n(n) {
        adj.resize(n + 1);
        d.resize(n + 1);
    }

    void addEdge(int u, int v, long long c) {
        adj[u].push_back({v, c});
        adj[v].push_back({u, c});
    }

    void dijkstra(int a) {
        for (int i = 1; i <= n; i++) {
            d[i] = INF;
        }
        d[a] = 0;

        priority_queue<II, vector<II>, greater<II>> pq;
        pq.push({0, a});

        while (!pq.empty()) {
            long long du = pq.top().first;
            int u = pq.top().second;
            pq.pop();

            if (d[u] != du) continue;

            for (auto i: adj[u]) {
                long long uv = i.second;
                int v = i.first;

                if (d[v] > du + uv) {
                    d[v] = du + uv;
                    pq.push({d[v], v});
                }
            }
        }
    }

    void eraseEdge() {
        for (int i = 1; i <= n; i++) {
            adj[i].clear();
        }
    }
};

int a[100005];
long long d[505][505];

void floyd(int n) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i != j) d[i][j] = INF;
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            d[i][j] = min(d[i][j], a[i] * 1ll * a[j]);
        }
    }

    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }
}

int main() {
    freopen("MULTIGRAPH.INP", "r", stdin);
    freopen("MULTIGRAPH.OUT", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    floyd(n);

    Dijkstra dijkstra(n);

    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            dijkstra.addEdge(i, j, a[i] * 1ll * a[j]);
        }
    }

    for (int z = 1; z <= q; z++) {
        int type;
        cin >> type;

        if (n <= 100 && q <= 100) {
            if (type == 1) {
                int u, x;
                cin >> u >> x;
                a[u] = x;

                dijkstra.eraseEdge();

                for (int i = 1; i <= n; i++) {
                    for (int j = i + 1; j <= n; j++) {
                        dijkstra.addEdge(i, j, a[i] * 1ll * a[j]);
                    }
                }
            }
            else {
                int u, v;
                cin >> u >> v;
                dijkstra.dijkstra(u);
                cout << dijkstra.d[v] << "\n";
            }
        }
        else {
            if (type == 1) {
                int u, x;
                cin >> u >> x;
                a[u] = x;

                floyd(n);
            }
            else {
                int u, v;
                cin >> u >> v;
                cout << d[u][v] << '\n';
            }
        }
    }

    return 0;
}

