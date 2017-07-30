// LA2531/UVa1306 The K-League
// Rujia Liu
#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;

const int maxn = 700;
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

  void init(int n) {
    for(int i = 0; i < n; i++) G[i].clear();
    edges.clear();
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

  int Maxflow(int s, int t) {
    this->s = s; this->t = t;
    int flow = 0;
    while(BFS()) {
      memset(cur, 0, sizeof(cur));
      flow += DFS(s, INF);
    }
    return flow;
  }
};

Dinic g;

const int maxt = 25 + 5;
int n, w[maxt], d[maxt], a[maxt][maxt];

inline int ID(int u, int v) { return u*n+v+1; }
inline int ID(int u) { return n*n+u+1; }

bool canWin(int team) {
  // ����teamȫʤ�����ʤ������
  int total = w[team];
  for(int i = 0; i < n; i++)
    total += a[team][i];
  for(int i = 0; i < n; i++)
    if(w[i] > total) return false;

  // ��ͼ��s=0, ���(u,v)�ı��Ϊu*n+v+1, ���u�ı��Ϊn^2+u+1, t=n^2+n+1
  g.init(n*n+n+2);
  int full = 0;
  int s = 0, t = n*n+n+1;
  for(int u = 0; u < n; u++) {
    for(int v = u+1; v < n; v++) {
      if(a[u][v] > 0) g.AddEdge(s, ID(u,v), a[u][v]); // S��(u,v)�Ļ�
      full += a[u][v];
      g.AddEdge(ID(u,v), ID(u), INF); // (u,v)��u�Ļ�
      g.AddEdge(ID(u,v), ID(v), INF); // (u,v)��v�Ļ�
    }
    if(w[u] < total) g.AddEdge(ID(u), t, total-w[u]); // u��T�Ļ�
  }
  return g.Maxflow(s, t) == full;
}

int main() {
  int T;
  scanf("%d", &T);
  while(T--) {
    scanf("%d", &n);
    for(int i = 0; i < n; i++) scanf("%d%d", &w[i], &d[i]);
    for(int i = 0; i < n; i++)
      for(int j = 0; j < n; j++)
        scanf("%d", &a[i][j]);

    bool first = true;
    for(int i = 0; i < n; i++)
      if(canWin(i)) {
        if(first) first = false; else printf(" ");
        printf("%d", i+1);
      }
    printf("\n");
  }
  return 0;
}
