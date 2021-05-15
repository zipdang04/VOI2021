#include<bits/stdc++.h>
using namespace std;

typedef long long Int;
#define task "COVID19"

const int MOD = 998244353;
const int MAX = 5e5 + 500;
int num_ppl, num_f0, num_days;

int f[MAX], x[MAX], y[MAX], coef[MAX];
char typ[MAX];

void Subtask2() {
	int answer = 0;
	for (int i = 1; i <= num_ppl; i++) {
		int add = coef[i] * f[i];
		answer += add;
		if (answer >= MOD) answer -= MOD;
		if (answer < 0) answer += MOD;
	}	
	cout << answer << '\n';
	for (int i = 1; i <= num_days; i++) {
		if (f[x[i]] == f[y[i]]) {
			cout << answer << '\n'; continue;
		}
		if (f[x[i]] > f[y[i]]) { //change x
			int f_new = f[y[i]] + 1;
			int cont = ((Int) coef[x[i]] * f[x[i]]) % MOD;
			answer -= cont;
			if (answer >= MOD) answer -= MOD;
			if (answer < 0) answer += MOD;
			
			f[x[i]] = f_new;
			cont = ((Int) coef[x[i]] * f_new) % MOD;
			answer += cont;
			if (answer >= MOD) answer -= MOD;
			if (answer < 0) answer += MOD;
		}
		else {
			int f_new = f[x[i]] + 1;
			int cont = ((Int) coef[y[i]] * f[y[i]]) % MOD;
			answer -= cont;
			if (answer >= MOD) answer -= MOD;
			if (answer < 0) answer += MOD;
			
			f[y[i]] = f_new;
			cont = ((Int) coef[y[i]] * f_new) % MOD;
			answer += cont;
			if (answer >= MOD) answer -= MOD;
			if (answer < 0) answer += MOD;
		}
		cout << answer << '\n';
	}
}

void Subtask3() {
	cerr << "It do sub3\n";
	int init = 0;
	for (int i = 1; i <= num_ppl; i++) {
		int add = coef[i] * f[i];
		init += add;
		if (init >= MOD) init -= MOD;
		if (init < 0) init += MOD;
	}	
	cout << init << '\n';
	for (int i = 1; i <= num_days; i++) {
		if (typ[i] == 'D') {
			if (f[x[i]] > f[y[i]]) f[x[i]] = f[y[i]] + 1; else 
			if (f[y[i]] > f[x[i]]) f[y[i]] = f[x[i]] + 1;
		}
		else {
			int first_gen = -1;
			for (int pos = x[i]; pos <= y[i]; pos++) 
				if (f[pos] >= 0) first_gen = min(first_gen, f[pos]);
			if (first_gen >= 0)
				for (int pos = x[i]; pos <= y[i]; pos++)
					if (f[pos] > first_gen) f[pos] = first_gen + 1;
		}
		int answer = 0;
		for (int i = 1; i <= num_ppl; i++) {
			int add = ((Int) coef[i] * f[i]) % MOD;
			answer += add;
			if (answer >= MOD) answer -= MOD;
			if (answer < 0) answer += MOD;
		}	
		cout << answer << '\n';
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	freopen(task".inp", "r", stdin);
	freopen(task".out", "w",stdout);

	int theta; cin >> theta;
	cin >> num_ppl >> num_f0 >> num_days;

	fill(f, f + 1 + num_ppl, -1);	
	for (int i = 1, x; i <= num_f0; i++) cin >> x, f[x] = 0;
	for (int i = 1; i <= num_days; i++) cin >> typ[i] >> x[i] >> y[i];
	
	coef[0] = 1;
	for (int i = 1; i <= num_ppl; i++) coef[i] = ((Int) coef[i - 1] * (num_ppl + 1)) % MOD;
	if (theta == 1) {
		int answer = 0;
		for (int i = 1; i <= num_ppl; i++) {
			answer -= coef[i];
			if (answer < 0) answer += MOD;	
		}
		for (int i = 0; i <= num_days; i++) cout << answer << '\n';
	} else
	if (theta == 2) Subtask2(); else
	if (theta == 3) Subtask3(); else ;
}

