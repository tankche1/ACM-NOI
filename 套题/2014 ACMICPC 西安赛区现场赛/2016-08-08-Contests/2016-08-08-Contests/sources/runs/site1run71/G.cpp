#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int MAXL=200005,SIGMA=26;

struct PT
{
    int ch[MAXL][SIGMA],fail[MAXL],s[MAXL],cnt[MAXL],num[MAXL],len[MAXL],last,n,p;

    int newnode(int l)
    {
        memset(ch[p],0,sizeof(ch[p]));
        cnt[p]=num[p]=0;
        len[p]=l;
        return p++;
    }

    void init()
    {
        p=0;
        newnode(0);
        newnode(-1);
        last=n=0;
        s[n]=-1;
        fail[0]=1;
    }

    int getfail(int x)
    {
        while (s[n]!=s[n-len[x]-1]) x=fail[x];
        return x;
    }

    void add(int c)
    {
        c-='a';
        s[++n]=c;
        int cur=getfail(last);
        if (!ch[cur][c])
        {
            int now=newnode(len[cur]+2);
            fail[now]=ch[getfail(fail[cur])][c];
            ch[cur][c]=now;
            num[now]=num[fail[now]]+1;
        }
        last=ch[cur][c];
        cnt[last]++;
    }

    void count()
    {
        for (int i=p-1;i>=0;i--) cnt[fail[i]]+=cnt[i];
    }
}Tree1,Tree2;

LL ans;
char s1[MAXL],s2[MAXL];

void dfs(int x,int y)
{
    for (int i=0;i<SIGMA;i++)
        if (Tree1.ch[x][i]&&Tree2.ch[y][i])
        {
            ans+=(LL)Tree1.cnt[Tree1.ch[x][i]]*Tree2.cnt[Tree2.ch[y][i]];
            dfs(Tree1.ch[x][i],Tree2.ch[y][i]);
        }
}

int main()
{
    //freopen("G.in","r",stdin);
    int T;
    scanf("%d",&T);
    for (int i=1;i<=T;i++)
    {
        scanf("%s%s",s1,s2);
        int l1=strlen(s1),l2=strlen(s2);
        Tree1.init();
        Tree2.init();
        for (int i=0;i<l1;i++) Tree1.add(s1[i]);
        for (int i=0;i<l2;i++) Tree2.add(s2[i]);
        Tree1.count();Tree2.count();
        ans=0;
        dfs(0,0);
        dfs(1,1);
        printf("Case #%d: %lld\n",i,ans);
    }
    return 0;
}
