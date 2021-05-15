//Dai Ca Di Hoc
#include <bits/stdc++.h>
#define sz(x) int(x.size())
#define MIN(x,y) if (x > y) x = y
#define PB push_back
#define mp make_pair
#define F first
#define S second
#define Task "mafia"
#define maxn 100000
#define MOD 1000000007
#define remain(x) if (x > MOD) x -= MOD
#define pii pair<int, int>
#define FOR(i,a,b) for(int i = (a); i <= (b); i++)
#define FORD(i,a,b) for(int i = (a); i >= (b); i--)

typedef char NameFile[1000];

using namespace std;

NameFile input, output, answer;
ifstream fi, fo, fa;

int n, m, s, t, c[100002];

int read()
{
    fi >> n >> m >> s >> t;
    for (int i = 1; i <= n; i ++) fi >> c[i];
}

int readInput()
{
  fi.open(input);
}

int readOutput()
{
  fo.open(output);
}

int readAnswer()
{
  fa.open(answer);
}

bool check()
{

  int ans = 0, out = 0, x;
  while (fa >> x) ans += c[x];
  while (fo >> x)out += c[x];
  if (out - ans)
  {
      cout << " Ket qua sai!!\n";
      cout << " Output is: " << out << endl;
      cout << " Answer is: " << ans << endl;
      return 0;
  }
// others here


  cout << " OK, Ket qua dung!!! \n";
  return 1;
}

main()
{
  gets(input);
  gets(output);

  strcpy(answer, input);
  strcat(input,  Task".inp");
  strcat(output, Task".out");
  strcat(answer, Task".out");

  readInput();
  readOutput();
  readAnswer();
  read();
  cout << ((check()) ? "1.00" : "0.00");
  fi.close();
  fo.close();
  fa.close();
//  system("pause");
}
