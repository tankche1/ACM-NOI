// UVa11990 "Dynamic" Inversion
// Rujia Liu
#include<cstdio>
#include<vector>
#include<algorithm>
#include<cassert>
using namespace std;

inline int lowbit(int x) { return x&-x; }

struct Node {
  Node *ch[2]; // ��������
  int v; // ֵ
  int s; // �����������ɾ����ǵĽ��δͳ������
  int d; // ɾ�����
  Node():d(0) {}
  int ch_s(int d) { return ch[d] == NULL ? 0 : ch[d]->s; }
};

// ����������ɾ��ʵ��
struct RankTree {
  int n, next;
  int *v;
  Node *nodes, *root;
  RankTree(int n, int* A):n(n) {
    nodes = new Node[n];
    next = 0;
    v = new int[n];
    for(int i = 0; i < n; i++) v[i] = A[i];
    sort(v, v+n);
    root = build(0, n-1);
    delete[] v;
  }

  Node* build(int L, int R) {
    if(L > R) return NULL;
    int M = L + (R-L) / 2;
    int u = next++;
    nodes[u].v = v[M];
    nodes[u].ch[0] = build(L, M-1);
    nodes[u].ch[1] = build(M+1, R);
    nodes[u].s = nodes[u].ch_s(0) + nodes[u].ch_s(1) + 1;
    return &nodes[u];
  }

  // type = 0��ͳ�Ʊ�vС��Ԫ�ظ���
  // type = 1��ͳ�Ʊ�v���Ԫ�ظ���  
  int count(int v, int type) {
    Node* u = root;
    int cnt = 0;
    while(u != NULL) {
      if(u->v == v) { cnt += u->ch_s(type); break; }
      int c = (v < u->v ? 0 : 1);
      if(c != type) cnt += u->s - u->ch_s(c);
      u = u->ch[c];
    }
    return cnt;
  }

  // Ҫ��֤v����������δɾ��
  void erase(int v) {
    Node* u = root;
    while(u != NULL) {
      u->s--;
      if(u->v == v) { assert(u->d == 0); u->d = 1; return; }
      int c = (v < u->v ? 0 : 1);
      u = u->ch[c];
    }
    assert(0);
  }

  ~RankTree() {
    delete[] nodes;
  }
};

// Ƕ����������Fenwick��
struct FenwickRankTree {
  int n;
  vector<RankTree*> C;

  void init(int n, int* A) {
    this->n = n;
    C.resize(n+1); // �����C[1]~C[n]
    for(int i = 1; i <= n; i++) {
      C[i] = new RankTree(lowbit(i), A+i-lowbit(i)+1);
    }
  }

  void clear() { for(int i = 1; i <= n; i++) delete C[i]; }

  // ͳ��A[1], A[2], ..., A[x]�ж��ٸ�Ԫ�ر�v��(x<=n)
  int count(int x, int v, int type) {
    int ret = 0;
    while(x > 0) {
      ret += C[x]->count(v, type); x -= lowbit(x);
    }
    return ret;
  }

  // ɾ��A[x]=v
  void erase(int x, int v) {
    while(x <= n) {
      C[x]->erase(v); x += lowbit(x);
    }
  }
};

// ��ͨFenwick��
struct FenwickTree {
  int n;
  vector<int> C;

  void init(int n) {
    this->n = n;
    C.resize(n+1);
    fill(C.begin(), C.end(), 0);
  }

  // ����A[1]+A[2]+...+A[x] (x<=n)
  int sum(int x) {
    int ret = 0;
    while(x > 0) {
      ret += C[x]; x -= lowbit(x);
    }
    return ret;
  }

  // A[x] += d (1<=x<=n)
  void add(int x, int d) {
    while(x <= n) {
      C[x] += d; x += lowbit(x);
    }
  }
};

const int maxn = 200000 + 5;
const int maxm = 100000 + 5;
typedef long long LL;

int n, m, A[maxn], B[maxn], pos[maxn];
FenwickRankTree frt;
FenwickTree f; // ��������������Լ�����ɾ����Ԫ���ж��ٸ���vС

LL inversion_pairs() {
  LL ans = 0;
  f.init(n);
  for(int i = n; i >= 1; i--) {
    ans += f.sum(A[i]-1);
    f.add(A[i], 1);
  }
  return ans;
}

int main() {
  while(scanf("%d%d", &n, &m) == 2) {
    for(int i = 1; i <= n; i++) {
      scanf("%d", &A[i]);
      pos[B[i] = A[i]] = i;
    }
    LL cnt = inversion_pairs();
    frt.init(n, A);
    f.init(n);
    for(int i = 0; i < m; i++) {
      printf("%lld\n", cnt);
      int x;
      scanf("%d", &x);
      f.add(x, 1);
      int a = frt.count(pos[x]-1, x, 1); // x�����a����x��
      int b = x-1; // һ����x-1������xС
      int c = f.sum(x-1); // ɾ��c����xС��
      int d = frt.count(pos[x]-1, x, 0);  // ���������d����xС
      b -= c + d;  // ��ʣb��
      cnt -= a + b; // ����Լ���a+b��
      frt.erase(pos[x], x);
    }
  }
  return 0;
}
