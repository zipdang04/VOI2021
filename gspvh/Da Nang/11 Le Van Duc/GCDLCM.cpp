#include<bits/stdc++.h>
using namespace std;

//Shortcuts
#define ll long long
#define lb long double
#define fi first
#define se second
#define debug(a) cout << "This is value of " << #a << ": " << a << "\n";
#define ft(i , a , b) for (ll i = (ll)a ; i <= (ll)b ; i++)
#define fd(i , a , b) for (ll i = (ll)a ; i >= (ll)b ; i--)
#define lt(i , a , b , c) for (ll i = (ll)a ; i <= (ll)b ; i += (ll)c)
#define ld(i , a , b , c) for (ll i = (ll)a ; i >= (ll)b ; i -= (ll)c)
#define at(a , b) for (auto a : b)

//Functions
mt19937 rando(chrono::steady_clock::now().time_since_epoch().count());
ll random(ll l , ll r) {return (rando() % (r - l + 1) + l);};
ll getbit(ll a , ll b) {return a & (1 << b);};
ll onbit(ll a , ll b) {return a | (1 << b);};
ll offbit(ll a , ll b) {return (!getbit(a , b)) ? a : a ^ (1 << b);};

//Variables
const ll mxN = 1e4 + 5;
const ll oo = 1e18;
const ll MOD = 1e9 + 7;
const ll d4i[4] = {-1 , 0 , 1 , 0} , d4j[4] = {0 , 1 , 0 , -1};
const ll d8i[8] = {-1 , -1 , 0 , 1 , 1 , 1 , 0 , -1} , d8j[8] = {0 , 1 , 1 , 1 , 0 , -1 , -1 , -1};

ll TestCase;
ll n , m , x , y , z;
string s;

void Solve() {
	map<ll , ll> gcd[mxN] , lcm[mxN];
	cin >> n >> m;
	ft(i , 1 , m) {
		cin >> s >> x >> y >> z;
		if (s == "LCM") {
			if (lcm[x][y] > 0 && lcm[x][y] != z) {
				cout << "N";
				return;
			}
			lcm[x][y] = z;
		}
		else {
			if (gcd[x][y] > 0 && gcd[x][y] != z) {
				cout << "N";
				return;
			}
			gcd[x][y] = z;
		}
		
		if (lcm[x][y] && gcd[x][y]) {
			if (lcm[x][y] % gcd[x][y] != 0) {
				cout << "N";
				return;
			}
			if (lcm[x][y] < gcd[x][y]) {
				cout << "N";
				return;
			}
		}
	}
	cout << "Y";
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	freopen("GCDLCM.inp" , "r" , stdin);
	freopen("GCDLCM.out" , "w" , stdout);
	int subtask;
	cin >> subtask;
	cin >> TestCase;
	while(TestCase--) {
		Solve();
	}
	return 0;
}



