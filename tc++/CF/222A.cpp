#include <cstdio>

#define N 510
int n, m, k, x, y;
char a[N + 1][N + 1];

const int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

inline bool valid(int x, int y) {
    return x > 0 && x <= n && y > 0 && y <= m && a[x][y] == '.';
}

void dfs(int x, int y) {
    if (!k) return ;
    a[x][y] = 'X', --k;
    for (int i = 0; i < 4; ++i) {
        int nx = x + dir[i][0], ny = y + dir[i][1];
        if (valid(nx, ny)) dfs(nx, ny);
    }
}

int main(int argc, char *argv[]) {
    
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; ++i) scanf("%s", a[i] + 1);
    int cnt = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            if (a[i][j] == '.') x = i, y = j, ++cnt;
    k = cnt - k;
    dfs(x, y);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            if (a[i][j] == '.') a[i][j] = 'X';
            else if (a[i][j] == 'X') a[i][j] = '.';
    for (int i = 1; i <= n; ++i) printf("%s\n", a[i] + 1);
    
    //fclose(stdin);
    //fclose(stdout);
    return 0;
}