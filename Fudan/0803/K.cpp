# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
const int maxn=28;
int a[maxn][maxn];
int n=26,m;
bool vis[maxn];
int loop[maxn];
int S[maxn*2],top;
bool go[maxn];

bool find(int x){
    S[++top]=x;vis[x]=1;go[x]=1;
    int u;
    for(int i=1;i<=n;i++){
        if(!a[x][i]) continue;
        if(vis[i]){
            u=S[top--];loop[++loop[0]]=u;
            while(u!=i){
                u=S[top--];loop[++loop[0]]=u;
            }
            return true;
        }
        else if(go[i]) continue;
        else if(find(i)) return true;
    }
    top--;vis[x]=false;
    return false;
}
int ans[30][30];
int dp[maxn];
int len,st;

void dfs(int x){
    if(dp[x]!=0) return;
    dp[x]=1;
    for(int i=1;i<=26;i++){
        if(!a[x][i]) continue;
        dfs(i);dp[x]=max(dp[x],dp[i]+1);
    }
    if(dp[x]>len) len=dp[x],st=x;
    return;
}

int lian[maxn];
int main(){
   // freopen("in.txt","r",stdin);
    int tcase;
    int x,y;
    char tt;
    scanf("%d",&tcase);
    while(tcase--){
        for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) a[i][j]=1;
        scanf("%d",&m);
        for(int i=1;i<=m;i++){
            while((tt=getchar())&&(tt<'a'||tt>'z'));x=tt-'a'+1;
            while((tt=getchar())&&(tt<'a'||tt>'z'));y=tt-'a'+1;
            a[x][y]=0;
        }
        memset(vis,false,sizeof(vis));loop[0]=0;top=-1;
        memset(go,false,sizeof(go));
        for(int i=1;i<=n;i++){
            memset(vis,false,sizeof(vis));
            if(find(i)) break;
        }
        int pos;
        if(loop[0]>0){
            for(int i=1;i<loop[0]-i+1;i++)
            swap(loop[i],loop[loop[0]-i+1]);
            pos=1;
            for(int i=1;i<=20;i++){
                ans[1][i]=pos++;if(pos>loop[0]) pos=1;
            }
            for(int j=1;j<=20;j++){
                pos=ans[1][j]+1;if(pos>loop[0]) pos=1;
                for(int i=2;i<=20;i++){
                    ans[i][j]=pos++;if(pos>loop[0]) pos=1;
                }
            }
            m=20;
            for(int i=1;i<=m;i++){
                for(int j=1;j<=m;j++)
                    printf("%c",loop[ans[i][j]]+'a'-1);
                puts("");
            }
        }
        else{
            memset(dp,0,sizeof(dp));len=0;lian[0]=0;
            for(int i=1;i<=n;i++) dfs(i);
            for(int i=1;i<=len;i++){
                lian[++lian[0]]=st;
                for(int j=1;j<=n;j++)
                    if((dp[j]+1==dp[st])&&a[st][j]) {st=j;break;}
            }
            if(lian[0]%2==0) lian[0]--;
            m=(lian[0]+1)/2;
            for(int i=1;i<=m;i++){
                ans[1][i]=i;
            }
            for(int j=1;j<=m;j++){
                pos=ans[1][j];
                for(int i=2;i<=m;i++){
                    pos++;ans[i][j]=pos;
                }
            }
            for(int i=1;i<=m;i++){
                for(int j=1;j<=m;j++)
                    printf("%c",lian[ans[i][j]]+'a'-1);
                puts("");
            }
        }

    }
    return 0;
}
