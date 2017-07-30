# include<stdio.h>
# include<string.h>
# include<queue>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=110;
int n,m;
int Bob,Alice;
vector<int> G[maxn],Back[maxn];
bool vis[maxn][maxn][2];
int out[maxn];
int _out[maxn][maxn];

struct state{
    int Bob,Alice,who;
    state(int Bob=0,int Alice=0,int who=0):Bob(Bob),Alice(Alice),who(who) {}
};

queue<state> Q;

int main(){
    int T,a,b;
    bool ans;
    scanf("%d",&T);
    for(int Tcase=1;Tcase<=T;Tcase++){

        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++) G[i].clear(),Back[i].clear(),out[i]=0;
        for(int i=1;i<=m;i++){
            scanf("%d%d",&a,&b);
            G[a].push_back(b);out[a]++;
            Back[b].push_back(a);
        }

        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                _out[i][j]=out[i];
            }
        }

        scanf("%d%d",&Bob,&Alice);
        memset(vis,0,sizeof(vis));

        while(!Q.empty()) Q.pop();
        for(int i=1;i<=n;i++)
            Q.push(state(i,i,0)),Q.push(state(i,i,1)),vis[i][i][0]=1,vis[i][i][1]=1;
        for(int i=1;i<=n;i++){
            if((int)G[i].size()==0){
                for(int j=1;j<=n;j++)
                    if(i!=j) Q.push(state(i,j,0)),vis[i][j][0]=1;
            }
        }

        state st;int v;
        while(!Q.empty()){
            st=Q.front();Q.pop();
            //printf("Bob:%d Alice:%d who:%d\n",st.Bob,st.Alice,st.who);
            //if(!vis[st.Bob][st.Alice][st.who]) puts("fuck");
            if(st.who==0){
                for(int e=0;e<(int)Back[st.Alice].size();e++){
                    v=Back[st.Alice][e];
                    if(!vis[st.Bob][v][1]){
                        vis[st.Bob][v][1]=1;
                        Q.push(state(st.Bob,v,1));
                    }
                }
            }
            else{
                for(int e=0;e<(int)Back[st.Bob].size();e++){
                    v=Back[st.Bob][e];--_out[v][st.Alice];
                    if(!vis[v][st.Alice][0]&&_out[v][st.Alice]==0){
                        vis[v][st.Alice][0]=1;
                        Q.push(state(v,st.Alice,0));
                    }
                }
            }
        }

        ans=vis[Bob][Alice][0];

        printf("Case #%d: ",Tcase);
        if(ans==0) puts("Yes");
        else puts("No");
    }
    return 0;
}
