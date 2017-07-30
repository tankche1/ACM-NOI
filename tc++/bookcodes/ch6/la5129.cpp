// LA5129/UVa1102 Affine Mess
// Rujia Liu
#include<cstdio>
#include<cmath>
#include<vector>
#include<algorithm>
using namespace std;

/*
  ������з������������ĸ�����
  p*s + d = x
  q*s + d = y
  r*s + d = z
  ����s��������ϵ����d����ƽ����

  �⣺��������(1), (2)����(p-q)*s = x-y
  i) ���p-q = 0���������x == y�������޽�
  ii) ���p-q != 0����s = (x-y)/(p-q)�����s�����������޽⣬����s��һ����

  ���Ƶģ���Ӧ����(2), (3)��(3), (1)��⡣
  i) �������˶��s�����Ǳ�����ͬ��
  ii) ���һ��s��û�еõ���˵���������⣨����2�Ϳ����ˣ�
  iii) ���s = 0���������⣬Ҳ�޽�
*/
int solve(int p, int q, int r, int x, int y, int z) {
  int a[] = {p, q, r};
  int b[] = {x, y, z};
  vector<int> ans;
  for(int i = 0; i < 3; i++) {
    int P = a[i], Q = a[(i+1)%3], X = b[i], Y = b[(i+1)%3];
    if(P == Q) { if(X != Y) return 0; }
    else if((X - Y) % (P - Q) != 0) return 0;
    else ans.push_back((X - Y) / (P - Q));
  }
  if(ans.empty()) return 2; // �������̵ȼۣ���������
  sort(ans.begin(), ans.end());
  if(ans[0] != ans.back() || ans[0] == 0) return 0; // �����s��ȫ��ͬ���ߵ���0
  return 1;
}

int x[3], y[3]; // �任ǰ�ĵ�
int x2[3], y2[3]; // �任��ĵ�
int ix[3], iy[3]; // ��ת+��׽f��ĵ�

int main() {
  int kase = 0;
  for(;;) {
    int ok = 0;
    for(int i = 0; i < 3; i++) {
      scanf("%d%d", &x[i], &y[i]);
      if(x[i] != 0 || y[i] != 0) ok = 1;
    }
    if(!ok) break;
    for(int i = 0; i < 3; i++) scanf("%d%d", &x2[i], &y2[i]);
    int ans = 0; // ��ĸ���

    // ö����ת��ʽ
    // ע����ת180�ȵȼ�������(-1,-1)������ֻö��40���������80��
    for(int i = 0; i < 40; i++) {
      int rx, ry;
      if(i < 20) { rx = 10; ry = i - 10; } // (10,-10), (10,-9), ..., (10,9), (10,9)
      else { rx = 30 - i; ry = 10; } // (10,10), (9,10), ..., (-9,10)

      // �任ǰ3���㣬������(ix[i],iy[i])��
      double len = sqrt(rx*rx+ry*ry);
      double cosa = rx / len;
      double sina = ry / len;
      int ix[3], iy[3];
      for(int j = 0; j < 3; j++) {
        ix[j] = (int)floor(x[j] * cosa - y[j] * sina + 0.5);
        iy[j] = (int)floor(x[j] * sina + y[j] * cosa + 0.5);
      }

      // ö��(ix, iy)��(x2, y2)�Ķ�Ӧ��ϵ
      int p[3] = {0, 1, 2};
      do {
        int cnt1 = solve(ix[0], ix[1], ix[2], x2[p[0]], x2[p[1]], x2[p[2]]);
        int cnt2 = solve(iy[0], iy[1], iy[2], y2[p[0]], y2[p[1]], y2[p[2]]);
        ans += cnt1 * cnt2; // x, y����������ֱ����
      } while(next_permutation(p, p+3));
    }

    printf("Case %d: ", ++kase);
    if(ans == 0) printf("no solution\n");
    else if(ans == 1) printf("equivalent solutions\n");
    else printf("inconsistent solutions\n");
  }
  return 0;
}
