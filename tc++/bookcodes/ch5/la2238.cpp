// LA2238 Fixed Partition Memory Management
// Rujia Liu
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int maxn = 500 + 5; // ����������Ŀ
const int INF = 1000000000;

// ���Ȩƥ��
struct KM {
  int n;                  // ���Ҷ������
  vector<int> G[maxn];    // �ڽӱ�
  int W[maxn][maxn];      // Ȩֵ
  int Lx[maxn], Ly[maxn]; // ����
  int left[maxn];         // left[i]Ϊ�ұߵ�i�����ƥ����ţ�-1��ʾ������
  bool S[maxn], T[maxn];  // S[i]��T[i]Ϊ��/�ҵ�i�����Ƿ��ѱ��

  void init(int n) {
    this->n = n;
    for(int i = 0; i < n; i++) G[i].clear();
    memset(W, 0, sizeof(W));
  }

  void AddEdge(int u, int v, int w) {
    G[u].push_back(v);
    W[u][v] = w;
  }

  bool match(int u){
    S[u] = true;
    for(int i = 0; i < G[u].size(); i++) {
      int v = G[u][i];
      if (Lx[u]+Ly[v] == W[u][v] && !T[v]){
        T[v] = true;
        if (left[v] == -1 || match(left[v])){
          left[v] = u;
          return true;
        }
      }
    }
    return false;
  }

  void update(){
    int a = INF;
    for(int u = 0; u < n; u++) if(S[u])
      for(int i = 0; i < G[u].size(); i++) {
        int v = G[u][i];
        if(!T[v]) a = min(a, Lx[u]+Ly[v] - W[u][v]);
      }
    for(int i = 0; i < n; i++) {
      if(S[i]) Lx[i] -= a;
      if(T[i]) Ly[i] += a;
    }
  }

  void solve() {    
    for(int i = 0; i < n; i++) {
      Lx[i] = *max_element(W[i], W[i]+n);
      left[i] = -1;
      Ly[i] = 0;
    }
    for(int u = 0; u < n; u++) {
      for(;;) {
        for(int i = 0; i < n; i++) S[i] = T[i] = false;
        if(match(u)) break; else update();
      }
    }
  }
};

KM solver;

const int maxp = 50 + 5; // ����(program)�������Ŀ
const int maxr = 10 + 5; // ����(region)�������Ŀ
int n, m;                // ������Ŀ��������Ŀ
int runtime[maxp][maxr]; // runtime[p][r]Ϊ����p������r�е�����ʱ��

// ��ӡ���巽��
void print_solution() {
  int start[maxp], region_number[maxp], total = 0; // ��ʼʱ�̡����䵽�������š��ܻ�תʱ��
  for(int region = 0; region < m; region++) {
    vector<int> programs; // ��regionִ�е����г��򣬰����������У���Ϊ��ָ����������pos������
    for(int pos = 0; pos < n; pos++) {
      int right = region * n + pos;
      int left = solver.left[right];
      if(left >= n) break; // ƥ�䵽�����㣬˵����region�Ѿ�û�и��������
      programs.push_back(left);
      region_number[left] = region;
      total -= solver.W[left][right]; // Ȩֵȡ���෴��
    }
    reverse(programs.begin(), programs.end());
    int time = 0;
    for(int i = 0; i < programs.size(); i++) {
      start[programs[i]] = time;
      time += runtime[programs[i]][region];
    }
  }

  printf("Average turnaround time = %.2lf\n", (double)total / n);
  for(int p = 0; p < n; p++)
    printf("Program %d runs in region %d from %d to %d\n", p+1, region_number[p]+1, start[p], start[p]+runtime[p][region_number[p]]);
  printf("\n");
}

int main(){
  int kase = 0;
  while(scanf("%d%d", &m, &n) == 2 && m && n) {
    solver.init(m*n);
    int size[maxr];
    for(int region = 0; region < m; region++) scanf("%d", &size[region]);
    for(int program = 0; program < n; program++) {
      int s[10], t[10], k;
      scanf("%d", &k);
      for(int i = 0; i < k; i++) scanf("%d%d", &s[i], &t[i]);

      for(int region = 0; region < m; region++) {
        // �������p���ڴ�����r�е�����ʱ��
        int& time = runtime[program][region];
        time = INF;
        if(size[region] < s[0]) continue;
        for(int i = 0; i < k; i++)
          if(i == k-1 || size[region] < s[i+1]) {
            time = t[i];
            break;
          }

        // ����X(program) -> Y(region,pos)
        for(int pos = 0; pos < n; pos++)
          solver.AddEdge(program, region * n + pos, -(pos + 1) * time); // ����Ҫ����Сֵ��ȨֵҪȡ�෴��
      }
    }

    // ����������
    for(int i = n; i < n*m; i++)
      for(int j = 0; j < n*m; j++)
        solver.AddEdge(i, j, 1);

    solver.solve();

    printf("Case %d\n", ++kase);
    print_solution();
  }
  return 0;
}
