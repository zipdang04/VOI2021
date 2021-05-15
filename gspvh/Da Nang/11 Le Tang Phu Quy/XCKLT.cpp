#include<bits/stdc++.h>
using namespace std;

#define task "XCKLT"
string a, b, c;

bool is_substring(const string& match, const string& pattern) {
	for (int it = 0, i = 0; i < (int) pattern.size(); i++) {
		if (it >= (int) match.size()) return true;
		if (pattern[i] == match[it]) ++it;
	}
	return false;
}

void Subtask1() {
	if (c.front() == a.front() or c.front() == b.front()) {
		cout << "TRETRAU"; return ;
	}
	if (a.front() != b.front()) cout << "2\n" << a << b;
	else cout << "1\n" << a;
}

int get_bit(int msk, int bit) { return (msk >> bit) & 1; }
void Subtask2() {
	int m = (int) a.size(), n = (int) b.size();
	int length = 2 * (m + n);
	string ans = "";
	
	int digits[m + n];
	for (int msk = 0; msk < 1 << (m + n); msk++) {
		if (__builtin_popcount(msk) != m) continue;

		string consider = "";
		for (int i = 0; i < m + n; i++) digits[i] = get_bit(msk, i);
		for (int i = 0, i_a = 0, i_b = 0; i < m + n; i++) {
			if (i + 1 < m + n and digits[i + 1] != digits[i] and a[i_a] == b[i_b]) {
				//merging characters
				consider += a[i_a]; //consider += b[i_b];
				i_a++, i_b++, i++;
			} else
			if (digits[i]) consider += a[i_a++]; else consider += b[i_b++];
		}
		
		if (!is_substring(c, consider)) {
			if ((int) consider.size() < length) ans = consider, length = (int) ans.size();
		}
	}
	
	cout << length << '\n' << ans;
}

template<typename type> bool minimize(type& var, const type& val) {
	if (val < var) { var = val; return true; } return false;
}

struct Answer {
	int cnt, length;
	Answer(int cnt = 0, int length = 0) : cnt(cnt), length(length) {
	}
 	bool operator< (const Answer& other) const {
 		return (cnt == other.cnt) ? length < other.length : cnt < other.cnt;
	}
	Answer operator+ (const Answer& other) const {
		return Answer(cnt + other.cnt, length + other.length);
	}
};

struct Trace { int x, y; Trace(int x = 0, int y = 0) : x(x), y(y) {} };

void Subtask3() {
	int m = (int) a.size(), n = (int) b.size(), lim = (int) c.size();
	Trace tr[m + 1][n + 1];
	Answer f[m + 1][n + 1] = {};
	
	for (int i = 0; i <= m; i++) for (int j = 0; j <= n; j++) f[i][j] = Answer(2 * lim);
	f[0][0] = Answer(0, 0);
	
	for (int sum = 1; sum <= m + n; sum++) {
		for (int i = 1; i <= min(m, sum); i++) {
			int j = sum - i;
			if (j > n or j < 1) continue;
			bool a_cost = (a[i - 1] == c.front());
			bool b_cost = (b[j - 1] == c.front());
			
			f[i][j] = f[i - 1][j] + Answer(a_cost, 1);
			tr[i][j] = Trace(i - 1, j);
			if (minimize(f[i][j], f[i][j - 1] + Answer(b_cost, 1))) tr[i][j] = Trace(i, j - 1);
			if (a[i - 1] == b[j - 1])
			if (minimize(f[i][j], f[i - 1][j - 1] + Answer(a_cost, 1))) tr[i][j] = Trace(i - 1, j - 1);
//			if (f[i][j] <= lim) cerr << "f(" << i << ',' << j << ") = " << f[i][j] << '\n';
		}
	}
	
//	cerr << "Finished dp-ing\n";
	int n_tr = n, m_tr = m;
	string res = "";
	
	while (n_tr > 0 and m_tr > 0) {
		if (f[m_tr][n_tr].cnt > lim) { cout << "TRETRAU"; return ; }
		int m_stt = tr[m_tr][n_tr].x;
		int n_stt = tr[m_tr][n_tr].y;
		
		if (m_stt < m_tr) res.push_back(a[m_tr - 1]);
		else res.push_back(b[n_tr - 1]);
		
		m_tr = m_stt, n_tr = n_stt;
	}
//	cerr << "Finished tracing\n";
	
	reverse(res.begin(), res.end());
	cout << (int) res.size() << '\n' << res;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	freopen(task".inp", "r", stdin);
	freopen(task".out", "w",stdout);

	cin >> a >> b >> c;
	if (is_substring(c, a) or is_substring(c, b)) {
//		cerr << "Loai tu vong gui xe :(\n";
		return cout << "TRETRAU", 0;
	}
		
	int max_length = max({(int) a.size(), (int) b.size(), (int) c.size()});
	if (max_length == 1) Subtask1(); else  
	if (max_length <= 10) Subtask2(); else 
	{
		bool is_monotonic = true;
		for (auto ch : c) is_monotonic &= ch == c.front();
		if (is_monotonic) Subtask3(); else
		cout << (int) a.size() + (int) b.size(); //can test
	}
//	Subtask2();
//	cerr << "Done sub2\n";
//	Subtask3();
}

