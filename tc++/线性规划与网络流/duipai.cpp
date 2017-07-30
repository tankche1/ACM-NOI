#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
using namespace std;
const int MAXN=1001;
struct edge
{
    edge *next;
    int t;
}*V[MAXN],ES[MAXN*2];
int N,M,X,Y,EC;
int dist[MAXN],path[MAXN][MAXN],deg[MAXN],Q[MAXN];
double F[MAXN][MAXN];
bool flag[MAXN];
inline void addedge(int a,int b)
{
    ES[++EC].next = V[a];
    V[a]=ES+EC; V[a]->t=b;
    deg[a]++;
}
void init()
{
    int i,j,a,b;
    //freopen("cchkk.in","r",stdin);
    //freopen("cchkk.out","w",stdout);
    scanf("%d%d%d%d",&N,&M,&X,&Y);
    for (i=1;i<=M;i++)
    {
        scanf("%d%d",&a,&b);
        addedge(a,b);
        addedge(b,a);
    }
    for (i=1;i<=N;i++)
    {
        for (j=1;j<=N;j++)
            F[i][j]=-1;
        F[i][i]=0;
    }
}
void APSP()
{
    int i,j,k,head,tail;
    for (k=1;k<=N;k++)
    {
        memset(dist,-1,sizeof(dist));
        dist[k]=0;
        path[k][k]=k;
        for (Q[head=tail=0]=k;head<=tail;)
        {
            i=Q[head++];
            for (edge *e=V[i];e && (j=e->t);e=e->next)
            {
                if (dist[j] == -1)
                {
                    dist[j] = dist[i] + 1;
                    path[j][k] = i;
                    Q[++tail]=j;
                }
                else if (dist[j] == dist[i] + 1 && i < path[j][k])
                    path[j][k] = i;
            }
        }
    }
}
double dp(int i,int j)
{
    if (F[i][j]==-1)
    {
        double rs=0;
        int x = path[ path[i][j] ][j];
        rs = dp(x,j) + 1;
        if (x!=j)
        {
            for (edge *e=V[j];e;e=e->next)
                rs += dp(x,e->t) + 1;
            rs /= deg[j] + 1;
			printf("mouse:%d cat:%d res:%.3lf\n",j,i,
        }
        F[i][j]=rs;
		
    }
	printf("mouse:%d cat:%d res:%.3lf\n",j,i,F[i][j]);
    return F[i][j];
}

int main()
{
    init();
    APSP();
    printf("%.3lfn",dp(X,Y));
    return 0;
}