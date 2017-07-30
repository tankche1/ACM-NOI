#pragma comment(linker, "/STACK:1024000000,1024000000")
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<queue>
#define maxn 100100
#define maxm 300300
using namespace std;
struct node
{
    int v,num;
    node *next,*back;
};
struct QQ
{
    int u,du;
    bool operator <(const QQ &b)const
    {
        return du<b.du;
    }
    QQ(int u,int du)
    {
        this->u=u;
        this->du=du;
    }
};
priority_queue<QQ>Q;
int ans[maxm];
node *map[maxn];
node Edge[maxm*2];
node *cnt=Edge;
int n,m;
int u[maxm],v[maxm];
int f[maxn];
bool vis[maxm],visu[maxn];
int In[maxn],sum[maxn],d[maxn];
void add_edge(int u,int v,int num)
{
    node *p=cnt++,*q=cnt++;
    p->v=v;p->next=map[u];map[u]=p;p->num=num;
    if(p->next) p->next->back=p,p->back=NULL;
    q->v=u;q->next=map[v];map[v]=q;q->num=num;
    if(q->next) q->next->back=q,q->back=NULL;
    return;
}
void DFS(int uu)
{
    visu[uu]=true;
    for(node *p=map[uu];p;p=p->next)
        if(!vis[p->num])
        {
            vis[p->num]=true;
            if(p==map[uu])
            {
                map[uu]=p->next;
                if(map[uu]) map[uu]->back=NULL;
            }
            else
            {
                p->back->next=p->next;
                if(p->next) p->next->back=p->back;
            }
            if(visu[p->v])
            {
                if(p->v==v[p->num]) ans[p->num]=1;
                else ans[p->num]=0;
                int i=uu;
                while(i!=p->v)
                {
                    if(i==v[f[i]]) {ans[f[i]]=1;i=u[f[i]];}
                    else {ans[f[i]]=0;i=v[f[i]];}
                    visu[i]=false;
                }
            }
        }
        else
        {
            if(p==map[uu]) {map[uu]=p->next;if(map[uu]) map[uu]->back=NULL;}
            else
            {
                p->back->next=p->next;
                if(p->next) p->next->back=p->back;
            }
        }
    return;
}
int main()
{
    int T;
    cin>>T;
    while(T--)
    {
        memset(ans,-1,sizeof ans);
        scanf("%d%d",&n,&m);
        for(int i=1;i<=m;++i)
        {
            scanf("%d%d",u+i,v+i);
            if(u[i]==v[i])
            {
                ans[i]=1;
                continue;
            }
            add_edge(u[i],v[i],i);
        }
        DFS(1);
        for(int i=1;i<=n;++i)
            map[i]=NULL;
        cnt=Edge;
        for(int i=1;i<=m;++i)
        {
            if(u[i]==v[i])
            {
                ans[i]=1;
                continue;
            }
            if(ans[i]==-1) add_edge(u[i],v[i],i);
        }
        for(int i=1;i<=m;++i)
            if(ans[i]==-1)
            {
                d[u[i]]++;
                d[v[i]]++;
            }
        for(int i=1;i<=n;++i)
            if(d[i])
            {
                Q.push(QQ(i,d[i]));
                sum[i]=1;
            }
        while(!Q.empty())
        {
            QQ tmp=Q.top();
            sum[tmp.u]--;
            Q.pop();
            if(!sum[tmp.u])
            {
                for(node *p=map[tmp.u];p;p=p->next)
                    if(ans[p->num]==-1)
                    {
                        if(In[tmp.u]<=-1)
                        {
                            In[tmp.u]++;
                            ans[p->num]=(u[p->num]==tmp.u?1:0);
                            In[p->v]--;
                        }
                        else if(In[tmp.u]>=1)
                        {
                            In[tmp.u]--;
                            ans[p->num]=(u[p->num]==tmp.u?0:1);
                            In[p->v]++;
                        }
                        else
                        {
                            if(In[p->v]==1)
                            {
                                In[tmp.u]++;
                                ans[p->num]=(u[p->num]==tmp.u?1:0);
                                In[p->v]--;
                            }
                            else
                            {
                                In[tmp.u]--;
                                ans[p->num]=(u[p->num]==tmp.u?0:1);
                                In[p->v]++;
                            }
                        }
                        d[p->v]--;
                        Q.push(QQ(p->v,d[p->v]));
                        sum[p->v]++;
                    }
            }
        }
        bool flag=true;
        for(int i=1;i<=n;++i)
            if(In[i]<-1||In[i]>1) flag=false;
        if(flag)
        {
            for(int i=1;i<=m;++i)
                printf("%d\n",ans[i]);
        }
        else printf("-1\n");
        for(int i=1;i<=n;++i)
            map[i]=NULL;
        cnt=Edge;
        memset(vis,0,sizeof vis);
        memset(visu,0,sizeof visu);
        memset(d,0,sizeof d);
        memset(In,0,sizeof In);
        memset(f,0,sizeof f);
    }
    return 0;
}
