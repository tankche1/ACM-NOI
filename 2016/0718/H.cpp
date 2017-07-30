# include<stdio.h>
# include<string.h>
# include<queue>
# include<algorithm>
using namespace std;

int n,m;
int vis[5001][5001];
int a[30];

typedef pair<int,int> pi;
queue<pi> Q;

int main(){
    int T;
    scanf("%d",&T);
    memset(vis,-1,sizeof(vis));
    for(int Tcase=1;Tcase<=T;Tcase++){
        scanf("%d%d",&n,&m);
        for(int i=1;i<=m;i++)
            scanf("%d",&a[i]);
        int bh=Tcase;
        while(!Q.empty()) Q.pop();
        Q.push(make_pair(0,0));
        int score,num,new_score,new_num;

        int ans=-1;
        while(!Q.empty()){
            score=Q.front().first,num=Q.front().second;Q.pop();
            if(score==n) ans=max(ans,num);

            for(int i=1;i<=m;i++){
                new_num=num+a[i];new_score=score+new_num;
                if(new_score<=n&&vis[new_score][new_num]!=bh){
                    vis[new_score][new_num]=bh;
                    Q.push(make_pair(new_score,new_num));
                }
            }
        }

        printf("%d\n",ans);
    }
    return 0;
}
