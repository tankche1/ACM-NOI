// UVa10635 Prince and Princess
// Rujia Liu
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 250 * 250;
const int INF = 1000000000;
int S[maxn], g[maxn], d[maxn]; // LIS����
int num[maxn]; // num[x]Ϊ����x���±��,num[x]=0��ʾxû����A�г��ֹ�

int main() {
  int T;
  scanf("%d", &T);
  for(int kase = 1; kase <= T; kase++) {
    int N, p, q, x;
    scanf("%d%d%d", &N, &p, &q);
    memset(num, 0, sizeof(num)); 
    for(int i = 1; i <= p+1; i++) { scanf("%d", &x); num[x] = i; }
    int n = 0;
    for(int i = 0; i < q+1; i++) { scanf("%d", &x); if(num[x]) S[n++] = num[x]; }

    // ���S[0]...S[n-1]��LIS
    for(int i = 1; i <= n; i++) g[i] = INF;
    int ans = 0;
    for(int i = 0; i < n; i++) {
      int k = lower_bound(g+1, g+n+1, S[i]) - g; // ��g[1]~g[n]�в���
      d[i] = k;
      g[k] = S[i];
      ans = max(ans, d[i]);
    }
    printf("Case %d: %d\n", kase, ans);
  }
  return 0;
}
