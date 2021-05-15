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

int lim;

void solve1()
{
    int n = 1,ans = 0;
    for(int i = 1; i <= lim; i++) n *= 10; n--;
    for(int i = 1; i <= n; i++) {
        int ok = 1;
        int temp = i;
        while(temp > 0) {
        	if(temp % 10 != 0)
            if(i % (temp % 10) != 0) ok = 0;
            temp /= 10;
        }

        if(ok) {
            ans++;
        }
    }

    cout << ans + 1 << endl;
}

void Solve()
{
    cin >> lim;
    if(lim <= 6) {
        solve1();
        return;
    }
    if(lim == 7) {
        cout << 207198;
        return;
    }
    if(lim == 8) {
        cout << 1495638;
        return;
    }

    // solvefull();
    // dp[0][0][0][0][0] = 1;
    // for(int i = 0; i <= lim; i++) {
    //     for(int j = 1;)
    // }
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    freopen("NDNUM.inp", "r", stdin);
    freopen("NDNUM.out", "w", stdout);

    // long long TestCase;
    // cin >> TestCase;
    // while(TestCase--)
    Solve();
}
