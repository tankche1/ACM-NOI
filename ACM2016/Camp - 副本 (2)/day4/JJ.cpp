# include<stdio.h>
# include<string.h>
# include<time.h>
# include<algorithm>
using namespace std;
const int INF=10000;
int n=6666;
int a[7000];
int num[2300];
bool vis[7000];
//int p[7000];

int main(){
    srand(time(NULL));
    //freopen("input.txt","r",stdin);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    //for(int i=1;i<=n;i++) p[i]=i;

    int S=0;
    while(1){
            S=0;
            memset(vis,0,sizeof(vis));
    for(int i=1;i<=2016;i++){
        int p=rand()%n+1;
        while(vis[p]){
            p=rand()%n+1;
        }
        vis[p]=1;
        S=S+a[p];
        while(S>=2016) S-=2016;
    }
    if(S==0){
        for(int i=1;i<=n;i++){
            if(vis[i]) printf("%d\n",i);
        }
    break;
    }
    }
    return 0;
}
