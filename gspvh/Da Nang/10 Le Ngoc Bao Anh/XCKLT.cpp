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

string a,b,c;

int f[5100][5100];

void solvesub1()
{
    if(a == c || b == c) {
        cout << "TRETRAU";
        return ;
    }

    cout << 2 << endl << a << b;
}

bool checker()
{
    for(int i = 1; i < a.size(); i++) {
        for(int j = 1; j < c.size(); j++) {
            f[i][j] = max(f[i][j - 1], f[i - 1][j]);
            if(a[i] == c[j]) f[i][j] = max(f[i][j], f[i - 1][j - 1] + 1);
        }
    }

    if(f[a.size() - 1][c.size() - 1] == c.size() - 1) {
        return false;
    }

    for(int i = 0; i <= b.size() + 10; i++) {
        for(int j = 0; j <= c.size() + 10; j++) {
            f[i][j] = 0;
        }
    }

    for(int i = 1; i < b.size(); i++) {
        for(int j = 1; j < c.size(); j++) {
            f[i][j] = max(f[i][j - 1], f[i - 1][j]);
            if(b[i] == c[j]) f[i][j] = max(f[i][j], f[i - 1][j - 1] + 1);
        }   
    }

    if(f[b.size() - 1][c.size() - 1] == c.size() - 1) {
        return false;
    }

    return true;
}

void solvesub2()
{
    a = '$' + a; b = '$' + b; c = '$' + c;
    if(!checker()) {
        cout << "TRETRAU";
        return ;
    }
}

void solvesub4()
{
    a = '$' + a; b = '$' + b; c = '$' + c;
    if(!checker()) {
        cout << "TRETRAU";
        return ;
    }
}

void Solve()
{
    cin >> a >> b >> c;
    if(a.size() == 1 && b.size() == 1 && c.size() == 1) {
        solvesub1();
        return;
    }

    if(a.size() <= 10 && b.size() <= 10 && c.size() <= 10) {
        solvesub2();
        return;
    }    

    solvesub4();
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    freopen("XCKLT.inp", "r", stdin);
    freopen("XCKLT.out", "w", stdout);

    // long long TestCase;
    // cin >> TestCase;
    // while(TestCase--)
    Solve();
}