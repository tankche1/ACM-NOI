
// DataMaker for tube

#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <ctime>

using namespace std;

const int maxm = 1000000, size = 2000003, limit = 300000;

struct link_node
  {
    long long data;
    link_node *next;
  } data[maxm], *head[size];

struct edge_type
  {
    int a, b, w, flag, rank;
    bool operator < (const edge_type &o) const
      {
        return rank < o.rank;
      }
  } e[maxm+1];

int top = 0;

int get_rand()
  {
    return ((rand()<<16)+rand())>>1;
  }

void Ins_Hash(int a, int b, int n)
  {
    if (a > b) swap(a, b);
    long long value = (long long)(a - 1) * n + b;
    int loc = int(value % size);
    link_node *p = &data[top ++];
    p->data = value, p->next = head[loc], head[loc] = p;
  }

int Find_Hash(int a, int b, int n)
  {
    if (a > b) swap(a, b);
    long long value = (long long)(a - 1) * n + b;
    int loc = int(value % size);
    for (link_node *p = head[loc]; p; p = p->next)
      if (p->data == value) return 1;
    return 0;
  }

int main()
  {
    FILE *out = fopen("tube.in", "w");
    srand(time(0));
    
    int n, m, q1, q2, i, a, b, ctrl, x, flag, tot;
    char ch;
    
    printf("You are welcome to use the DataMaker for problem tube.\n");
    printf("Please input n and m : "), scanf("%d%d", &n, &m);
    printf("Please input the number of operation 1 : "), scanf("%d", &q1);
    printf("Please input the number of operation 2 : "), scanf("%d", &q2);
    printf("Do you want to make the tree's longest path longer? (Y/N)\n");
    do
      ch = getchar();
    while (ch != 'Y' && ch != 'y' && ch != 'N' && ch != 'n');
    flag = ch == 'Y' || ch == 'y';
    
    if (q2 + n - 1 > m || m > (long long)(n) * (n - 1) / 2)
      {
        printf("Error input!\n");
        system("pause");
        return 0;
      }
    
    for (i = 1; i < n; i ++)
      {
        e[i].a = i + 1;
        if (flag)
          e[i].b = i - get_rand() % ((i > 2) ? 3 : i);
        else
          e[i].b = get_rand() % i + 1;
        e[i].w = get_rand() % limit + 1;
        e[i].flag = 0;
        Ins_Hash(e[i].a, e[i].b, n);
      }
    for (i = 1; i <= q2; i ++)
      {
        if (flag)
          {
            tot = 0;
            do
              {
                a = get_rand() % (n-5) + 4;
                b = a - get_rand() % 3 - 1;
                tot ++;
              }
            while (tot <= 500 && Find_Hash(a, b, n));
            if (tot > 500)
              do
                {
                  a = get_rand() % n + 1;
                  b = get_rand() % n + 1;
                }
              while (a == b || Find_Hash(a, b, n));
          }
        else
          do
            {
              a = get_rand() % n + 1;
              b = get_rand() % n + 1;
            }
          while (a == b || Find_Hash(a, b, n));
        e[n-1+i].a = a, e[n-1+i].b = b;
        e[n-1+i].w = get_rand() % limit + 1;
        e[n-1+i].flag = 1;
        Ins_Hash(a, b, n);
      }
    
    for (i = n + q2; i <= m; i ++)
      {
        do
          {
            a = get_rand() % n + 1;
            b = get_rand() % n + 1;
          }
        while (a == b || Find_Hash(a, b, n));
        e[i].a = a, e[i].b = b, e[i].flag = 0;
        e[i].w = get_rand() % limit + limit + 1;
        Ins_Hash(a, b, n);
      }
    
    for (i = 1; i <= m; i ++) e[i].rank = get_rand();
    sort(e + 1, e + m + 1);
    
    fprintf(out, "%d %d %d\n", n, m, q1 + q2);
    for (i = 1; i <= m; i ++)
      fprintf(out, "%d %d %d\n", e[i].a, e[i].b, e[i].w);
    for (i = q1 + q2; i; i --)
      {
        x = get_rand() % (q1 + q2) + 1;
        if (x <= q1) ctrl = 0; else ctrl = 1;
        if (ctrl == 0)
          {
            do
              {
                a = get_rand() % n + 1;
                b = get_rand() % n + 1;
              }
            while (a == b);
            fprintf(out, "1 %d %d\n", a, b);
            q1 --;
          }
        else
          {
            do
              x = get_rand() % m + 1;
            while (! e[x].flag);
            e[x].flag = 0, fprintf(out, "2 %d %d\n", e[x].a, e[x].b);
            q2 --;
          }
      }
    
    fclose(out);
    printf("The work has finished!\n");
    system("pause");
    
    return 0;
  }
