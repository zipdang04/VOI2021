#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXN = 102;
const int INF = MAXN*MAXN;

typedef pair<int, int> ii;

ii operator+(const ii& a, const ii& b){
    return ii(a.first + b.first, a.second + b.second);
}


int r,s;
char mat[MAXN][MAXN];


//ENSW
ii delta[] = {ii(0, 1), ii(-1, 0), ii(1, 0), ii(0, -1)};


int measure(ii p){
    int d = 0;
    for(;;){
        switch(mat[p.first][p.second]){
        case 'x':
            return d;
        case '>':
            p = p+delta[0];
            break;
        case '^':
            p = p+delta[1];
            break;
        case 'v':
            p = p+delta[2];
            break;
        case '<':
            p = p+delta[3];
            break;
        default:
            return INF;
        }
        d++;
    }
    return INF;
}

int main(){
    scanf("%d%d", &r, &s);
    for(int i=0;i<r;i++){
        scanf("%s", mat[i]);
    }
    ii start;
    for(int i=0;i<r;i++){
        for(int j=0;j<s;j++){
            if(mat[i][j] == 'o')
                start = ii(i, j);
        }
    }
    int bl = INF;
    char s = 0;
    for(int i=0;i<4;i++){
        int len = measure(start + delta[i]);
        if(len<bl){
            bl = len;
            s = "ENSW"[i];
        }
    }
    if(s)
        printf(":)\n%c\n", s);
    else
        puts(":(");
}
