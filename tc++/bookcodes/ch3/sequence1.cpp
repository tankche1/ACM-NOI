// Fast Sequence Operations I
// Rujia Liu
// �����ʽ��
// n m     ���鷶Χ��a[1]~a[n]����ʼ��Ϊ0��������m��
// 1 L R v ��ʾ��a[L]+=v, a[L+1]+v, ..., a[R]+=v
// 2 L R   ��ѯa[L]~a[R]��sum, min��max
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxnode = 1<<17;

int _sum, _min, _max, op, qL, qR, v;

struct IntervalTree {
  int sumv[maxnode], minv[maxnode], maxv[maxnode], addv[maxnode];

  // ά����Ϣ
  void maintain(int o, int L, int R) {
    int lc = o*2, rc = o*2+1;
    sumv[o] = minv[o] = maxv[o] = 0;
    if(R > L) {
      sumv[o] = sumv[lc] + sumv[rc];
      minv[o] = min(minv[lc], minv[rc]);
      maxv[o] = max(maxv[lc], maxv[rc]);
    }
    if(addv[o]) { minv[o] += addv[o]; maxv[o] += addv[o]; sumv[o] += addv[o] * (R-L+1); }
  }

  void update(int o, int L, int R) {
    int lc = o*2, rc = o*2+1;
    if(qL <= L && qR >= R) { // �ݹ�߽�      
      addv[o] += v; // �ۼӱ߽��addֵ
    } else {
      int M = L + (R-L)/2;
      if(qL <= M) update(lc, L, M);
      if(qR > M) update(rc, M+1, R);
    }
    maintain(o, L, R); // �ݹ����ǰ���¼��㱾���ĸ�����Ϣ
  }

  void query(int o, int L, int R, int add) {
    if(qL <= L && qR >= R) { // �ݹ�߽磺�ñ߽�����ĸ�����Ϣ���´�
      _sum += sumv[o] + add * (R-L+1);
      _min = min(_min, minv[o] + add);
      _max = max(_max, maxv[o] + add);
    } else { // �ݹ�ͳ�ƣ��ۼӲ���add
      int M = L + (R-L)/2;
      if(qL <= M) query(o*2, L, M, add + addv[o]);
      if(qR > M) query(o*2+1, M+1, R, add + addv[o]);
    }
  }
};

const int INF = 1000000000;

IntervalTree tree;

int main() {
  int n, m;
  while(scanf("%d%d", &n, &m) == 2) {
    memset(&tree, 0, sizeof(tree));
    while(m--) {
      scanf("%d%d%d", &op, &qL, &qR);
      if(op == 1) {
        scanf("%d", &v);
        tree.update(1, 1, n);
      } else {
        _sum = 0; _min = INF; _max = -INF;
        tree.query(1, 1, n, 0);
        printf("%d %d %d\n", _sum, _min, _max);
      }
    }
  }
  return 0;
}
