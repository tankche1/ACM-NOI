// UVa10917 A Walk through the Forest
// Rujia Liu
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;

const int INF = 1000000000;
const int maxn = 1000 + 10;

struct Edge {
  int from, to, dist;
};

struct HeapNode {
  int d, u;
  bool operator < (const HeapNode& rhs) const {
    return d > rhs.d;
  }
};

struct Dijkstra {
  int n, m;
  vector<Edge> edges;
  vector<int> G[maxn];
  bool done[maxn];    // �Ƿ������ñ��
  int d[maxn];        // s��������ľ���
  int p[maxn];        // ���·�е���һ����

  void init(int n) {
    this->n = n;
    for(int i = 0; i < n; i++) G[i].clear();
    edges.clear();
  }

  void AddEdge(int from, int to, int dist) {
    edges.push_back((Edge){from, to, dist});
    m = edges.size();
    G[from].push_back(m-1);
  }

  void dijkstra(int s) {
    priority_queue<HeapNode> Q;
    for(int i = 0; i < n; i++) d[i] = INF;
    d[s] = 0;
    memset(done, 0, sizeof(done));
    Q.push((HeapNode){0, s});
    while(!Q.empty()) {
      HeapNode x = Q.top(); Q.pop();
      int u = x.u;
      if(done[u]) continue;
      done[u] = true;
      for(int i = 0; i < G[u].size(); i++) {
        Edge& e = edges[G[u][i]];
        if(d[e.to] > d[u] + e.dist) {
          d[e.to] = d[u] + e.dist;
          p[e.to] = G[u][i];
          Q.push((HeapNode){d[e.to], e.to});
        }
      }
    }
  }
};

//////// ��Ŀ���
Dijkstra solver;
int d[maxn]; // ���Ҿ���

int dp(int u) {
  if(u == 1) return 1; // ������

  int& ans = d[u];
  if(ans >= 0) return ans;

  ans = 0;
  for(int i = 0; i < solver.G[u].size(); i++) {
    int v = solver.edges[solver.G[u][i]].to;
    if(solver.d[v] < solver.d[u]) ans += dp(v);
  }
  return ans;
}

int main() {
  int n, m;
  while(scanf("%d%d", &n, &m) == 2) {
    solver.init(n);
    for(int i = 0; i < m; i++) {
      int a, b, c;
      scanf("%d%d%d", &a, &b, &c); a--; b--;
      solver.AddEdge(a, b, c);
      solver.AddEdge(b, a, c);
    }

    solver.dijkstra(1); // ��(1)�����е�ľ��롣��Ϊ��·����˫��ģ����԰Ѽҿ������Ҳ��
    memset(d, -1, sizeof(d));
    printf("%d\n", dp(0)); // �칫��(0)���ҵķ���������·������
  }
  return 0;
}
