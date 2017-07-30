// UVa11478 Halum
// Rujia Liu
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;

const int INF = 1000000000;
const int maxn = 500 + 10;
const int maxm = 2700 + 10;

struct Edge {
  int to, dist;
};

// �ڽӱ�д��
struct BellmanFord {
  int n, m;
  Edge edges[maxm];
  int head[maxn];
  int next[maxm];
  bool inq[maxn];   // �Ƿ��ڶ�����
  int d[maxn];      // s��������ľ���
  int cnt[maxn];    // ���Ӵ���

  void init(int n) {
    this->n = n;
    m = 0;
    memset(head, -1, sizeof(head));
  }

  void AddEdge(int from, int to, int dist) {
    next[m] = head[from];
    head[from] = m;
    edges[m++] = (Edge){to, dist};
  }

  bool negativeCycle() {
    queue<int> Q;
    memset(inq, 0, sizeof(inq));
    memset(cnt, 0, sizeof(cnt));
    for(int i = 0; i < n; i++) { d[i] = 0; Q.push(i); }

    int u;
    while(!Q.empty()) {
      u = Q.front(); Q.pop();
      inq[u] = false;
      for(int i = head[u]; i != -1; i = next[i]) {
        Edge& e = edges[i];
        if(d[e.to] > d[u] + e.dist) {
          d[e.to] = d[u] + e.dist;
          if(!inq[e.to]) { Q.push(e.to); inq[e.to] = true; if(++cnt[e.to] > n) return true; }
        }
      }
    }
    return false;
  }
};

BellmanFord solver;

// �ж��ڳ�ʼ���Լ��ϵͳ��ÿ������ʽ�Ҳ�ͬʱ��ȥx֮���Ƿ��н�
bool test(int x) {
  for(int i = 0; i < solver.m; i++)
    solver.edges[i].dist -= x;
  bool ret = solver.negativeCycle();
  for(int i = 0; i < solver.m; i++)
    solver.edges[i].dist += x;
  return !ret; // ����и�����˵�����Լ��ϵͳ�޽�
}

int main() {
  int n, m;
  while(scanf("%d%d", &n, &m) == 2) {
    solver.init(n);
    int ub = 0;
    while(m--) {
      int u, v, d;
      scanf("%d%d%d", &u, &v, &d); ub = max(ub, d);
      solver.AddEdge(u-1, v-1, d);
    }

    if(test(ub+1)) printf("Infinite\n"); // ���������ÿ����Ȩ��>ub��˵��ÿ���ߵ�Ȩ�������ˣ��ظ�һ�λ����ӵø���...ֱ������
    else if(!test(1)) printf("No Solution\n");
    else {
      int L = 2, R = ub, ans = 1;
      while(L <= R) {
        int M = L + (R-L)/2;
        if(test(M)) { ans = M; L = M+1; } else R = M-1;
      }
      printf("%d\n", ans);
    }
  }
  return 0;
}
