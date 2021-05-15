#include<bits/stdc++.h>
using namespace std;

typedef long long Int;
const int MOD = 2004010501;//>2e9
Int lcm(Int a, Int b) { return a / __gcd(a, b) * b; }

#define task "REFLECTION"

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	freopen(task".inp", "r", stdin);
	freopen(task".out", "w", stdout);

	Int width, height, dx, dy;
	cin >> width >> height >> dx, dy = height;
	
	Int bao_anh_va_hieu_co_bi_ngu_khong = lcm(width, dx);
	bao_anh_va_hieu_co_bi_ngu_khong = bao_anh_va_hieu_co_bi_ngu_khong / width + bao_anh_va_hieu_co_bi_ngu_khong / dx - 2;
	cerr << bao_anh_va_hieu_co_bi_ngu_khong;
	
	if (width <= (int) 3e7) {
		Int x = 0, y = 0;
		Int x_trend = +1, y_trend = +1;
		
		Int answer = 0;
		do {
			x += x_trend * dx, y += y_trend * dy;
	//		cerr << '(' << x << ',' << y << ")\n";
			if (x == 0 or x == width) return cout << answer, 0; 
			++answer;
			y_trend = -y_trend;
			if (x > width) {
				++answer, x = width - (x - width), 
				x_trend = -x_trend, y_trend = -y_trend;
	//			cerr << "bounced from right side\n";
			}
			if (x < 0) {
				++answer, x = -x, 
				x_trend = -x_trend, y_trend = -y_trend; 
	//			cerr << "bounced from left side\n";
			}
		} while (true);
		
		cout << answer;
	}
	else cout << bao_anh_va_hieu_co_bi_ngu_khong;
}
