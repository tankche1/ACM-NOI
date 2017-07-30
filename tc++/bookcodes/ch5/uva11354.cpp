// UVa11354 Bond
// Rujia Liu
#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn = 100000 + 10;
const int logmaxn = 20;
const int INF = 1000000000;

struct LCA {
  int n;
  int fa[maxn];   // ��������
  int cost[maxn]; // �͸��׵ķ���
  int L[maxn];    // ��Σ����ڵ���Ϊ0��
  int anc[maxn][logmaxn];     // anc[p][i]�ǽ��p�ĵ�2^i�����ס�anc[i][0] = fa[i]
  int maxcost[maxn][logmaxn]; // maxcost[p][i]��i��anc[p][i]��·���ϵ�������

  // Ԥ��������fa��cost�������anc��maxcost����
  void preprocess() {
    for(int i = 0; i < n; i++) {
      anc[i][0] = fa[i]; maxcost[i][0] = cost[i];
      for(int j = 1; (1 << j) < n; j++) anc[i][j] = -1;
    }   
    for(int j = 1; (1 << j) < n; j++)
      for(int i = 0; i < n; i++)
        if(anc[i][j-1] != -1) {
          int a = anc[i][j-1];
          anc[i][j] = anc[a][j-1];
          maxcost[i][j] = max(maxcost[i][j-1], maxcost[a][j-1]);
        }
  }

  // ��p��q��·���ϵ����Ȩ
  int query(int p, int q) {
    int tmp, log, i;
    if(L[p] < L[q]) swap(p, q);
    for(log = 1; (1 << log) <= L[p]; log++); log--;

    int ans = -INF;
    for(int i = log; i >= 0; i--)
      if (L[p] - (1 << i) >= L[q]) { ans = max(ans, maxcost[p][i]); p = anc[p][i];}
   
    if (p == q) return ans; // LCAΪp
   
    for(int i = log; i >= 0; i--)
      if(anc[p][i] != -1 && anc[p][i] != anc[q][i]) {
        ans = max(ans, maxcost[p][i]); p = anc[p][i];
        ans = max(ans, maxcost[q][i]); q = anc[q][i];
      }

    ans = max(ans, cost[p]);
    ans = max(ans, cost[q]);
    return ans; // LCAΪfa[p]����Ҳ����fa[q]��
  }  
};

LCA solver;

#include<cstdio>
#include<vector>

int pa[maxn];
int findset(int x) { return pa[x] != x ? pa[x] = findset(pa[x]) : x; } 

vector<int> G[maxn], C[maxn];

void dfs(int u, int fa, int level) {
  solver.L[u] = level;
  for(int i = 0; i < G[u].size(); i++) {
    int v = G[u][i];
    if(v != fa) {
      solver.fa[v] = u;
      solver.cost[v] = C[u][i];
      dfs(v, u, level+1);
    }
  }
}

struct Edge {
  int x, y, d;
  bool operator < (const Edge& rhs) const {
    return d < rhs.d;
  }
};

const int maxm = 100000;
Edge e[maxm];

int main() {
  int kase = 0, n, m, x, y, d, Q;
  while(scanf("%d%d", &n, &m) == 2 && n) {
    for(int i = 0; i < m; i++) {
      scanf("%d%d%d", &x, &y, &d);
      e[i] = (Edge){ x-1, y-1, d };
    }
    // ��С������
    sort(e, e+m);
    for(int i = 0; i < n; i++) { pa[i] = i; G[i].clear(); C[i].clear(); }
    for(int i = 0; i < m; i++) {
      int x = e[i].x, y = e[i].y, d = e[i].d, u = findset(x), v = findset(y);
      if(u != v) {
        pa[u] = v;
        G[x].push_back(y); C[x].push_back(d);
        G[y].push_back(x); C[y].push_back(d);
      }
    }
    // �����и���
    solver.n = n;
    dfs(0, -1, 0);
    solver.preprocess();

    if(++kase != 1) printf("\n");
    scanf("%d", &Q);
    while(Q--) {
      scanf("%d%d", &x, &y);
      printf("%d\n", solver.query(x-1, y-1));
    }
  }
  return 0;
}
