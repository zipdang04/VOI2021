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
const long long MOD = 998244353;

/* Author : Le Ngoc Bao Anh, 10A5, LQD High School for Gifted Student */

long long Power[maxN];
long long f[maxN];

void Solve()
{
    int Case,n,k,p,u,l,r,q;
    string type;
    long long ans = 0;
    cin >> Case;
    cin >> n >> k >> q;
    for(int i = 1; i <= n; i++) f[i] = -1;
    for(int i = 1; i <= k; i++) {
        cin >> u; f[u] = 0;
    } 

    Power[0] = 1;
    for(int i = 1; i <= n; i++) Power[i] = Power[i - 1] * (n + 1), Power[i] %= MOD;

    if(Case == 1) {
        for(int i = 1; i <= n; i++) ans = ans + MOD - Power[i], ans %= MOD;
        cout << ans << endl;
        for(int i = 1; i <= q; i++) {
            cin >> type >> l >> r;
            cout << ans << endl;
        } 
    }

    if(Case == 2) {
        for(int i = 1; i <= n; i++) ans = ans + MOD + ((f[i] * Power[i]) % MOD), ans %= MOD;
        cout << ans << endl;
        for(int i = 1; i <= q; i++) {
            cin >> type >> l >> r;
            // cout << f[l] << " " << f[r] << endl;
            long long curr, hold = 0;
            if(f[l] == -1) curr = f[r];
            if(f[r] == -1) curr = f[l];
            if(curr == -1) {
                cout << ans << endl;
                continue;
            }

            if(f[l] != -1 && f[r] != -1) curr = min(f[l], f[r]);
            if(f[l] > curr + 1 || f[l] == -1) {
                if(f[l] == -1) hold = (curr + 2) * Power[l], hold %= MOD, hold = MOD - hold;
                else hold = (f[l] - curr - 1) * Power[l], hold %= MOD;
                f[l] = curr + 1;
            }

            // cout << "with i = " << i << " " << hold << endl;

            if(f[r] > curr + 1 || f[r] == -1) {
                if(f[r] == -1) hold = hold + MOD - (((curr + 2) * Power[r]) % MOD);
                else hold = hold + ((f[r] - curr - 1) * Power[r] % MOD), hold %= MOD;
                f[r] = curr + 1;
            }

            ans = ans + MOD - hold; ans %= MOD;
            cout << ans << endl;
        } 
    }

    if(Case == 3) {
        for(int i = 1; i <= n; i++) ans = ans + MOD + ((f[i] * Power[i]) % MOD), ans %= MOD;
        cout << ans << endl;
        for(int i = 1; i <= q; i++) {
            cin >> type >> l >> r;
            // cout << f[l] << " " << f[r] << endl;
            long long curr, hold = 0;
            if(type == "P") {
                curr = 12345678;
                for(int j = l; j <= r; j++) {
                    if(f[j] != -1) curr = min(curr, f[j]);
                }
                if(curr == 12345678) {
                    cout << ans << endl;
                    continue;
                }

                for(int j = 1; j <= n; j++) {
                    if(f[j] > curr + 1 || f[j] == -1) {
                        if(f[j] == -1) hold = hold + MOD - (((curr + 2) * Power[j]) % MOD);
                        else hold = hold + ((f[j] - curr - 1) * Power[j] % MOD), hold %= MOD;
                        f[j] = curr + 1;
                    }
                }

                ans = ans + MOD - hold; ans %= MOD;
                cout << ans << endl;
                continue;
            }
            if(f[l] == -1) curr = f[r];
            if(f[r] == -1) curr = f[l];
            if(curr == -1) {
                cout << ans << endl;
                continue;
            }

            if(f[l] != -1 && f[r] != -1) curr = min(f[l], f[r]);
            if(f[l] > curr + 1 || f[l] == -1) {
                if(f[l] == -1) hold = (curr + 2) * Power[l], hold %= MOD, hold = MOD - hold;
                else hold = (f[l] - curr - 1) * Power[l], hold %= MOD;
                f[l] = curr + 1;
            }

            // cout << "with i = " << i << " " << hold << endl;

            if(f[r] > curr + 1 || f[r] == -1) {
                if(f[r] == -1) hold = hold + MOD - (((curr + 2) * Power[r]) % MOD);
                else hold = hold + ((f[r] - curr - 1) * Power[r] % MOD), hold %= MOD;
                f[r] = curr + 1;
            }

            ans = ans + MOD - hold; ans %= MOD;
            cout << ans << endl;
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    freopen("COVID19.inp", "r", stdin);
    freopen("COVID19.out", "w", stdout);

    // long long TestCase;
    // cin >> TestCase;
    // while(TestCase--)b
    Solve();
}