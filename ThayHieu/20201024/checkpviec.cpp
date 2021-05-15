//Dai Ca Di Hoc
#include <bits/stdc++.h>
#define sz(x) int(x.size())
#define MIN(x,y) if (x > y) x = y
#define PB push_back
#define mp make_pair
#define F first
#define S second
#define Task "pviec"
#define maxn 505
#define MOD 1000000007
#define remain(x) if (x > MOD) x -= MOD
#define pii pair<int, int>
#define FOR(i,a,b) for(int i = (a); i <= (b); i++)
#define FORD(i,a,b) for(int i = (a); i >= (b); i--)

using namespace std;
ifstream fi, fo, fa;

int dd[maxn][maxn];
int finish[maxn];
int m, n;

bool check()
{
  string ans, out;
  fo >> out;
  fa >> ans;
  int ma = 0, mo = 0;
  if (ans == "YES")
  {
    fo >> mo;
    fa >> ma;
  }
  if (out!=ans)
  {
      cout << " Ket qua sai!!\n";
      cout << " Output is: " << out << " " << mo << endl;
      cout << " Answer is: " << ans << " " << ma << endl;
      return 0;
  }
// others here
    int x;
    memset(dd, 0 ,sizeof(dd));
    memset(finish, 0, sizeof(finish));
    fi >> m >> n;
  if (ans == "YES")
  {
    for (int i = 1; i <= n; i ++)
    {
        while (1)
        {
            fi >> x;
            if (x == 0) break;
            dd[i][x] = 1;
        }
        int cnt = 0;
        while (1)
        {
            fo >> x;
            if (x == 0) break;
            cnt ++;
            if (cnt > mo)
            {
                cout << " Nguoi " << i << " lam qua nhieu viec \n";
                return 0;
            }
            if (dd[i][x] == 0)
            {
                cout << " Nguoi " << i << " khong lam viec " << x << "\n";
                return 0;
            }
            if (finish[x])
            {
                cout << " Viec " << x << " duoc lam boi 2 nguoi \n";
                return 0;
            }
            dd[i][x] = 0;
            finish[x] = 1;
        }
    }
    if (*min_element(finish+1, finish+m+1) == 0)
    {
        cout << " KHong lam het viec \n";
        return 0;
    }
    if (mo > ma)
    {
        cout << " Khong toi uu \n";
        return 0;
    }
  }


  cout << " Ket qua dung!!! \n";
  return 1;
}

int main(int argc, char** argv)
{
  fi = ifstream(argv[1]);
  fo = ifstream(argv[2]);
  fa = ifstream(argv[3]);
  bool kq = check();
  fi.close();
  fo.close();
  fa.close();
  #define TRUE 0
  #define FALSE 1
  if (kq) return TRUE; else return FALSE;
//  system("pause");
}
