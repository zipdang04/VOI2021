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

const int oo = 1e9;
const long long maxN = 1e5 + 100;

/* Author : Le Ngoc Bao Anh, 10A5, LQD High School for Gifted Student */

vector<int> a[maxN];
int d[510][510];
int f[maxN];
int vs[maxN];
vector<int> spe;
vector<int> ans;
int root[maxN];
int row[maxN];
int RMQ[maxN][17];
int n,k;

void dfs(int id, int node) {
    for(int i = 0; i < a[node].size(); i++) {
        if(d[id][a[node][i]] == oo) {
            d[id][a[node][i]] = d[id][node] + 1;
            dfs(id, a[node][i]);
        }
    }
}

void solve()
{
    int u, v, res = 0;

    for(int i = 1; i <= k; i++) {
        for(int j = 1; j <= n; j++) d[i][j] = oo;
    }

    for(int i = 1; i <= k; i++) {
    	d[i][spe[i - 1]] = 0;
        dfs(i, spe[i - 1]);
    }

    for(int node = 1; node <= n; node++) {
        int ok = 1;
        for(int i = 1; i <= k; i++) {
            for(int j = i + 1; j <= k; j++) {
                if(d[i][node] == d[j][node]) ok = 0;
            }
        }
        if(ok) {
            res++;
            ans.pb(node);
        }
    }

    cout << res << endl;
    for(int i = 0 ; i < res; i++) cout << ans[i] << " ";
}

void dfsfindroot(int node) {
    for(int i = 0; i < a[node].size(); i++) {
        if(root[a[node][i]] == 0) {
            root[a[node][i]] = node;
            row[a[node][i]] = row[node] + 1;
            dfsfindroot(a[node][i]);
        }
    }
}

void buildRMQ()
{
    for(int i = 1; i <= n; i++) RMQ[i][0] = root[i];

    for(int i = 1; i <= 16; i++) {
        for(int node = 1; node <= n; node++) {
            if(row[node] > (1 << i)) {
                RMQ[node][i] = RMQ[RMQ[node][i - 1]][i - 1];
            }
        }
    }
}

void dfs2(int node, int r)
{
    if(vs[node] == 0) vs[node] = 2;
    if(root[node] == r) return;
    dfs(root[node], r);
}

void dfs3(int node) {
	for(int i = 0; i < a[node].size(); i++) {
		if(a[node][i] != root[node]) {
			if(vs[a[node][i]] == 0) vs[a[node][i]] = 1;
			dfs3(a[node][i]);
		}
	}
}
void get(int u, int v)
{
    int ancu, ancv;
    ancu = u; ancv = v;
    if(row[u] > row[v]) swap(u, v), swap(ancu, ancv);

    for(int i = 16; i >= 0; i--) {
        if(row[v] - (1 << i) >= row[u]) {
            v = RMQ[v][i];
        }
    }

    if(u == v) {
        if((row[ancv] - row[ancu]) % 2 == 0) {
            int nxt = row[ancv] - (row[ancv] - row[ancu]) / 2;
            v = ancv;
            for(int i = 16; i >= 0; i--) {
                if(row[v] - (1 << i) >= nxt) {
                    v = RMQ[v][i];
                }
            }

            vs[v] = 1;
        }
        return;
    }

    for(int i = 16; i >= 0; i--) {
        if(row[u] <= (1 << i)) continue;

        if(RMQ[u][i] != RMQ[v][i]) {
            u = RMQ[u][i];
            v = RMQ[v][i];
        }
    }

    u = root[u];
    if(row[ancu] == row[ancv]) {
        dfs2(ancu, u);
        dfs2(ancv, u);
        dfs3(ancu); dfs3(ancv);

//        cout << "d" << vs[2] << endl;
        for(int i = 1; i <= n; i++) if(vs[i] != 2) vs[i] = 1;
        for(int i = 1; i <= n; i++) if(vs[i] == 2) vs[i] = 0;

        return;
    }

    if((row[ancv] + row[ancu] - 2 * row[u]) % 2 == 0) {
        int nxt = row[ancv] - (row[ancv] + row[ancu] - 2 * row[u]) / 2;
        v = ancv;
        for(int i = 16; i >= 0; i--) {
            if(row[v] - (1 << i) >= nxt) {
                v = RMQ[v][i];
            }
        }

        vs[v] = 1;
    }
}

void solve2()
{
    int res = 0;
    root[1] = 1; row[1] = 1;
    dfsfindroot(1);

    int cnt = 0;
    for(int i = 0; i < k; i++) {
        for(int j = i + 1; j < k; j++) {
            if(row[spe[i]] == row[spe[j]]) cnt++;
        }
    }
    
//    cout << row[2] << " " << row[4] << endl;
 
    if(cnt > 1) {
        cout << 0;
        return;
    }
 
	buildRMQ();

    for(int i = 1; i <= k; i++) {
        for(int j = i + 1; j <= k; j++) {
            get(spe[i - 1], spe[j - 1]);
        }
    }

    for(int i = 1; i <= n; i++) {
        if(!vs[i]) {
            res++;
            ans.pb(i);
        }
    }

    cout << res << endl;
    for(int i = 0; i < res; i++) cout << ans[i] << " ";
}

void toanswer() 
{
    int u, v;
    cin >> n >> k;
    for(int i = 1; i <= k; i++) {
        cin >> u;
        spe.pb(u);
    }    

    for(int i = 1; i < n; i++) {
        cin >> u >> v;
        a[u].pb(v); a[v].pb(u);
    }
    if(n <= 500) {
    	solve();
    	return;
	}
    solve2();
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    freopen("MILITARY.inp", "r", stdin);
    freopen("MILITARY.out", "w", stdout);

    // long long TestCase;
    // cin >> TestCase;
    // while(TestCase--)
    toanswer();
}
