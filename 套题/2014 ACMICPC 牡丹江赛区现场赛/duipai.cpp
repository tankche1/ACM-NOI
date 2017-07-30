#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;

const int maxn = 200005;
const int INF = 0x3f3f3f3f;

int M, first[maxn], jump[maxn * 2], edge[maxn * 2];
int N, s, e, far[maxn], dis[maxn];
queue<int> que;

inline void add_edge(int u, int v) {
    edge[M] = v;
    jump[M] = first[u];
    first[u] = M++;
}

void init () {
    int l, r;
    M = 0;
    scanf("%d", &N);
    memset(first, -1, sizeof(first));
    for (int i = 1; i < N; i++) {
        scanf("%d%d", &l, &r);
        add_edge(l, r);
        add_edge(r, l);
    }
}

int bfs(int s) {
    que.push(s);
    dis[s] = far[s] = 0;

    int u;
    while (!que.empty()) {
        u = que.front();
        que.pop();

        for (int i = first[u]; i + 1; i = jump[i]) {
            int v = edge[i];
            if (dis[v] > dis[u] + 1) {
                far[v] = u;
                dis[v] = dis[u] + 1;
                que.push(v);
            }
        }
    }
    return u;
}

bool judge (int L) {
    memset(dis, INF, sizeof(dis));
    s = bfs(1);
    for (int i = 0; i < L; i++) {
        s = far[s];
        if (far[s] == 0) {
            e = s % N + 1;
            return true;
        }
    }

    memset(dis, INF, sizeof(dis));
    e = bfs(s);
    for (int i = 0; i < L; i++) {
        if (far[e] == 0)
            return true;
        e = far[e];
    }

    if (e == s)
        e = e % N + 1;
    bfs(e);
    for (int i = 1; i <= N; i++)
        if (dis[i] > L)
            return false;
    return true;
}

void solve () {
    if (N == 2) {
        printf("0 1 2\n");
        return ;
    }

    int l = 0, r = N;
    while (l < r) {
        int mid = (l + r) / 2;
        if (judge(mid))
            r = mid;
        else
            l = mid + 1;
    }
    judge(l);
    printf("%d %d %d\n", l, s, e);
}

int main () {
    int cas;
    scanf("%d", &cas);
    while (cas--) {
        init();
        solve();
    }
    return 0;
}
