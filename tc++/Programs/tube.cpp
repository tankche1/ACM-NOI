
// Task  :  Winter Camp 2006 tube
// Time Complexity  :  O(MlogM + (N+Q)*logN)
// Memory Complexity  :  O(M + N + Q)
// It uses Link-Cut Tree to solve dynamic tree problem

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

struct node
  {
    int value[2], maxv[2], rev, kind;
    node *pre, *ch[2];
  } tree[maxn+1], *Null;

int v[maxn+1], op[maxq+1][3], flag[maxm+1], ans[maxq+1];
int queue[maxn+1], s[maxn+1], rank[maxn+1], top;

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

void Update(node *x)
  {
    if (x == Null) return;
    int a, b, c;
    
    a = x->ch[0]->maxv[0], b = x->ch[1]->maxv[0], c = x->value[0];
    x->maxv[0] = (tree_e[a].w > tree_e[b].w) ? a : b;
    if (tree_e[c].w > tree_e[x->maxv[0]].w) x->maxv[0] = c;
    
    a = x->ch[0]->maxv[1], b = x->ch[1]->maxv[1], c = x->value[1];
    x->maxv[1] = (tree_e[a].w > tree_e[b].w) ? a : b;
    if (tree_e[c].w > tree_e[x->maxv[1]].w) x->maxv[1] = c;
  }

void Reverse(node *x)
  {
    if (x == Null) return;
    x->rev = ! x->rev, swap(x->ch[0], x->ch[1]);
    swap(x->value[0], x->value[1]), swap(x->maxv[0], x->maxv[1]);
  }

void Push_Down(node *x)
  {
    if (x == Null || ! x->rev) return;
    Reverse(x->ch[0]), Reverse(x->ch[1]), x->rev = 0;
  }

void Rotate(node *x, int c)
  {
    node *y = x->pre;
    y->ch[! c] = x->ch[c], x->pre = y->pre;
    if (x->ch[c] != Null) x->ch[c]->pre = y;
    if (y->kind) y->pre->ch[y == y->pre->ch[1]] = x;
    y->pre = x, x->ch[c] = y, Update(y), Update(x);
    if (! y->kind) y->kind = 1, x->kind = 0;
  }

void Splay(node *x)
  {
    for (Push_Down(x); x->kind; )
      if (! x->pre->kind)
        {
          Push_Down(x->pre), Push_Down(x);
          Rotate(x, x == x->pre->ch[0]);
        }
      else
        {
          node *y = x->pre, *z = y->pre;
          Push_Down(z), Push_Down(y), Push_Down(x);
          if (y == z->ch[0])
            if (x == y->ch[0])
              Rotate(y, 1), Rotate(x, 1);
            else
              Rotate(x, 0), Rotate(x, 1);
          else
            if (x == y->ch[1])
              Rotate(y, 0), Rotate(x, 0);
            else
              Rotate(x, 1), Rotate(x, 0);
        }
  }

node *Get_Top(node *x)
  {
    for ( ; Push_Down(x), x->ch[0] != Null; x = x->ch[0]);
    return x;
  }

void Expose(node *x)
  {
    for (node *u = x, *v = Null; u != Null; v = u, u = u->pre)
      {
        Splay(u), u->ch[1]->kind = 0, u->ch[1] = v;
        u->value[1] = Get_Top(v)->value[0], Update(u);
        if (v != Null) v->kind = 1;
      }
  }

int Query_Max(int a, int b)
  {
    int res;
    Expose(&tree[a]);
    for (node *u = &tree[b], *v = Null; u != Null; v = u, u = u->pre)
      {
        Splay(u);
        if (u->pre == Null)
          {
            int a = u->ch[1]->maxv[0], b = v->maxv[0];
            res = (tree_e[a].w > tree_e[b].w) ? a : b;
          }
        u->ch[1]->kind = 0, u->ch[1] = v;
        u->value[1] = Get_Top(v)->value[0], Update(u);
        if (v != Null) v->kind = 1;
      }
    return res;
  }

void Ins_Edge(int a, int b, int w, int c)
  {
    edge_node *p = &edge[top ++];
    p->data = b, p->weight = w, p->no = c;
    p->next = ge[a], ge[a] = p;
  }

void Make_GE(int n)
  {
    int i;
    for (top = 0, i = 1; i <= n; i ++) ge[i] = 0;
    for (i = 1; i < n; i ++)
      {
        Ins_Edge(tree_e[i].a, tree_e[i].b, tree_e[i].w, i);
        Ins_Edge(tree_e[i].b, tree_e[i].a, tree_e[i].w, i);
      }
  }

node *New_Node()
  {
    node *p = &tree[top ++];
    p->value[0] = p->value[1] = p->maxv[0] = p->maxv[1] = 0;
    p->rev = p->kind = 0, p->pre = p->ch[0] = p->ch[1] = Null;
    return p;
  }

void Make_Tree(int n)
  {
    int i, head, tail;
    top = 0, Null = New_Node();
    Null->pre = Null->ch[0] = Null->ch[1] = Null;
    for (i = 1; i <= n; i ++) New_Node();
    memset(v, 0, sizeof(v)), v[1] = 1, queue[1] = 1;
    for (head = tail = 1; head <= tail; head ++)
      for (edge_node *p = ge[queue[head]]; p; p = p->next)
        if (! v[p->data])
          {
            tree[p->data].pre = &tree[queue[head]];
            tree[p->data].value[0] = p->no;
            v[p->data] = 1, queue[++ tail] = p->data;
          }
  }

int main()
  {
    int n, m, q, i, j, a, b, tot, loc;
    
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
      if (op[i][0] = getint(), op[i][0] == 1)
        op[i][1] = getint(), op[i][2] = getint();
      else
        {
          a = getint(), b = getint();
          if (a > b) swap(a, b);
          loc = lower_bound(e+1, e+m+1, (edge_type){a, b, 0}) - e;
          flag[loc] = 1, op[i][1] = loc;
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
    
    Make_GE(n), tree_e[0].w = 0, Make_Tree(n);
    for (i = q; i; i --)
      if (op[i][0] == 1)
        ans[i] = tree_e[Query_Max(op[i][1], op[i][2])].w;
      else
        {
          loc = Query_Max(e[op[i][1]].a, e[op[i][1]].b);
          if (e[op[i][1]].w < tree_e[loc].w)
            {
              a = tree_e[loc].a, b = tree_e[loc].b, Splay(&tree[a]);
              if (tree[a].value[0] == loc) swap(a, b);
              Expose(&tree[a]), Splay(&tree[b]);
              tree[b].pre = Null, tree[b].value[0] = 0;
              Update(&tree[b]), tree_e[loc] = e[op[i][1]];
              a = tree_e[loc].a, b = tree_e[loc].b;
              Expose(&tree[b]), Splay(&tree[b]), Reverse(&tree[b]);
              tree[b].pre = &tree[a], tree[b].value[0] = loc;
              Update(&tree[b]);
            }
        }
    for (i = 1; i <= q; i ++)
      if (op[i][0] == 1) printf("%d\n", ans[i]);
    
    return 0;
  }
