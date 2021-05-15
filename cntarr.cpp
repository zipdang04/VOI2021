#include <bits/stdc++.h>
using namespace std;
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
*/

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef map<int, int> mii;
typedef unordered_map<int, int> umii;
typedef map<ll, ll> mll;
typedef unordered_map<ll, ll> umll;

/*
struct Node
{
    int node, len;
    Node() {node = len = 0;}
    Node(int node, int len) {this -> node = node, this -> len = len;}
};
typedef vector<Node> vg;
*/

#define MAX 1000001
#define MOD 1000000007

#define fi first
#define se second
#define pf push_front
#define pb push_back

#define FOR(type, i, a, b) for(type i = (a); i <= (b); i++)
#define FORR(type, i, b, a) for(type i = (b); i >= (a); i--)

#define testBit(n, bit) ((n >> bit) & 1)
#define flipBit(n, bit) (n ^ (1ll << bit))
#define cntBit(n) __builtin_popcount(n)
#define cntBitll(n) __builtin_popcountll(n)
#define randomize mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count());

int t;

int build(int left, int right, int currSum, bool prev, int cnt, int k){
    if (left == 0 && right == 0) return cnt == k;
    
    int ans = 0;
    // case1
    if (left){
        int newSum = currSum - 1;
        bool curr = newSum < 0;
        int newCnt = cnt + (curr || prev);
        if (newCnt <= k) 
            ans += build(left - 1, right, newSum, curr, newCnt, k);
    }
    if (right){
        int newSum = currSum + 1;
        bool curr = newSum < 0;
        int newCnt = cnt + (curr || prev);

        if (newCnt <= k) 
            ans += build(left, right - 1, newSum, curr, newCnt, k);
    }
    return ans;
}

main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> t;
    FOR(int, _,1 , t){
        int n, k; cin >> n >> k;
        cout << build(n, n, 0, false, 0, k);
        if (_ < t) cout << '\n';
    }
}