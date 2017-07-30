#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <stack>
#include <algorithm>
using namespace std;

typedef unsigned long long LL;
const int N = 70;
LL f[70][70];
// f[i][j]表示将i个盘通过j个柱子从第一根柱子移动到最后一根柱子所需要的最少次数 
int path[70][70]; // 表示f[i][j]的得到的最优移动方案是先将最小的path[i][j]个盘移动到某一根柱子上 
int n, m;
stack<int>stk[70];
char ocp[70];


void pre() {
    memset(f, 0x3f, sizeof (f));
    for (int i = 3; i <= 65; ++i) {
        f[0][i] = 0;
        f[1][i] = 1;
    }
    for (int i = 1; i <= 64; ++i) { // 初始化三根柱子的情况 
        f[i][3]    = f[i-1][3] * 2 + 1;
        path[i][3] = i-1;
    }
    for (int i = 2; i <= 64; ++i) {
        for (int j = 4; j <= 65; ++j) {
            for (int k = 1; k < i; ++k) {
                if (f[i][j] > f[i-k][j-1] + 2*f[k][j]) {
                    f[i][j] = f[i-k][j-1] + 2*f[k][j];
                    path[i][j] = k;
                }
            }
        }
    }
}
/*
move 2 from 1 to 2
move 1 from 3 to 2 atop 2
*/

void display(int an, int am, int sta, int end) {
    if (an == 1) {
        if (stk[end].size()) {
            printf("move %d from %d to %d atop %d\n", stk[sta].top(), sta, end, stk[end].top());
        } else {
            printf("move %d from %d to %d\n", stk[sta].top(), sta, end);
        }
        stk[end].push(stk[sta].top());
        stk[sta].pop();
        return;
    }
    int peg = 0;
    for (int i = 1; i <= m; ++i) {
        if (i != sta && i != end && !ocp[i]) {
            peg = i;
            break;
        }
    }
    display(path[an][am], am, sta, peg);
    ocp[peg] = 1;
    display(an-path[an][am], am-1, sta, end);
    ocp[peg] = 0;
    display(path[an][am], am, peg, end);
}

void solve() {
    for (int i = 1; i <= m; ++i) while (!stk[i].empty()) stk[i].pop();
    for (int i = n; i >= 1; --i) stk[1].push(i);
    memset(ocp, 0, sizeof (ocp)); 
    printf("%llu\n", f[n][m]);
    display(n, m, 1, m);
}

int main() {
	//freopen("input.txt","r",stdin);
	//freopen("output.b","w",stdout);
    pre();
    int T=1;
    //scanf("%d", &T);
    while (T--) {
        scanf("%d %d", &n, &m);
        solve();
    }
    return 0;
}