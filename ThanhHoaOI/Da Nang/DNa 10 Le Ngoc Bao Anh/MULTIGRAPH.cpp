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
const long long maxN = 1e6;

/* Author : Le Ngoc Bao Anh, 10A5, LQD High School for Gifted Student */

multiset<int> ms;
int n, q;
int a[maxN];

void Solve()
{
    int x,u,v;
    cin >> n >> q;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        ms.insert(a[i]);
    }
    for(int i = 1; i <= q; i++) {
        cin >> x >> u >> v;
        if(x == 1) {
            ms.erase(ms.find(a[u]));
            a[u] = v; ms.insert(v);
        } else {
            if(u == v) {
                cout << 0 << endl;
                continue;
            }
            int temp = *ms.begin();
            cout << min(a[u] * a[v], a[u] * temp + temp * a[v]) << endl;
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    freopen("MULTIGRAPH.inp", "r", stdin);
	freopen("MULTIGRAPH.out", "w", stdout);
    // long long TestCase;
    // cin >> TestCase;
    // while(TestCase--)
    Solve();
}
