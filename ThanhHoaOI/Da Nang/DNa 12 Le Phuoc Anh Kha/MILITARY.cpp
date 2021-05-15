#include<bits/stdc++.h>
using namespace std;

struct LCA {
    int n, logn = 0;
    vector<vector<int>> adj, p;
    vector<int> h;

    LCA(int n): n(n) {
        while ((1 << logn) <= n) logn++;
        p.assign(n + 1, vector<int>(logn + 1));
        adj.resize(n + 1);
        h.resize(n + 1);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs(int n, int par) {
        h[n] = h[par] + 1;
        p[n][0] = par;
        for (auto i: adj[n]) {
            if (i != par) dfs(i, n);
        }
    }

    void initJumps() {
        for (int j = 1; j <= logn; j++) {
            for (int i = 1; i <= n; i++) {
                p[i][j] = p[p[i][j - 1]][j - 1];
            }
        }
    }

    int lca(int u, int v) {
        if (h[u] < h[v]) swap(u, v);
        if (h[u] > h[v]) {
            for (int i = logn; i >= 0; i--) {
                if (h[p[u][i]] >= h[v]) u = p[u][i];
            }
        }

        for (int i = logn; i >= 0; i--) {
            if (p[u][i] != p[v][i]) {
                u = p[u][i];
                v = p[v][i];
            }
        }

        while (u != v) {
            u = p[u][0];
            v = p[v][0];
        }

        return u;
    }

    int dist(int u, int v) {
        int par = lca(u, v);
        return h[u] + h[v] - 2 * h[par];
    }
};

int a[2005];
bool vs[100005];

int main() {
    freopen("MILITARY.INP", "r", stdin);
    freopen("MILITARY.OUT", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= k; i++) {
        cin >> a[i];
    }

    LCA lca(n);

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        lca.addEdge(u, v);
    }

    lca.dfs(1, 0);
    lca.initJumps();

    int res = 0;
    vector<int> ans;

    for (int i = 1; i <= n; i++) {
        bool ok = true;
        for (int j = 1; j <= k; j++) {
            int val = lca.dist(i, a[j]);
            if (vs[val]) ok = false;
            vs[val] = 1;
        }

        if (ok) {
            res++;
            ans.push_back(i);
        }

        for (int j = 1; j <= k; j++) {
            int val = lca.dist(i, a[j]);
            vs[val] = 0;
        }
    }

    sort(ans.begin(), ans.end());

    cout << res << "\n";
    for (auto i: ans) cout << i << ' ';

    return 0;
}

