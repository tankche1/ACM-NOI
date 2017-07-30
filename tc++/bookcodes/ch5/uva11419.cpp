// UVa11419 SAM I AM
// Rujia Liu
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int maxn = 1000 + 5; // ���ඥ��������Ŀ

// ����ͼ������ƥ��
struct BPM {
  int n, m;               // ���Ҷ������
  vector<int> G[maxn];    // �ڽӱ�
  int left[maxn];         // left[i]Ϊ�ұߵ�i�����ƥ����ţ�-1��ʾ������
  bool T[maxn];           // T[i]Ϊ�ұߵ�i�����Ƿ��ѱ��

  int right[maxn];        // ����С������
  bool S[maxn];           // ����С������

  void init(int n, int m) {
    this->n = n;
    this->m = m;
    for(int i = 0; i < n; i++) G[i].clear();
  }

  void AddEdge(int u, int v) {
    G[u].push_back(v);
  }

  bool match(int u){
    S[u] = true;
    for(int i = 0; i < G[u].size(); i++) {
      int v = G[u][i];
      if (!T[v]){
        T[v] = true;
        if (left[v] == -1 || match(left[v])){
          left[v] = u;
          right[u] = v;
          return true;
        }
      }
    }
    return false;
  }

  // �����ƥ��
  int solve() {
    memset(left, -1, sizeof(left));
    memset(right, -1, sizeof(right));
    int ans = 0;
    for(int u = 0; u < n; u++) { // ����߽��u��ʼ����
      memset(S, 0, sizeof(S));
      memset(T, 0, sizeof(T));
      if(match(u)) ans++;
    }
    return ans;
  }

  // ����С���ǡ�X��YΪ��С�����еĵ㼯
  int mincover(vector<int>& X, vector<int>& Y) {
    int ans = solve();
    memset(S, 0, sizeof(S));
    memset(T, 0, sizeof(T));
    for(int u = 0; u < n; u++)
      if(right[u] == -1) match(u); // ������Xδ�ǵ��������
    for(int u = 0; u < n; u++)
      if(!S[u]) X.push_back(u); // X�е�δ��ǵ�
    for(int v = 0; v < m; v++)
      if(T[v]) Y.push_back(v);  // Y�е��ѱ�ǵ�
   return ans;
  }
};

BPM solver;

int R, C, N;

int main(){
  int kase = 0;
  while(scanf("%d%d%d", &R, &C, &N) == 3 && R && C && N) {
    solver.init(R, C);
    for(int i = 0; i < N; i++) {
      int r, c;
      scanf("%d%d", &r, &c); r--; c--;
      solver.AddEdge(r, c);
    }
    vector<int> X, Y;
    int ans = solver.mincover(X, Y);
    printf("%d", ans);
    for(int i = 0; i < X.size(); i++) printf(" r%d", X[i]+1);
    for(int i = 0; i < Y.size(); i++) printf(" c%d", Y[i]+1);
    printf("\n");
  }
  return 0;
}
