#include<iostream>
#include<cstdio>
#include<cstring>
typedef long long ll;
using namespace std;
int s[400010][2],go[400010][26];
int l[400010],fa[400010];
char a[200010];
int n,t,last,cas,i;

int getf(int x)
{
    while (a[i-l[x]-1]!=a[i]) x=fa[x];
    return x;
}

void newnode(int w)
{
    l[++t]=w; fa[t]=0;s[t][0]=s[t][1]=0;
    memset(go[t],0,sizeof(go[t]));
}

void add(int c,int w)
{
    int cur=getf(last);
    if (!go[cur][c])
    {
        newnode(l[cur]+2);
        fa[t]=go[getf(fa[cur])][c];
        go[cur][c]=t;
    }
    last=go[cur][c];
    s[last][w]++;
}

int main()
{
    scanf("%d",&cas);
    for (int tt=1;tt<=cas; tt++)
    {
        scanf("%s",a+1);
        n=strlen(a+1);
        t=-1;
        newnode(0); newnode(-1);
        fa[0]=1; fa[1]=1; last=0;
        for (i=1; i<=n; i++)
          add(a[i]-'a',0);
        scanf("%s",a+1);
        n=strlen(a+1); last=0;
        for (i=1; i<=n; i++)
          add(a[i]-'a',1);
        for (i=t; i>=1; i--)
        {
            s[fa[i]][0]+=s[i][0];
            s[fa[i]][1]+=s[i][1];
        }
        ll ans=0;
        for (i=2; i<=t; i++)
          ans+=(ll)s[i][0]*(ll)s[i][1];
        cout <<"Case #"<<tt<<": "<<ans<<endl;
    }
    return 0;
}


