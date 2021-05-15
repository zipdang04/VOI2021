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
#define vitural 300010
//#pragma GCC optimize("Ofast")  
//#pragma GCC target("avx,avx2,fma")
using namespace std;

int d4x[4] = {1, 0, -1, 0}; int d4y[4] = {0, 1, 0, -1};
int d8x[8] = {0, 1, 1, 1, 0, -1, -1, -1};
int d8y[8] = {1, 1, 0, -1, -1, -1, 0, 1}; 

const long long oo = 1e18;
const long long maxN = 1e6;

/* Author : Le Ngoc Bao Anh, 10A5, LQD High School for Gifted Student */

struct edge
{
    int u, v, w, id;
};

edge edges[maxN];
edge edgesadd[maxN];
int row[maxN];
int root[maxN];
vector<int> ansadd;
vector<int> ansdel;
long long debug[maxN];

bool cmp1(edge &_a, edge &_b)
{
    if(_a.w == _b.w) return _a.id > _b.id;
    return _a.w > _b.w;
}

bool cmp2(edge &_a, edge &_b)
{
    if(_a.w == _b.w) return _a.id < _b.id;
    return _a.w < _b.w;
}

int findRoot(int u) {
    if(root[u] != u) root[u] = findRoot(root[u]);
    return root[u];
}

void UnionSet(int u, int v)
{
    u = findRoot(u); v = findRoot(v);
    if(u == v) return;

    if(row[u] == row[v]) row[u]++;
    if(row[u] < row[v]) root[u] = v;
    else root[v] = u;
}

void UnionSetAdd(int u, int v)
{
    u = findRoot(u); v = findRoot(v);
    if(u == v) return;

    if(row[u] == row[v]) row[u]++;
    if(row[u] < row[v]) root[u] = v;
    else root[v] = u;
}

void Solve()
{
    int n,shop,u,v,w,m,q;
    long long tt = 0,weights = 0;
    cin >> n;
    row[vitural] = 2;
    for(int i = 1; i <= n; i++) root[i] = i, row[i] = 1;

    cin >> shop;
    for(int i = 1; i <= shop; i++) {
        cin >> u;
        root[u] = vitural;
        row[u] = 1;
    }

    cin >> m;
    for(int i = 1; i <= m; i++) {
        cin >> u >> v >> w;
        debug[i] = w;
        edges[i] = {u, v, w, i};
    }

    cin >> q;
    for(int i = 1; i <= q; i++) {
        cin >> u >> v >> w;
        edgesadd[i] = {u, v, w, i};
    }

    sort(edges + 1, edges + 1 + m, cmp1);

    for(int i = 1; i <= m; i++) {
        u = edges[i].u; v = edges[i].v;
        u = findRoot(u); v = findRoot(v);
        if(u == v) {
            weights += edges[i].w;
            ansdel.pb(edges[i].id);
        } else {
            UnionSet(u, v);
        }
    }

    sort(edgesadd + 1, edgesadd + 1 + q, cmp2);
    for(int i = 1; i <= q; i++) {
        u = edgesadd[i].u; v = edgesadd[i].v;
        u = findRoot(u); v = findRoot(v);

        if(u != v) {
            weights += edgesadd[i].w;
            ansadd.pb(edgesadd[i].id);
            UnionSetAdd(u, v);
        }
    }

    sort(ansdel.begin(), ansdel.end());
    sort(ansadd.begin(), ansadd.end());

    cout << weights << endl;
    cout << (int)ansdel.size() << endl;
    for(int i = 0; i < (int)ansdel.size(); i++) {
        cout << ansdel[i] << " ";
        // tt += debug[ansdel[i]];
    }
    cout << endl << (int)ansadd.size() << endl;
    for(int i = 0; i < (int)ansadd.size(); i++) cout << ansadd[i] << " ";
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    freopen("MOJI.inp", "r", stdin);
    freopen("MOJI.out", "w", stdout);

    long long TestCase;
    cin >> TestCase;
    // while(TestCase--)
    Solve();
}
