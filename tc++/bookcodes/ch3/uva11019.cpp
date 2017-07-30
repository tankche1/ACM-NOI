// UVa11019 Matrix Matcher
// Rujia Liu
#include<cstring>
#include<queue>
#include<cstdio>
#include<map>
#include<string>
using namespace std;

const int SIGMA_SIZE = 26;
const int MAXNODE = 10000 + 10;

void process_match(int pos, int v); // AC�Զ���ÿ�ҵ�һ��ƥ������һ�Σ�����λ��Ϊpos��valΪv

struct AhoCorasickAutomata {
  int ch[MAXNODE][SIGMA_SIZE];
  int f[MAXNODE];    // fail����
  int val[MAXNODE];  // ÿ���ַ����Ľ�β��㶼��һ����0��val
  int last[MAXNODE]; // ����������һ�����
  int sz;

  void init() {
    sz = 1;
    memset(ch[0], 0, sizeof(ch[0]));
  }

  // �ַ�c�ı��
  int idx(char c) {
    return c-'a';
  }

  // �����ַ�����v�����0
  void insert(char *s, int v) {
    int u = 0, n = strlen(s);
    for(int i = 0; i < n; i++) {
      int c = idx(s[i]);
      if(!ch[u][c]) {
        memset(ch[sz], 0, sizeof(ch[sz]));
        val[sz] = 0;
        ch[u][c] = sz++;
      }
      u = ch[u][c];
    }
    val[u] = v;
  }

  // �ݹ��ӡ�Խ��j��β�������ַ���
  void report(int pos, int j) {
    if(j) {
      process_match(pos, val[j]);
      report(pos, last[j]);
    }
  }

  // ��T����ģ��
  int find(char* T) {
    int n = strlen(T);
    int j = 0; // ��ǰ����ţ���ʼΪ�����
    for(int i = 0; i < n; i++) { // �ı�����ǰָ��
      int c = idx(T[i]);
      while(j && !ch[j][c]) j = f[j]; // ˳��ϸ���ߣ�ֱ������ƥ��
      j = ch[j][c];
      if(val[j]) report(i, j);
      else if(last[j]) report(i, last[j]); // �ҵ��ˣ�
    }
  }

  // ����fail����
  void getFail() {
    queue<int> q;
    f[0] = 0;
    // ��ʼ������
    for(int c = 0; c < SIGMA_SIZE; c++) {
      int u = ch[0][c];
      if(u) { f[u] = 0; q.push(u); last[u] = 0; }
    }
    // ��BFS˳�����fail
    while(!q.empty()) {
      int r = q.front(); q.pop();
      for(int c = 0; c < SIGMA_SIZE; c++) {
        int u = ch[r][c];
        if(!u) continue;
        q.push(u);
        int v = f[r];
        while(v && !ch[v][c]) v = f[v];
        f[u] = ch[v][c];
        last[u] = val[f[u]] ? f[u] : last[f[u]];
      }
    }
  }

};

AhoCorasickAutomata ac;

const int maxn = 1000 + 10;
const int maxm = 1000 + 10;
const int maxx = 100 + 10;
const int maxy = 100 + 10;
char text[maxn][maxm], P[maxx][maxy];

int repr[maxx]; // repr[i]Ϊģ���i�еġ�����Ԫ��
int next[maxx]; // next[i]Ϊģ�������i����ȵ���һ���б��
int len[maxx]; // ģ����еĳ���

int tr; // ��ǰ�ı��б��
int cnt[maxn][maxm];
void process_match(int pos, int v) {
  int pr = repr[v - 1]; // ƥ�䵽��ģ���б��
  int c = pos - len[pr] + 1;
  while(pr >= 0) {
    if(tr >= pr) // P����pr��������T��tr�У���ʼ�б��Ϊc
      cnt[tr - pr][c]++;
    pr = next[pr];
  }
}

int main() {
  int T, n, m, x, y;
  scanf("%d", &T);
  while(T--) {
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; i++)
      scanf("%s", text[i]);

    scanf("%d%d", &x, &y);
    ac.init();
    for(int i = 0; i < x; i++) {
      scanf("%s", P[i]);
      len[i] = strlen(P[i]);
      repr[i] = i;
      next[i] = -1;
      for(int j = 0; j < i; j++)
        if(strcmp(P[i], P[j]) == 0) {
          repr[i] = j;
          next[i] = next[j];
          next[j] = i;
          break;
        }
      if(repr[i] == i) ac.insert(P[i], i+1);
    }
    ac.getFail();

    memset(cnt, 0, sizeof(cnt));
    for(tr = 0; tr < n; tr++)
      ac.find(text[tr]);

    int ans = 0;
    for(int i = 0; i < n-x+1; i++)
      for(int j = 0; j < m-y+1; j++)
        if(cnt[i][j] == x) ans++;
    printf("%d\n", ans);
  }
  return 0;
}
