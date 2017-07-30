#include<iostream>
#include<cstdio> 
#include<cstring> 
#include<cmath>
#include<cstdlib>
#include<algorithm>
using namespace std;
const int MAX_N = 100001, MAX_M = 5000001, INF = 1000000000; 
int g[MAX_M], next[MAX_M], c[MAX_N], nm, flow[MAX_M], cost[MAX_M]; 
int Q[MAX_M], vd[MAX_N], pre[MAX_N], pn[MAX_N], d[MAX_N];
int n, m, nn, rt; int a[1001][1001]; int S, T, ans, cnt; int b[1001][1001]; 
int vi[MAX_N];  int p[MAX_N]; int rd[MAX_N];   
void addedge(int x, int y, int w, int ct){
	g[nm] = y;      next[nm] = c[x];      c[x] = nm;  
    flow[nm] = w;      cost[nm] = ct;      nm++; 
	}    
	void add(int x, int y, int w, int ct){     
		addedge(x, y, w, ct);      addedge(y, x, 0, -ct); }    int spfa(){     for (int i = 1; i <= cnt; ++i) d[i] = INF;     int l = 1, r = 0;     memset(vd, 0, sizeof vd);     d[S] = 0;     Q[r = 1] = S;     for (; l <= r; ++l){         int i = Q[l];         vd[i] = 0;         for (int k = c[i]; k != -1; k = next[k]){             int j = g[k];             if (flow[k])                if (d[i] + cost[k] < d[j]){                   pre[j] = i;                   pn[j] = k;                   d[j] = d[i] + cost[k];                   if (!vd[j]){                      vd[j] = 1;                      Q[++r] = j;                   }                }         }     }     return d[T] != INF; }    
		void aug(){      int ret = INF;      for (int i = T; i != S; i = pre[i])          ret = min(ret, flow[pn[i]]); // printf("ret:%d\n",ret);
			//if(ret>1) puts("fuck");
			
			for (int i = T; i != S; i = pre[i]){          vi[i] = 1;          flow[pn[i]] -= ret;          flow[pn[i] ^ 1] += ret;          ans += ret * cost[pn[i]];      }      rt += ret; }   
		void add_x(int i, int j){      b[i][j] = ++cnt;      for (int k = 1; k <= nn; ++k)          add(k + 2, b[i][j], 1, j * a[i][k]);      add(b[i][j], T, 1, 0); }    
		int main(){  	freopen("delicacy.in","r",stdin);
	freopen("delicacy.ans","w",stdout);  scanf("%d%d", &nn, &m);     for (int i = 1; i <= nn; ++i) scanf("%d", &p[i]), n += p[i];     for (int i = 1; i <= nn; ++i)         for (int j = 1; j <= m; ++j)             scanf("%d", &a[j][i]);     S = 1;     T = 2;     cnt = 2;     memset(c, -1, sizeof c);     for (int i = 1; i <= nn; ++i)         add(S, ++cnt, p[i], 0);     for (int i = 1; i <= m; ++i){         rd[i] = 1;         add_x(i, rd[i]);     }    
		while (spfa()){  
			aug();         // int tt=0;
			
			for (int i = 1; i <= m; ++i)               if (vi[b[i][rd[i]]]) add_x(i, ++rd[i]); //  if(tt!=1) puts("fuck");
				
				}     
			printf("%d\n", ans);
			}
			