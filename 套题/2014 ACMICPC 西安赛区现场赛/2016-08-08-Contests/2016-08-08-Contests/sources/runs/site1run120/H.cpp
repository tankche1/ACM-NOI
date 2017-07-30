# include<stdio.h>
# include<string.h>
# include<math.h>
# include<vector>
# include<queue>
# include<algorithm>
using namespace std;
const int maxn=110;
int _out[maxn];
int out[maxn][maxn];
vector<int> Back[maxn];

struct state{
    int Alice,Bob,who;//who==0 Alice go who==1 Bob go
    state() {}
    state(int Alice,int Bob,int who):Alice(Alice),Bob(Bob),who(who) {}
};
int n,m;
bool vis[maxn][maxn][2];
queue<state> Q;

int main(){
   // freopen("in.txt","r",stdin);
    int T,a,b;
    scanf("%d",&T);
    for(int Tcase=1;Tcase<=T;Tcase++){
        scanf("%d%d",&n,&m);
        int alice,bob;
        for(int i=1;i<=n;i++) Back[i].clear(),_out[i]=0;
        for(int i=1;i<=m;i++){
            scanf("%d%d",&a,&b);
            Back[b].push_back(a);_out[a]++;
        }

        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++) out[i][j]=_out[j];
        }
    scanf("%d %d",&bob,&alice);
        memset(vis,0,sizeof(vis));
        for(int i=1;i<=n;i++){
            if(out[i]==0){
                for(int j=1;j<=n;j++){
                    vis[j][i][1]=0;Q.push(state(j,i,1));
                }
            }
        }
        for(int i=1;i<=n;i++){
            if(!vis[i][i][1]) {vis[i][i][1]=1;Q.push(state(i,i,1));}
            if(!vis[i][i][0]) {vis[i][i][0]=1;Q.push(state(i,i,0));}
        }

        while(!Q.empty()){
            state now=Q.front();Q.pop();
            //printf("alice:%d bob:%d who:%d\n",now.Alice,now.Bob,now.who);
            if(now.who==1){
                for(int e=0;e<(int)Back[now.Alice].size();e++){
                    if(!vis[Back[now.Alice][e]][now.Bob][0]){
                        vis[Back[now.Alice][e]][now.Bob][0]=1;
                        Q.push(state(Back[now.Alice][e],now.Bob,0));
                    }
                }
            }
            else{
                for(int e=0;e<(int)Back[now.Bob].size();e++){
                    if((!vis[now.Alice][Back[now.Bob][e]][1])&&(--out[now.Alice][Back[now.Bob][e]]==0)){
                        vis[now.Alice][Back[now.Bob][e]][1]=1;
                        Q.push(state(now.Alice,Back[now.Bob][e],1));
                    }
                }
            }
        }

        bool ans=!vis[alice][bob][1];
        printf("Case #%d: ",Tcase);
        if(ans) puts("Yes");
        else puts("No");
    }
    return 0;
}
