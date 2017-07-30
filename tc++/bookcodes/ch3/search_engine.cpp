// �����ı���T��Ԥ���������Ӵ���ѯ
// Ԥ����ʱ����T�ĺ�׺����
// ��ѯʱ���ж��ֲ���+�ַ����Ƚϣ�ʱ�临�Ӷ�ΪO(|P|*log|T|)
// ����height���飬���԰ѵ����ѯ��ʱ�临�ӶȽ�ΪO(|P|+log|T|)
// ���ύ��UVa10679 "I love Strings!!!"
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 100000 + 10;

struct SuffixArray {
  char s[maxn];     // ԭʼ�ַ����飨���һ���ַ�Ӧ������0����ǰ����ַ������0��
  int sa[maxn];     // ��׺����
  int rank[maxn];   // ��������. rank[0]һ����n-1�������һ���ַ�
  int height[maxn]; // height����
  int t[maxn], t2[maxn], c[maxn]; // ��������
  int n; // �ַ�����

  void clear() { n = 0; memset(sa, 0, sizeof(sa)); }

  // mΪ����ַ�ֵ��1������֮ǰ�����ú�s��n
  void build_sa(int m) {
    int i, *x = t, *y = t2;
    for(i = 0; i < m; i++) c[i] = 0;
    for(i = 0; i < n; i++) c[x[i] = s[i]]++;
    for(i = 1; i < m; i++) c[i] += c[i-1];
    for(i = n-1; i >= 0; i--) sa[--c[x[i]]] = i;
    for(int k = 1; k <= n; k <<= 1) {
      int p = 0;
      for(i = n-k; i < n; i++) y[p++] = i;
      for(i = 0; i < n; i++) if(sa[i] >= k) y[p++] = sa[i]-k;
      for(i = 0; i < m; i++) c[i] = 0;
      for(i = 0; i < n; i++) c[x[y[i]]]++;
      for(i = 0; i < m; i++) c[i] += c[i-1];
      for(i = n-1; i >= 0; i--) sa[--c[x[y[i]]]] = y[i];
      swap(x, y);
      p = 1; x[sa[0]] = 0;
      for(i = 1; i < n; i++)
        x[sa[i]] = y[sa[i-1]]==y[sa[i]] && y[sa[i-1]+k]==y[sa[i]+k] ? p-1 : p++;
      if(p >= n) break;
      m = p;
    }
  }

  int cmp_suffix(char* P, int p, int m) {
    return strncmp(P, s+sa[p], m);
  }

  int find(char* P) {
    int m = strlen(P);
    if(cmp_suffix(P, 0, m) < 0) return -1;
    if(cmp_suffix(P, n-1, m) > 0) return -1;
    int L = 0, R = n-1;
    while(R >= L) {
      int M = L + (R-L)/2;
      int res = cmp_suffix(P, M, m);
      if(!res) return M;
      if(res < 0) R = M-1; else L = M+1;
    }
    return -1;
  }
};

SuffixArray sa;
char P[maxn];

int main() {
  int T, q;
  scanf("%d", &T);
  while(T--) {
    scanf("%s", sa.s);
    sa.n = strlen(sa.s) + 1;
    sa.build_sa('z' + 1);
    scanf("%d", &q);
    while(q--) {
      scanf("%s", P);
      if(sa.find(P) >= 0) printf("y\n"); else printf("n\n");
    }
  }
  return 0;
}
