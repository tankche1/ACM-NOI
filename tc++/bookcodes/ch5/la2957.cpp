// LA2957/UVa1324 Bring Them There
// Rujia Liu
#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;

const int maxn = 5000 + 10;
const int INF = 1000000000;

struct Edge {
  int from, to, cap, flow;
};

bool operator < (const Edge& a, const Edge& b) {
  return a.from < b.from || (a.from == b.from && a.to < b.to);
}

struct Dinic {
  int n, m, s, t;
  vector<Edge> edges;    // ����������
  vector<int> G[maxn];   // �ڽӱ�G[i][j]��ʾ���i�ĵ�j������e�����е����
  bool vis[maxn];        // BFSʹ��
  int d[maxn];           // ����㵽i�ľ���
  int cur[maxn];         // ��ǰ��ָ��

  void init() { edges.clear(); }

  void clearNodes(int a, int b) {
    for(int i = a; i <= b; i++) G[i].clear();
  }

  void AddEdge(int from, int to, int cap) {
    edges.push_back((Edge){from, to, cap, 0});
    edges.push_back((Edge){to, from, 0, 0});
    m = edges.size();
    G[from].push_back(m-2);
    G[to].push_back(m-1);
  }

  bool BFS() {
    memset(vis, 0, sizeof(vis));
    queue<int> Q;
    Q.push(s);
    vis[s] = 1;
    d[s] = 0;
    while(!Q.empty()) {
      int x = Q.front(); Q.pop();
      for(int i = 0; i < G[x].size(); i++) {
        Edge& e = edges[G[x][i]];
        if(!vis[e.to] && e.cap > e.flow) {
          vis[e.to] = 1;
          d[e.to] = d[x] + 1;
          Q.push(e.to);
        }
      }
    }
    return vis[t];
  }

  int DFS(int x, int a) {
    if(x == t || a == 0) return a;
    int flow = 0, f;
    for(int& i = cur[x]; i < G[x].size(); i++) {
      Edge& e = edges[G[x][i]];
      if(d[x] + 1 == d[e.to] && (f = DFS(e.to, min(a, e.cap-e.flow))) > 0) {
        e.flow += f;
        edges[G[x][i]^1].flow -= f;
        flow += f;
        a -= f;
        if(a == 0) break;
      }
    }
    return flow;
  }

  // ��s-t�������������������limit����ֻ��һ������Ϊlimit����
  int Maxflow(int s, int t, int limit) {
    this->s = s; this->t = t;
    int flow = 0;
    while(BFS()) {
      memset(cur, 0, sizeof(cur));
      flow += DFS(s, limit - flow);
      if(flow == limit) break; // �ﵽ�������ƣ�ֱ���˳�
    }
    return flow;
  }
};

Dinic g;

const int maxm = 200 + 10;
int main() {
  int n, m, k, S, T;
  int u[maxm], v[maxm]; // �����
  while(scanf("%d%d%d%d%d", &n, &m, &k, &S, &T) == 5) {
    for(int i = 0; i < m; i++) scanf("%d%d", &u[i], &v[i]);
    g.init();
    int day = 1;
    g.clearNodes(0, n-1); // ��һ������Ϊ0~n-1����day��(day>=1)�����Ϊday*n~day*n+n-1
    int flow = 0;
    for(;;) {
      // �ж�day���Ƿ��н�
      // һ�ܷɴ������Ҫn-1�쵽��Ŀ�ĵأ�������һ·�������Ҫn+k-2��Ϳ����������зɴ����ܽ����������(n+k-1)n
      g.clearNodes(day*n, day*n+n-1);
      for(int i = 0; i < n; i++) g.AddEdge((day-1)*n+i, day*n+i, INF); // ԭ�ز���
      for(int i = 0; i < m; i++) {
        g.AddEdge((day-1)*n+u[i]-1, day*n+v[i]-1, 1); // u[i]->v[i]
        g.AddEdge((day-1)*n+v[i]-1, day*n+u[i]-1, 1); // v[i]->u[i]
      }
      flow += g.Maxflow(S-1, day*n+T-1, k - flow);
      if(flow == k) break;
      day++;
    }

    // �����
    printf("%d\n", day);
    int idx = 0;
    vector<int> location(k, S); // ÿ�ܷɴ��ĵ�ǰλ��
    for(int d = 1; d <= day; d++) {
      idx += n*2;
      vector<int> moved(k, 0); // ��d����û���ƶ��ɴ�i
      vector<int> a, b;        // ��d����һ�ܷɴ���a[i]��b[i]
      for(int i = 0; i < m; i++) {
        int f1 = g.edges[idx].flow; idx += 2;
        int f2 = g.edges[idx].flow; idx += 2;
        if(f1 == 1 && f2 == 0) { a.push_back(u[i]); b.push_back(v[i]); }
        if(f1 == 0 && f2 == 1) { a.push_back(v[i]); b.push_back(u[i]); }
      }
      printf("%d", a.size());
      for(int i = 0; i < a.size(); i++) {
        // �������ļܷɴ���a[i]�ƶ�����b[i]
        for(int j = 0; j < k; j++)
          if(!moved[j] && location[j] == a[i]) {
            printf(" %d %d", j+1, b[i]);
            moved[j] = 1;
            location[j] = b[i];
            break;
          }
      }
      printf("\n");
    }
  }
  return 0;
}
