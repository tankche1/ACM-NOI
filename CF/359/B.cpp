# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=300010;

vector<int> G[maxn];
int n,q;
int sz[maxn],son[maxn],fa[maxn],ans[maxn];

void dfs1(int x){
    sz[x]=1;son[x]=((int)G[x].size()>0)?G[x][0]:0;
    for(int e=0;e<(int)G[x].size();e++){
        dfs1(G[x][e]);sz[x]+=sz[G[x][e]];
        if(sz[G[x][e]]>sz[son[x]]) son[x]=G[x][e];
    }
}

int S[maxn],top;

void dfs2(int x){
    if(top>=0){
        int L=0,R=top,M;
        while(L<=R){
            M=(L+R)>>1;
            if(sz[x]>=sz[S[M]]-sz[S[M]]/2) R=M-1;
            else L=M+1;
        }
        int qr=R+1;
        //if(qr>top) goto Loop;

        L=0;R=top;
        while(L<=R){
            M=(L+R)>>1;
            if(sz[son[x]]<=sz[S[M]]/2) L=M+1;
            else R=M-1;
        }

        int ql=L-1;
        for(int i=qr;i<=ql;i++){
            ans[S[i]]=x;
        }
    }

    if(sz[son[x]]<=sz[x]/2) ans[x]=x;

    S[++top]=x;
    for(int e=0;e<(int)G[x].size();e++){
        dfs2(G[x][e]);
    }

    top--;
}

int main(){
    scanf("%d%d",&n,&q);
    for(int i=2;i<=n;i++) {
        scanf("%d",&fa[i]);G[fa[i]].push_back(i);
    }

    dfs1(1);sz[0]=0;

    top=-1;
    dfs2(1);

    int a;
    for(int i=1;i<=q;i++){
        scanf("%d",&a);
        printf("%d\n",ans[a]);
    }
    return 0;
}
