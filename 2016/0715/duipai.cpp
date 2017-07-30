#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
const int mmax  = 60;

int max_num[mmax],min_num[mmax];
int L[mmax],R[mmax];
bool G[mmax][mmax];
int n,m1,m2;
void init()
{
    memset(G,0,sizeof G);
    for(int i=1;i<=n;i++)
    {
        L[i]=min_num[i]=1;
        R[i]=max_num[i]=n;
    }
}
int link[mmax];
bool vis[mmax];
int Match[mmax];
bool match(int x)
{
    for(int i=1;i<=n;i++)
    {
        if(G[x][i] && !vis[i])
        {
            vis[i]=1;
            if(link[i]==-1 || match(link[i]))
            {
                link[i]=x;
                Match[x]=i;
                return 1;
            }
        }
    }
    return 0;
}
int hungury()
{
    int cnt=0;
    memset(link,-1,sizeof link);
    for(int i=1;i<=n;i++)
    {
        memset(vis,0,sizeof vis);
        if(match(i))
            cnt++;
    }
    return cnt;
}
int main()
{
    int a,b,c;
    while(~scanf("%d %d %d",&n,&m1,&m2))
    {
        init();
        for(int i=1;i<=m1;i++)
        {
            scanf("%d %d %d",&a,&b,&c);
            for(int j=a;j<=b;j++)
                min_num[j]=max(min_num[j],c);
            L[c]=max(L[c],a);
            R[c]=min(R[c],b);
        }
        for(int i=1;i<=m2;i++)
        {
            scanf("%d %d %d",&a,&b,&c);
            for(int j=a;j<=b;j++)
                max_num[j]=min(max_num[j],c);
            L[c]=max(L[c],a);
            R[c]=min(R[c],b);
        }

        for(int i=1;i<=n;i++)
        {
            for(int j=min_num[i];j<=max_num[i];j++)
            {
                if(L[j]<=i && i<=R[j])
                    G[i][j]=1;
            }
        }
        int num = hungury();
        if(num==n)
        {

//            for(int i=1;i<=n;i++)
//                printf("%d%c",Match[i],i==n?'\n':' ');

            for(int i=1;i<=n;i++)
            {
                int tmp=Match[i];
                G[i][tmp]=0;
                link[tmp]=-1;
                bool fg=0;
                memset(vis,0,sizeof vis);
                for(int j=1;j<tmp;j++)
                {
                    if(!vis[j] && G[i][j])
                    {
                        vis[j]=1;
                        if(link[j]==-1 || match(link[j]))
                        {
                            link[j]=i;
                            Match[i]=j;
                            fg=1;
                            break;
                        }
                    }
                }
                if(!fg)
                {
                    G[i][tmp]=1;
                    link[tmp]=i;
                }
                tmp=Match[i];
                for(int j=1;j<=n;j++)
                    G[j][tmp]=0;
            }


            for(int i=1;i<=n;i++)
                printf("%d%c",Match[i],i==n?'\n':' ');
        }
        else
            puts("-1");
    }
    return 0;
}
