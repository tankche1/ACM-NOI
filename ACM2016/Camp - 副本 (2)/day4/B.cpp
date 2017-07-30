# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
int ans=0;
int dp[32][1<<16];
int G[1<<16];
int n,m;
int g[32][32];
int bh[32];
int col[32],cnt=0;
int num1=0,num2=0;
int cover[32];
int l_cover[32];

void dfs(int x){
    for(int i=1;i<=n;i++){
        if(g[x][i]&&col[i]==0){
            col[i]=3-col[x];dfs(i);
        }
    }
}
bool vis[31];

void solve(){
    for(int i=1;i<=num1;i++){
        l_cover[i]=0;
        for(int j=1;j<=num2;j++){
            if(g[i][j]){
                l_cover[i]|=1<<(j-1);
            }
        }
    }
    memset(dp,0,sizeof(dp));
    dp[0][0]=1;
    for(int j=1;j<=num2;j++){
        cover[j]=0;
        for(int i=1;i<=num1;i++){
            if(g[i][j]){
                cover[j]|=1<<(i-1);
            }
        }
    }

    for(int i=0;i<num2;i++){
        for(int j=0;j<(1<<num1);j++){
            if(dp[i][j]){
                dp[i+1][j]+=dp[i][j];
                dp[i+1][j|cover[i+1]]+=dp[i][j];
            }
        }
    }
    for(int j=0;j<(1<<num1);j++) G[j]=dp[num2][j];

    for(int i=1;i<=num1;i++){
        for(int j=0;j<(1<<num1);j++){
            if((j&(1<<(i-1)))==0) G[j]+=G[j^(1<<(i-1))];
        }
    }

    /*for(int j=0;j<(1<<num1);j++){
        printf("G[%d]:%d\n",j,G[j]);
    }*/

    int right,tmp,left=0;
    for(int choose=0;choose<(1<<num1);choose++){
        right=0;
        for(int i=1;i<=num1;i++){
            if((choose>>(i-1))&1){
                right|=l_cover[i];
            }
        }
        tmp=0;left=choose;
        for(int j=1;j<=num2;j++) if(((right>>(j-1))&1)==0) {tmp++;left|=cover[j];}
        //printf("choose:%d right:%d tmp:%d G:%d \n",choose,right,tmp,G[((1<<num1)-1)^left]/(1<<tmp));
        ans+=G[((1<<num1)-1)^left]/(1<<tmp);
    }
    printf("%d\n",ans);
}

int main(){
    int a,b;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        scanf("%d%d",&a,&b);g[a][b]=g[b][a]=1;
    }

    for(int i=1;i<=n;i++){
        if(col[i]==0) col[i]=1,dfs(i);
    }
    int num=0;
    for(int i=1;i<=n;i++) if(col[i]==1) num++;
    if(num>n-num){
        for(int i=1;i<=n;i++) col[i]=3-col[i];
    }

    for(int i=1;i<=n;i++){
        if(col[i]==1) {
                bh[i]=++num1;

        }
        else bh[i]=++num2;
    }
    int C[31][31];
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) C[i][j]=g[i][j];
    memset(g,0,sizeof(g));
    for(int i=1;i<=n;i++){
        if(col[i]==1){
            for(int j=1;j<=n;j++){
                if(col[j]==2&&C[i][j]==1)
                    g[bh[i]][bh[j]]=1;
            }
        }
        //printf("col[%d]:%d\n",i,col[i]);
    }
    solve();
    return 0;
}
