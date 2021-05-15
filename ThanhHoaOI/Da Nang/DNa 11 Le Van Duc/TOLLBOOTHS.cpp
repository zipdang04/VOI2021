#include<bits/stdc++.h>
using namespace std;

//Variables
const int mxN = 1e5 + 5;
const int MOD = 1e9 + 7;
const long long oo = 1e18;
const int d4i[4] = {-1 , 0 , 1 , 0} , d4j[4] = {0 , 1 , 0 , -1};
const int d8i[8] = {-1 , -1 , 0 , 1 , 1 , 1 , 0 , -1} , d8j[8] = {0 , 1 , 1 , 1 , 0 , -1 , -1 , -1};

int TestCase , SubTask;
long long n , k;

void Solve() {
//	cin >> SubTask;
	cin >> n >> k;
	if (n / 2 >= k) {
		cout << k + k / 2 + 1;
	}
	else {
		cout << (n - k) / 2 + k + 1;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	freopen("TOLLBOOTHS.INP" , "r" , stdin);
	freopen("TOLLBOOTHS.OUT" , "w" , stdout);
//	cin >> TestCase;
	TestCase = 1;
	while(TestCase--)
		Solve();
	return 0;
}



