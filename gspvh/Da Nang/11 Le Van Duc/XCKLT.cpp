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
const ll mxN1 = 400 + 5;
const ll mxN2 = 500 + 5;
const ll oo = 1e18;
const ll MOD = 1e9 + 7;
const ll d4i[4] = {-1 , 0 , 1 , 0} , d4j[4] = {0 , 1 , 0 , -1};
const ll d8i[8] = {-1 , -1 , 0 , 1 , 1 , 1 , 0 , -1} , d8j[8] = {0 , 1 , 1 , 1 , 0 , -1 , -1 , -1};

ll TestCase;
string s1 , s2 , s3 , ss;
int n , m , p;
int dp[mxN1][mxN1][mxN1] , dp1[mxN2][mxN2];
bool mark[mxN1][mxN1][mxN1] , mark1[mxN2][mxN2];

int cal(int len1 , int len2 , int len3) {
	int &ans = dp[len1][len2][len3];
	bool &tie = mark[len1][len2][len3];
	
	if (len3 > p) return 1e9;
	if (len1 > n && len2 > m) {
		if (len3 <= p) return 0;
		return 1e9;
	}	
	if (tie) return ans;
	tie = true;
	ans = 1e9;
	
	if (len1 <= n) ans = min(ans , cal(len1 + 1 , len2 + (s1[len1] == s2[len2]) , len3 + (s1[len1] == s3[len3])) + 1);
	if (len2 <= m) ans = min(ans , cal(len1 + (s1[len1] == s2[len2]) , len2 + 1 , len3 + (s2[len2] == s3[len3])) + 1);
	return ans;
}

void trace(int len1 , int len2 , int len3) {
	int &ans = dp[len1][len2][len3];
	if (len1 > n && len2 > m) return;
	
	if (len1 <= n && ans == cal(len1 + 1 , len2 + (s1[len1] == s2[len2]) , len3 + (s1[len1] == s3[len3])) + 1) {
		cout << s1[len1];
		trace(len1 + 1 , len2 + (s1[len1] == s2[len2]) , len3 + (s1[len1] == s3[len3]));
		return;
	}
	else {
		cout << s2[len2];
		trace(len1 + (s1[len1] == s2[len2]) , len2 + 1 , len3 + (s2[len2] == s3[len3]));
		return;
	}
}

void trau() {
//	cout << "TRAU\n";
	cal(1 , 1 , 1);
	if (dp[1][1][1] == 1e9) {
		cout << "TRETRAU";
		return;
	}
	cout << dp[1][1][1] << "\n";
	trace(1 , 1 , 1);
	exit(0);
}

int cal1(int len1 , int len2) {
	int &ans = dp1[len1][len2];
	bool &tie = mark1[len1][len2];
	
	if (len1 > n && len2 > m) return 0;
	if (tie) return ans;
	tie = true;
	ans = 1e9;
	
	if (len1 <= n) ans = min(ans , cal1(len1 + 1 , len2 + (s1[len1] == s2[len2])) + 1);
	if (len2 <= m) ans = min(ans , cal1(len1 + (s1[len1] == s2[len2]) , len2 + 1) + 1);
	return ans;
}

void trace1(int len1 , int len2) {
	int &ans = dp1[len1][len2];
	if (len1 > n && len2 > m) return;
	
	if (len1 <= n && ans == cal1(len1 + 1 , len2 + (s1[len1] == s2[len2])) + 1) {
		cout << s1[len1];
		trace1(len1 + 1 , len2 + (s1[len1] == s2[len2]));
		return;
	}
	else {
		cout << s2[len2];
		trace1(len1 + (s1[len1] == s2[len2]) , len2 + 1);
		return;
	}
}

void ac() {
//	cout << "\nAC\n";
	int cnt = 1;
	ft(i , 1 , n) if (s1[i] == s3[cnt]) cnt++;
	if (cnt > p) {
		cout << "TRETRAU";
		return;
	}
	cnt = 1;
	ft(i , 1 , m) if (s2[i] == s3[cnt]) cnt++;
	if (cnt > p) {
		cout << "TRETRAU";
		return;
	}
	cout << cal1(1 , 1) << "\n";
	trace1(1 , 1);	
}

void Solve() {
	cin >> s1 >> s2 >> s3;
	
	n = s1.size();
	m = s2.size();
	p = s3.size();
	s1 = "#" + s1;
	s2 = "#" + s2;
	s3 = "#" + s3;
	
	if (n <= 400 && m <= 400 && p <= 400) trau();
	ac();
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	freopen("XCKLT.inp" , "r" , stdin);
	freopen("XCKLT.out" , "w" , stdout);
//	cin >> TestCase;
	TestCase = 1;
	while(TestCase--)
		Solve();
	return 0;
}



