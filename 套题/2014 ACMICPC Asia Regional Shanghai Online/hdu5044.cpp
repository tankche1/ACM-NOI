# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=100010<<1;
int n,m;
int first[maxn],nex[maxn<<1],v[maxn<<1],edge;
LL addv[maxn][2];
int dp[maxn][18],dep[maxn];
int Step=16;

template <class T>
inline bool read(T &ret) {
	char c; int sgn;
	if(c=getchar(),c==EOF) return 0; //EOF
	while(c!='-'&&(c<'0'||c>'9')) c=getchar();
	sgn=(c=='-')?-1:1;
	ret=(c=='-')?0:(c-'0');
	while(c=getchar(),c>='0'&&c<='9') ret=ret*10+(c-'0');
	ret*=sgn;
	return 1;
}

void add_edge(int a,int b){
    nex[edge]=first[a];v[edge]=b;first[a]=edge++;
}

void dfs1(int x){
    for(int e=first[x];e!=-1;e=nex[e]){
        if(v[e]==dp[x][0]) continue;
        dp[v[e]][0]=x;dep[v[e]]=dep[x]+1;
        dfs1(v[e]);
    }
}

void prepare(){
    for(int j=1;j<=Step;j++){
        for(int i=1;i<=n;i++){
            dp[i][j]=dp[dp[i][j-1]][j-1];
        }
    }
}

int Lca(int a,int b){
    if(dep[a]<dep[b]) swap(a,b);
    int j=dep[a]-dep[b],k=0;
    while(j>0){
        if(j&1) a=dp[a][k];
        j>>=1;k++;
    }
    j=Step;
    while(a!=b){
        while(dp[a][j]==dp[b][j]&&j>0) j--;
        a=dp[a][j];b=dp[b][j];
    }
    return a;
}

void dfs2(int x){
    for(int e=first[x];e!=-1;e=nex[e]){
        if(v[e]==dp[x][0]) continue;
        dfs2(v[e]);
    }
    if(x!=1){
        addv[dp[x][0]][0]+=addv[x][0];
        addv[dp[x][0]][1]+=addv[x][1];
    }
}

int main(){
    int T;
    int a,b,c,anc,type;
    char op[20];
    scanf("%d",&T);
    for(int Tcase=1;Tcase<=T;Tcase++){
        read(n);read(m);
        edge=0;
        for(int i=1;i<n+n;i++) addv[i][0]=addv[i][1]=0,first[i]=-1;
        for(int i=1;i<n;i++){
            read(a);read(b);
            add_edge(a,n+i);add_edge(n+i,a);
            add_edge(n+i,b);add_edge(b,n+i);
        }
        dp[1][0]=1;dep[1]=1;dfs1(1);
        prepare();

        for(int i=1;i<=m;i++){
            scanf("%s",op);
            if(op[3]=='1') type=0;
            else type=1;
            read(a);read(b);read(c);
            anc=Lca(a,b);
            addv[a][type]+=c;addv[b][type]+=c;
            addv[anc][type]-=c;
            if(anc!=1) addv[dp[anc][0]][type]-=c;
        }
        dfs2(1);

        printf("Case #%d:\n",Tcase);
        for(int i=1;i<n;i++) printf("%I64d ",addv[i][0]);printf("%I64d\n",addv[n][0]);
        for(int i=1;i<n-1;i++) printf("%I64d ",addv[n+i][1]);
        if(n>1) printf("%I64d",addv[n+n-1][1]);
        puts("");
    }
    return 0;
}
