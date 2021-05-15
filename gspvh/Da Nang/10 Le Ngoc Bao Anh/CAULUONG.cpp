#include<bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
#define pf push_front
#define popb pop_back
#define popf pop_front
#define ins insert
#define all(x) (x).begin(),(x).end()
#define rall(x) (x).rbegin(),(x).rend()
#define unmap unordered_map
#define pq priority_queue
#define minEle min_element
#define maxEle max_element
#define lb lower_bound //first pos >= val
#define ub upper_bound // first pos > val
#define cnt_bit __builtin_popcount
//#pragma GCC optimize("Ofast")  
//#pragma GCC target("avx,avx2,fma")
using namespace std;

int d4x[4] = {1, 0, -1, 0}; int d4y[4] = {0, 1, 0, -1};
int d8x[8] = {0, 1, 1, 1, 0, -1, -1, -1};
int d8y[8] = {1, 1, 0, -1, -1, -1, 0, 1}; 

const long long oo = 1e18;
const int maxN = 2000;
const int MOD = 998244353;

/* Author : Le Ngoc Bao Anh, 10A5, LQD High School for Gifted Student */

struct data
{
    int v, w, id;
};

struct priority
{
    int node; long long d;

    bool operator < (const priority & temp) const {
        return d > temp.d;
    }
};

vector<data> a[maxN];
long long f[maxN][maxN];
int dist[maxN][maxN];
long long cnt[maxN][maxN];
long long currVal[maxN][maxN];
long long ans[maxN * 3];
int n,m;
int u[maxN * 3],v[maxN * 3],w[maxN * 3];

bool cmp(data &_a, data &_b)
{
    return _a.w < _b.w;
}

void dijkstra(int root)
{
    priority_queue<priority> q;
    f[root][root] = 0; q.push({root, 0});
    while(!q.empty()) {
        int node = q.top().node; q.pop();

        for(int i = 0; i < (int)a[node].size(); i++) {
            if(f[root][a[node][i].v] > f[root][node] + a[node][i].w) {
                f[root][a[node][i].v] = f[root][node] + a[node][i].w;
                q.push({a[node][i].v, f[root][a[node][i].v]});
            }
        }
    }
}

bool haveinqueue[2000];

void bfstoans(int root)
{
    queue<int> q; q.push(root);
    while(!q.empty()) {
        int node = q.front(); q.pop(); haveinqueue[node] = false;
        // cout << root << " " << node << " " << currVal[root][node] << " " << cnt[root][node] << endl;

        for(int i = 0; i < (int)a[node].size(); i++) {
            if(f[root][node] + a[node][i].w == f[root][a[node][i].v]) {
                currVal[root][a[node][i].v] += currVal[root][node];
                currVal[root][a[node][i].v] %= MOD;
                cnt[root][a[node][i].v] += currVal[root][node];
                cnt[root][a[node][i].v] %= MOD;
                if(!haveinqueue[a[node][i].v]) q.push(a[node][i].v), haveinqueue[a[node][i].v] = true;
            }
        }

        currVal[root][node] = 0;
    }
}


// long long cal(int node)
// {
//     if(end[node] != -1) return end[node];

//     end[node] = 1;

//     for(int i = 0; i <= (int)getto[node].size(); i++) {
//         long long temp = oo; int pre = getto[node][i];
//         for(int j = 0; j < (int)a[pre].size(); j++) {
//             if(a[pre][j].v == node && a[pre])
//         }
//     }
// }

void solvesub1()
{
    for(int i = 1; i <= n; i++) sort(a[i].begin(), a[i].end(), cmp);

    //calculate dist
    for(int i = 1; i <= n; i++) {
        dijkstra(i);
    }

    //setup
    for(int i = 1; i <= n; i++) {
        currVal[i][i] = 1; cnt[i][i] = 1;
        bfstoans(i);
    }      

    // for(int i = 1; i <= n; i++) {
    //     for(int j = 1; j <= n; j++) cout << cnt[i][j] << " ";
    //     cout << endl;
    // }


    for(int i = 1; i <= m; i++) {
        for(int uu = 1; uu <= n; uu++) {
            for(int vv = 1; vv <= n; vv++) {
                // cout << ans[i] << endl;
                if(w[i] + f[uu][u[i]] + f[v[i]][vv] == f[uu][vv]) ans[i] += (cnt[uu][u[i]]) * (cnt[v[i]][vv]);
                // cout << i << " " << uu << " " << vv << " " << ans[i] << endl;
                // cout << cnt[uu][u[i]] << " " << cnt[v[i]][vv] << endl;
            }
        }
    }

    //cout
    for(int i = 1; i <= m; i++) cout << ans[i] << " ";
}

void Solve()
{
    int Case; cin >> Case;
    cin >> n >> m;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) dist[i][j] = 100000000, f[i][j] = oo;
    }

    for(int i = 1; i <= m; i++) {
        cin >> u[i] >> v[i] >> w[i];
        a[u[i]].pb({v[i], w[i], i});
        dist[u[i]][v[i]] = min(dist[u[i]][v[i]], w[i]);
    }

    if(Case <= 4) {
        solvesub1();
    }
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    freopen("CAULUONG.inp", "r", stdin);
    freopen("CAULUONG.out", "w", stdout);

    // long long TestCase;
    // cin >> TestCase;
    // while(TestCase--)
    Solve();
}