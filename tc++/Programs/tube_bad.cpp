
// Task  :  Winter Camp 2006 tube
// Time Complexity  :  O(MlogM + QN)
// Memory Complexity  :  O(M + N + Q)

#include <algorithm>
#include <cstring>
#include <cstdio>

using namespace std;

const int maxn = 100000, maxm = 1000000, maxq = 100000;

struct edge_type
  {
    int a, b, w;
    bool operator < (const edge_type &o) const
      {
        return a < o.a || a == o.a && b < o.b;
      }
  } e[maxm+1], tmp[maxm+1], tree_e[maxn];

struct edge_node
  {
    int data, weight, no;
    edge_node *next;
  } edge[2*maxn], *ge[maxn+1];

int v[maxn+1], op[maxq+1][3], flag[maxm+1], ans[maxq+1];
int maxv[maxn+1], queue[maxn+1], s[maxn+1], rank[maxn+1];
int up_e[maxn+1], pre[maxn+1], anc[maxn+1], top;

int getint()
  {
    char ch = getchar();
    for ( ; ch > '9' || ch < '0'; ch = getchar());
    int tmp = 0;
    for ( ; '0' <= ch && ch <= '9'; ch = getchar())
      tmp = tmp * 10 + int(ch) - 48;
    return tmp;
  }

int Compare_With_Weight(edge_type a, edge_type b)
  {
    return a.w < b.w;
  }

int Find_Set(int x)
  {
    int t, res, bak;
    for (res = x; s[res] != res; res = s[res]);
    for (t = x; s[t] != t; t = bak)
      bak = s[t], s[t] = res;
    return res;
  }

void Union(int a, int b)
  {
    a = Find_Set(a), b = Find_Set(b);
    if (rank[a] < rank[b])
      s[a] = b;
    else
      s[b] = a, rank[a] += rank[a] == rank[b];
  }

void Ins_Edge(int a, int b, int w, int c)
  {
    edge_node *p = &edge[top ++];
    p->data = b, p->weight = w, p->no = c;
    p->next = ge[a], ge[a] = p;
  }

void Make_Tree(int n)
  {
    int i, head, tail;
    for (top = 0, i = 1; i <= n; i ++) ge[i] = 0;
    for (i = 1; i < n; i ++)
      {
        Ins_Edge(tree_e[i].a, tree_e[i].b, tree_e[i].w, i);
        Ins_Edge(tree_e[i].b, tree_e[i].a, tree_e[i].w, i);
      }
    memset(v, 0, sizeof(v)), v[1] = 1, queue[1] = 1, pre[1] = up_e[1] = 0;
    for (head = tail = 1; head <= tail; head ++)
      for (edge_node *p = ge[queue[head]]; p; p = p->next)
        if (! v[p->data])
          {
            pre[p->data] = queue[head], up_e[p->data] = p->no;
            v[p->data] = 1, queue[++ tail] = p->data;
          }
  }

int Find_Max(int a, int b)
  {
    int last, tmp, now, res;
    for (last = tmp = 0, now = a; now; last = now, now = pre[now])
      if (tree_e[up_e[last]].w > tree_e[tmp].w)
        maxv[now] = up_e[last], tmp = up_e[last];
      else
        maxv[now] = tmp;
    for (res = 0, now = b; maxv[now] == -1; now = pre[now])
      if (tree_e[up_e[now]].w > tree_e[res].w) res = up_e[now];
    if (tree_e[maxv[now]].w > tree_e[res].w) res = maxv[now];
    for (now = a; now; now = pre[now]) maxv[now] = -1;
    return res;
  }

int main()
  {
    int n, m, q, i, j, a, b, tot, loc, now;
    
    freopen("tube.in", "r", stdin);
    freopen("tube.out", "w", stdout);
    
    n = getint(), m = getint(), q = getint();
    for (i = 1; i <= m; i ++)
      {
        e[i].a = getint(), e[i].b = getint(), e[i].w = getint();
        if (e[i].a > e[i].b) swap(e[i].a, e[i].b);
      }
    
    sort(e+1, e+m+1), memset(flag, 0, sizeof(flag));
    for (i = 1; i <= q; i ++)
      {
        op[i][0] = getint();
        if (op[i][0] == 1)
          op[i][1] = getint(), op[i][2] = getint();
        else
          {
            a = getint(), b = getint();
            if (a > b) swap(a, b);
            loc = lower_bound(e+1, e+m+1, (edge_type){a, b, 0}) - e;
            flag[loc] = 1, op[i][1] = loc;
          }
      }
    
    for (tot = 0, i = 1; i <= m; i ++)
      if (! flag[i]) tmp[++ tot] = e[i];
    sort(tmp+1, tmp+tot+1, Compare_With_Weight);
    for (i = 1; i <= n; i ++) s[i] = i, rank[i] = 1;
    for (j = 1, i = 1; i < n; i ++)
      {
        for ( ; Find_Set(tmp[j].a) == Find_Set(tmp[j].b); j ++);
        Union(tmp[j].a, tmp[j].b), tree_e[i] = tmp[j];
      }
    
    memset(maxv, -1, sizeof(maxv));
    for (Make_Tree(n), tree_e[0].w = 0, i = q; i; i --)
      if (op[i][0] == 1)
        ans[i] = tree_e[Find_Max(op[i][1], op[i][2])].w;
      else
        {
          loc = Find_Max(e[op[i][1]].a, e[op[i][1]].b);
          if (e[op[i][1]].w < tree_e[loc].w)
            {
              a = tree_e[loc].a, b = tree_e[loc].b;
              if (pre[a] == b) swap(a, b);
              pre[b] = 0, up_e[b] = 0, tree_e[loc] = e[op[i][1]];
              a = tree_e[loc].a, b = tree_e[loc].b;
              for (tot = 0, now = b; now; now = pre[now])
                anc[++ tot] = now;
              for (j = tot; j > 1; j --)
                pre[anc[j]] = anc[j-1], up_e[anc[j]] = up_e[anc[j-1]];
              pre[b] = a, up_e[b] = loc;
            }
        }
    
    for (i = 1; i <= q; i ++)
      if (op[i][0] == 1) printf("%d\n", ans[i]);
    
    return 0;
  }
