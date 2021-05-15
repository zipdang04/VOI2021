#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v;
    long long c;
    int id;

    bool operator < (const Edge &other) const {
        return c < other.c;
    }
};

Edge edges[300005];
Edge edges2[300005];
int a[300005];
int root[300005];
vector<int> adj[300005];
bool vs[300005], vs2[300005];

int findRoot(int u) {
    if (u > 0) return u;

    while (root[u] >= 0) {
        u = root[u];
    }
    return u;
}

bool merge(int x, int y) {
    x = findRoot(x);
    y = findRoot(y);

    if (x == y) return 0;

    if (root[x] > root[y]) swap(x, y);

    root[x] += root[y];
    root[y] = x;
    return 1;
}

void dfs(int n) {
    vs[n] = 1;
    for (auto i: adj[n]) {
        if (vs[i]) continue;

        vs[i] = 1;
        dfs(i);
    }
}

void sub2(int p) {
    sort(edges + 1, edges + p + 1);

    memset(root, -1, sizeof(root));

    long long res = 0;
    vector<int> path;
    for (int i = 1; i <= p; i++) {
        if (merge(edges[i].u, edges[i].v)) {
            res += edges[i].c;
            path.push_back(edges[i].id);
        }
    }
    cout << res << "\n";
    cout << 0 << "\n";
    cout << "\n";

    cout << path.size() << "\n";

    sort(path.begin(), path.end());
    for (auto i: path) cout << i << ' ';
}

int main() {
    freopen("MOJI.INP", "r", stdin);
    freopen("MOJI.OUT", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(NULL);
    
    int test;
    cin >> test;

    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= k; i++) {
        cin >> a[i];
    }

    int m;
    cin >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        long long c;
        cin >> u >> v >> c;
        edges[i] = {u, v, c, i};

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int p;
    cin >> p;
    for (int i = 1; i <= p; i++) {
        int u, v;
        long long c;
        cin >> u >> v >> c;
        edges2[i] = {u, v, c, i}; 
    }

    if (test == 2) {
        sub2(p);
    }   
    else {
        int cnt = 0;
        for (int i = 1; i <= n; i++) {
            if (!vs[i]) {
                vs[i] = 1;
                cnt++;
                dfs(i);
            }
        }

        sort(edges + 1, edges + m + 1);
        sort(edges2 + 1, edges2 + p + 1);

        memset(root, -1, sizeof(root));

        for (int i = 1; i <= k; i++) {
            root[a[i]] = a[i];
        }

        long long res = 0;
        vector<int> path;
        for (int i = 1; i <= p; i++) {
            if (cnt == k) break;

            if (merge(edges2[i].u, edges2[i].v)) {
                cnt--;
                res += edges[i].c;
                path.push_back(edges2[i].id);
            }
        }

        sort(path.begin(), path.end());

        vector<int> ans;
        memset(vs, 0, sizeof(vs));

        memset(root, -1, sizeof(root));
        for (int i = 1; i <= k; i++) {
            root[a[i]] = a[i];
        }

        for (int i = 1; i <= m; i++) {
            if (merge(edges[i].u, edges[i].v) && (!vs[edges[i].u] || !vs[edges[i].v])) {
                vs[edges[i].u] = vs[edges[i].v] = 1;
                vs2[edges[i].id] = 1;
            }
        }

        for (int i = 1; i <= m; i++) {
            if (!vs2[i]) {
                ans.push_back(i);
                res += edges[i].c;
            }
        }

        sort(ans.begin(), ans.end());

        cout << res << "\n";
        cout << ans.size() << "\n";
        for (auto i: ans) cout << i << ' ';

        cout << "\n";

        cout << path.size() << "\n";
        for (auto i: path) cout << i << ' ';
    }

    return 0;
}