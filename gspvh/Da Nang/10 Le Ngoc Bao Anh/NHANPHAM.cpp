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

long long a[maxN];

void Solve()
{
    long long n,k,l,r,curr = 0,day = 0,mid = 0;
    cin >> n >> k;
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i <= n; i++) curr += i - a[i];
    l = 0; r = sqrt(((k - curr) / (n * n)) * 2) + 100;
    while(l <= r) {
        mid = (l + r) >> 1;
        if(k >= curr * mid + n * n * (mid - 1) * mid / 2) {
            day = mid;
            l = mid + 1;
        } else r = mid - 1;
    }    

    // cout << day << endl;

    k -= curr * day + n * n * (day - 1) * day / 2;
    if(k <= 0) {
        cout << day * n << endl;
        return;
    }
    for(int i = 1; i <= n; i++) {
        k = k + a[i];
        k = k - n * day - i;
        if(k <= 0) {
            cout << i + day * n << endl;
            return;
        } 
    }
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    freopen("NHANPHAM.inp", "r", stdin);
    freopen("NHANPHAM.out", "w", stdout);

    // long long TestCase;
    // cin >> TestCase;
    // while(TestCase--)
    Solve();
}