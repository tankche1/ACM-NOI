// UVa11297 Census
// Rujia Liu
#include<algorithm>
using namespace std;

const int INF = 1<<30;
const int maxn = 2000 + 10;
struct IntervalTree2D {
  int Max[maxn][maxn], Min[maxn][maxn], n, m;
  int xo, xleaf, x1, y1, x2, y2, x, y, v, vmax, vmin; // ��������ѯ������м����

  void query1D(int o, int L, int R) {
    if(y1 <= L && R <= y2) {
      vmax = max(Max[xo][o], vmax); vmin = min(Min[xo][o], vmin);
    } else {
      int M = L + (R-L)/2;
      if(y1 <= M) query1D(o*2, L, M);
      if(M < y2) query1D(o*2+1, M+1, R);
    }
  }

  void query2D(int o, int L, int R) {
    if(x1 <= L && R <= x2) { xo = o; query1D(1, 1, m); }
    else {
      int M = L + (R-L)/2;
      if(x1 <= M) query2D(o*2, L, M);
      if(M < x2) query2D(o*2+1, M+1, R);
    }
  }

  void modify1D(int o, int L, int R) {
    if(L == R) {
      if(xleaf) { Max[xo][o] = Min[xo][o] = v; return; }
      Max[xo][o] = max(Max[xo*2][o], Max[xo*2+1][o]);
      Min[xo][o] = min(Min[xo*2][o], Min[xo*2+1][o]);
    } else {
      int M = L + (R-L)/2;
      if(y <= M) modify1D(o*2, L, M);
      else modify1D(o*2+1, M+1, R);
      Max[xo][o] = max(Max[xo][o*2], Max[xo][o*2+1]);
      Min[xo][o] = min(Min[xo][o*2], Min[xo][o*2+1]);
    }
  }

  void modify2D(int o, int L, int R) {
    if(L == R) { xo = o; xleaf = 1; modify1D(1, 1, m); }
    else {
      int M = L + (R-L)/2;
      if(x <= M) modify2D(o*2, L, M);
      else modify2D(o*2+1, M+1, R);
      xo = o; xleaf = 0; modify1D(1, 1, m);
    }
  }

  void query() {
    vmax = -INF; vmin = INF;
    query2D(1, 1, n);
  }

  void modify() {
    modify2D(1, 1, n);
  }

};

IntervalTree2D t;

#include<cstdio>

int main() {
  int n, m, Q, x1, y1, x2, y2, x, y, v;
  char op[10];
  scanf("%d%d", &n, &m);
  t.n = n; t.m = m;
  for(int i = 1; i <= n; i++)
    for(int j = 1; j <= m; j++) {
      scanf("%d", &t.v);
      t.x = i; t.y = j;
      t.modify();
    }
  scanf("%d", &Q);
  while(Q--) {
    scanf("%s", op);
    if(op[0] == 'q') {
      scanf("%d%d%d%d", &t.x1, &t.y1, &t.x2, &t.y2);
      t.query();
      printf("%d %d\n", t.vmax, t.vmin);
    } else {
      scanf("%d%d%d", &t.x, &t.y, &t.v);
      t.modify();
    }
  }
  return 0;
}
