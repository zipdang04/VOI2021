#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long long ld;
typedef vector<int> vi;
typedef pair<ll, ll> pii;

struct Node
{
    int node, len;
    Node() {node = len = 0;}
    Node(int node, int len) {this -> node = node, this -> len = len;}
};
typedef vector<Node> vg;

#define MAX 100001
#define NON 0
#define MOD 1000000007

#define FOR(type, i, a, b) for(type i = a; i < b; i++)
#define FORR(type, i, b, a) for(type i = b; i > a; i--)
#define FORE(type, i, a, b) for(type i = a; i <= b; i++)
#define FORRE(type, i, b, a) for(type i = b; i >= a; i--)

#define testBit(n, bit) ((n >> bit) & 1)
#define flipBit(n, bit) (n ^ (1ll << bit))

ll T;
ll query[MAX];

ll output(ll test, string out, ll a, ll b, ll c){
    cout << "Test " << test << ": " << out << '.';
    cout << "Cac ban in ra: " << a << ' ' << b << ' ' << c << endl;
    exit(1); 
}

int main(int argc, char** argv)
{
    ifstream inp(argv[1]);
    ifstream out(argv[2]);
    ifstream ans(argv[3]);
    // read input
    inp >> T;
    for (ll i = 0; i < T; i++) inp >> query[i];
    // read output
    for (ll i = 0; i < T; i++)
    {
        ll a, b, c; out >> a >> b >> c;
        if (a % query[i]) output(i + 1, "Khong chia het ahihi", a, b, c);
        if (b % query[i]) output(i + 1, "Khong chia het ahihi", a, b, c);
        if (c % query[i]) output(i + 1, "Khong chia het ahihi", a, b, c);
        if ((a ^ b) ^ c) output(i + 1, "ahihi XOR khac khong do ngok", a, b, c);
    }
    return 0;
}