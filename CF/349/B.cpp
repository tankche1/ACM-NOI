# include<stdio.h>
# include<string.h>
# include<iostream>
# include<vector>
# include<bitset>
# include<algorithm>
using namespace std;
const int maxn=3010;
const int maxm=5010;
int n,m;
int a,b;
int d[maxn][maxn];
int q[maxn];
int front,tail;

int first[maxn],next[maxm],v[maxm],edge=0;
void add_edge(int a,int b){
    next[edge]=first[a];v[edge]=b;first[a]=edge++;
}
int from[maxn][3],to[maxn][3];

void bfs(int S){
    for(int i=1;i<=n;i++) d[S][i]=-1;
    d[S][S]=0;
    q[front=tail=0]=S;
    int x;
    while(front<=tail){
        x=q[front++];
        for(int e=first[x];e!=-1;e=next[e]){
            if(d[S][v[e]]==-1) d[S][v[e]]=d[S][x]+1,q[++tail]=v[e];
        }
    }


}

void update(int S){

    to[S][0]=to[S][1]=to[S][2]=from[S][0]=from[S][1]=from[S][2]=-1;
    for(int i=1;i<=n;i++){
        if(d[S][i]!=-1&&i!=S){
            if(to[S][0]==-1||d[S][i]>=d[S][to[S][0]]){
                to[S][2]=to[S][1];to[S][1]=to[S][0];to[S][0]=i;
            }
            else if(to[S][1]==-1||d[S][i]>=d[S][to[S][1]]){
                to[S][2]=to[S][1];to[S][1]=i;
            }
            else if(to[S][2]==-1||d[S][i]>=d[S][to[S][2]]){
                to[S][2]=i;
            }
        }

        if(d[i][S]!=-1&&i!=S){
            if(from[S][0]==-1||d[i][S]>=d[from[S][0]][S]){
                from[S][2]=from[S][1];from[S][1]=from[S][0];from[S][0]=i;
            }
            else if(from[S][1]==-1||d[i][S]>=d[from[S][1]][S]){
                from[S][2]=from[S][1];from[S][1]=i;
            }
            else if(from[S][2]==-1||d[i][S]>=d[from[S][2]][S]){
                from[S][2]=i;
            }
        }
    }
}

int main(){
    edge=0;memset(first,-1,sizeof(first));
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        scanf("%d%d",&a,&b);
        add_edge(a,b);
    }

    for(int i=1;i<=n;i++){
        bfs(i);
    }

    for(int i=1;i<=n;i++) update(i);

    int ans=0;
    int p1,p2,p3,p4;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(i==j||d[i][j]==-1) continue;
            for(int c=0;c<3;c++){
                if(from[i][c]!=j&&from[i][c]!=-1){
                    for(int dd=0;dd<3;dd++){
                        if(to[j][dd]!=-1&&to[j][dd]!=i&&to[j][dd]!=from[i][c]){
                            if(d[from[i][c]][i]+d[i][j]+d[j][to[j][dd]]>ans){
                                ans=d[from[i][c]][i]+d[i][j]+d[j][to[j][dd]];
                                p1=from[i][c];p2=i;p3=j;p4=to[j][dd];
                            }

                        }
                    }
                }

            }
        }
    }

    //printf("%d\n",ans);
    printf("%d %d %d %d\n",p1,p2,p3,p4);
    return 0;
}
