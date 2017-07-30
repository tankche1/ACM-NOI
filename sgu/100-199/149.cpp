# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
const int maxn=10010;
int n;
int first[maxn],nnext[maxn],v[maxn],fa[maxn],w[maxn],edge=0;
int up[maxn],down1[maxn],down2[maxn];

void add_edge(int a,int b,int c){
    nnext[edge]=first[a];v[edge]=b;w[edge]=c;first[a]=edge++;
}

void dfs1(int x){
    down1[x]=0;down2[x]=-1;
    for(int e=first[x];e!=-1;e=nnext[e]){
        dfs1(v[e]);
        if(down1[x]<down1[v[e]]+w[e])
            down2[x]=down1[x],down1[x]=down1[v[e]]+w[e];
        else if(down2[x]<down1[v[e]]+w[e])
            down2[x]=down1[v[e]]+w[e];
    }
    //printf("down1[%d]:%d\n",x,down1[x]);
    return;
}

void dfs2(int x){
    for(int e=first[x];e!=-1;e=nnext[e]){
        up[v[e]]=up[x]+w[e];
        if(down1[v[e]]+w[e]==down1[x])
            up[v[e]]=max(up[v[e]],down2[x]+w[e]);
        else up[v[e]]=max(up[v[e]],down1[x]+w[e]);
        dfs2(v[e]);
    }
    return;
}

int main(){
    int a,b;
    scanf("%d",&n);
    memset(first,-1,sizeof(first));edge=0;
    for(int i=2;i<=n;i++){
        scanf("%d%d",&a,&b);
        fa[i]=a;add_edge(a,i,b);
    }
    up[1]=0;
    dfs1(1);
    dfs2(1);
    for(int i=1;i<=n;i++){
        printf("%d\n",max(up[i],down1[i]));
    }
    return 0;
}
