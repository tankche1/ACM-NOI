#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<set>
using namespace std;

const int MaxN=100007;

int T,n,w[MaxN],id[MaxN];
int maxx[MaxN][20],lg[MaxN];
int ans[MaxN],tmp[MaxN];
set<int> iset;
set<int>::iterator iter;
bool vis[MaxN];

void Init()
{
    int i,j;
    scanf("%d",&n);
    for(i=1;i<=n;i++) scanf("%d",w+i);
    iset.clear();
    for(i=1;i<=n;i++) id[w[i]]=i,tmp[i]=i,ans[i]=0,vis[i]=false;
    for(i=2;i<=n;i++)
    {
        lg[i]=lg[i-1];
        if(i>=(1<<(lg[i]+1))) lg[i]++;
    }
    for(i=1;i<=n;i++) maxx[i][0]=w[i];
    for(j=1;(1<<j)<=n+1;j++)
        for(i=1;i+(1<<j)<=n+1;i++)
            maxx[i][j]=max(maxx[i][j-1],maxx[i+(1<<(j-1))][j-1]);
    return;
}

inline int Query(int l,int r)
{
    if(l>r) return -1;
    int tmp=lg[r-l+1];
    return max(maxx[l][tmp],maxx[r-(1<<tmp)+1][tmp]);
}

void Solve()
{
    int i,j,k,u,l,r;
    for(i=1;i<=n;i++)
    {
        u=id[i];
        if(vis[u]) continue;
        //cout<<"Count: "<<i<<' '<<tmp[i]<<endl;
        if(vis[u-1]&&vis[u+1])
        {
            vis[u]=true;
            ans[i]=tmp[i];
            continue;
        }
        iter=iset.lower_bound(u);
        if(iter==iset.begin()) l=1;
        else iter--,l=(*iter)+1;
        r=u-1;
        j=Query(l,r);
        //cout<<l<<' '<<r<<' '<<j<<' '<<vis[i+1]<<endl;
        if(!vis[i+1]&&j>w[i+1])
        {
            //cout<<u<<"-->"<<endl;
            for(k=u-1;w[k]!=j;k--);
            for(j=k;j<u;j++) ans[w[j]]=w[j+1],vis[j]=true;
            ans[w[u]]=w[k],vis[u]=true;
            iset.insert(u);
            //for(j=k;j<=u;j++) cout<<w[j]<<"-->"<<ans[w[j]]<<endl;
        }
        else
        {
            if(vis[u+1]||w[u]>w[u+1]) ans[i]=tmp[i],vis[u]=true;
            else
            {
                //cout<<i<<"->"<<w[u+1]<<endl;
                ans[i]=w[u+1],vis[u]=true; tmp[w[u+1]]=tmp[i];
                iset.insert(u+1);
            }
        }
/*
    cout<<"=========================="<<endl;
    for(int i=1;i<=n;i++) printf("%d ",ans[i]);
    printf("\n");
    cout<<"=========================="<<endl;
*/
    }
    for(i=1;i<=n;i++) printf("%d ",ans[i]);
    printf("\n");
    return;
}

int main()
{
    freopen("12.in","r",stdin);
    freopen("12.out","w",stdout);
    scanf("%d",&T);
    while(T--)
    {
        Init();
        Solve();
    }
}
