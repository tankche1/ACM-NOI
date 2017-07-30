// UVa10537 Toll! Revisited
// Rujia Liu
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 52 + 10;
const long long INF = 1LL << 60;
typedef long long LL;

int n, G[maxn][maxn], src, dest, p;
int mark[maxn]; // ���
LL d[maxn];     // d[i]��ʾ�ӵ�i�������Ѿ�������i��˰�ˣ�ʱ����Ҫ�����ٶ�������destʱ����ʣp������

int read_node() {
  char ch[9];
  scanf("%s", ch);
  if(ch[0] >= 'A' && ch[0] <= 'Z') return ch[0] - 'A';
  else return ch[0] - 'a' + 26;
}

char format_node(int u) {
  return u < 26 ? 'A' + u : 'a' + (u - 26);
}

// ����item������ȥ���next����ʣ���ٸ�����
LL forward(LL item, int next) {
  if(next < 26) return item - (item + 19) / 20;
  return item - 1;
}

// ����Ҫ���Ŷ��ٸ�����������u����˰�Ժ���ʣd[u]������
// Ϊ��ʹ����������⣬����ʹ��һ�ֲ�̫��ѧ�Ľⷨ
LL back(int u) {
  if(u >= 26) return d[u]+1;
  LL X = d[u] * 20 / 19; // ��ʼֵ
  while(forward(X, u) < d[u]) X++; // ����
  return X;
}

void solve() {
  n = 52; // ������52�����
  memset(mark, 0, sizeof(mark));
  d[dest] = p;
  mark[dest] = 1;
  for(int i = 0; i < n; i++) if(i != dest) {
    d[i] = INF;
    if(G[i][dest]) d[i] = back(dest);
  }

  // Dijkstra�����̣�����
  while(!mark[src]) {
    // ����С��d
    int minu = -1;
    for(int i = 0; i < n; i++) if(!mark[i]) {
      if(minu < 0 || d[i] < d[minu]) minu = i;
    }
    mark[minu] = 1;
    // ������������d
    for(int i = 0; i < n; i++) if(!mark[i]) {
      if(G[i][minu]) d[i] = min(d[i], back(minu));
    }
  }

  // ���
  printf("%lld\n", d[src]);
  printf("%c", format_node(src));
  int u = src;
  LL item = d[src];
  while(u != dest) {
    int next;
    for(next = 0; next < n; next++) // �ҵ���һ�������ߵĽ��
      if(G[u][next] && forward(item, next) >= d[next]) break;
    item = d[next];
    printf("-%c", format_node(next));
    u = next;
  }
  printf("\n");
}

int main() {
  int kase = 0;
  while(scanf("%d", &n) == 1 && n >= 0) {
    memset(G, 0, sizeof(G));
    for(int i = 0; i < n; i++) {
      int u = read_node();
      int v = read_node();
      if(u != v) G[u][v] = G[v][u] = 1;
    }
    scanf("%d", &p);
    src = read_node();
    dest = read_node();
    printf("Case %d:\n", ++kase);
    solve();
  }
  return 0;
}
