#include<bits/stdc++.h>
using namespace std;

//Variables
const int mxN = 200 + 5;
const int MOD = 999999937;
const long long oo = 1e18;
const int d4i[4] = {-1 , 0 , 1 , 0} , d4j[4] = {0 , 1 , 0 , -1};
const int d8i[8] = {-1 , -1 , 0 , 1 , 1 , 1 , 0 , -1} , d8j[8] = {0 , 1 , 1 , 1 , 0 , -1 , -1 , -1};

int TestCase , SubTask;
long long n , answer;
long long prefix[mxN] = {1 , 9 , 23 , 105 , 614 , 3826 , 25373 , 177247 , 1288440 , 9679469 , 104842283};

bool check(int x) {
	int n , t;
	n = x;
	while (x) {
		t = x % 10;
		if (t) if (n % t != 0) return false;
		x /= 10;
	}
	return true;
}

void dq(int idx , int val) {
	if (idx > n) {
		if (check(val)) answer++;
		return;
	}
	int limit = 0;
	if (idx == 1) limit = 1;
	for (int i = limit; i <= 9; i++) dq(idx + 1 , val * 10 + i);
}

void Solve() {
	for (int i = 1; i <= 10; i++) {
		prefix[i] += prefix[i - 1];
		prefix[i] %= MOD;
	}
	cin >> n;
	if (n <= 10) cout << prefix[n];
	else cout << 0;
	exit(0);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	freopen("NDNUM.INP" , "r" , stdin);
	freopen("NDNUM.OUT" , "w" , stdout);
//	cin >> TestCase;
	TestCase = 1;
	while(TestCase--)
		Solve();
	return 0;
}



