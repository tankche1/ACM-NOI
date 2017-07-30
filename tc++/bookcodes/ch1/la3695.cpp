// LA3695 Distant Galaxy
// Rujia Liu
#include<cstdio>
#include<algorithm>
using namespace std;

struct Point {
  int x, y;
  bool operator < (const Point& rhs) const {
    return x < rhs.x;
  }
};

const int maxn = 100 + 10;
Point P[maxn];
int n, m, y[maxn], on[maxn], on2[maxn], left[maxn];

int solve() {
  sort(P, P+n);
  sort(y, y+n);
  m = unique(y, y+n) - y; // ���в�ͬ��y����ĸ���
  if(m <= 2) return n; // ������ֲ�ͬ��y

  int ans = 0;
  for(int a = 0; a < m; a++)
    for(int b = a+1; b < m; b++) {
      int ymin = y[a], ymax = y[b]; // �������±߽�ֱ�Ϊymin��ymaxʱ�Ľ�

      // ����left, on, on2
      int k = 0;
      for(int i = 0; i < n; i++) {
        if(i == 0 || P[i].x != P[i-1].x) { // һ���µ�����
          k++;
          on[k] = on2[k] = 0;
          left[k] = k == 0 ? 0 : left[k-1] + on2[k-1] - on[k-1];
        } 
        if(P[i].y > ymin && P[i].y < ymax) on[k]++;
        if(P[i].y >= ymin && P[i].y <= ymax) on2[k]++;
      }
      if(k <= 2) return n; // ������ֲ�ͬ��x

      int M = 0;
      for(int j = 1; j <= k; j++) {
        ans = max(ans, left[j]+on2[j]+M);
        M = max(M, on[j]-left[j]);
      }
    }
  return ans;
}

int main() {
  int kase = 0;
  while(scanf("%d", &n) == 1 && n) {
    for(int i = 0; i < n; i++) { scanf("%d%d", &P[i].x, &P[i].y); y[i] = P[i].y; }
    printf("Case %d: %d\n", ++kase, solve());
  }
  return 0;
}
