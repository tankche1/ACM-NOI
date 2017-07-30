# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=100010;
vector<int> to[maxn],from[maxn],way[maxn],G[maxn];
int in[maxn],out[maxn];
int n,m;
bool vis[maxn];

int cnt;
int S[maxn],top=-1;
bool dfs(int x,int now){
    vis[x]=1;S[++top]=x;
    printf("x:%d\n",x);
    if(now==cnt){
        for(int e=0;e<G[x].size();e++){
            if(to[x][e]==1){
                S[++top]=1;
                printf("%d",1);
                for(int i=0;i<top;i++){
                    for(int e=0;e<G[S[i]].size();e++){
                        if(G[S[i]][e]==S[i+1]){
                            if(way[S[i]][e]!=0){
                                printf(" %d",way[S[i]][e]);
                                int o=way[S[i]][e];
                                while(to[o][0]!=S[i+1]){
                                    printf(" %d",to[o][0]);
                                    o=to[o][0];
                                }

                            }printf(" %d",S[i+1]);
                        }
                    }
                }
                return true;
            }
        }
        vis[x]=0;
        return false;
    }

    for(int e=0;e<G[x].size();e++){
        if(!vis[G[x][e]]){
            if(dfs(G[x][e],now+1)) return true;
        }
    }
    vis[x]=0;
    top--;
    return false;
}

int main(){
    int a,b;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        scanf("%d%d",&a,&b);in[b]++;out[a]++;
        to[a].push_back(b);G[a].push_back(b);way[a].push_back(0);from[b].push_back(a);
    }
    cnt=n;
    for(int i=2;i<=n;i++){
        if(in[i]==1&&out[i]==1){
            G[from[i][0]].push_back(to[i][0]);
            way[from[i][0]].push_back(i);
        }
        cnt--;
    }

    //for(int i=0;i<to[1].size();i++) G[1].push_back(to[1][i]);

    if(!dfs(1,1)) puts("There is no route, Karl!\n");
    return 0;
}
