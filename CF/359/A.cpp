# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;

int n,m;
int seven[10];
int num_n,num_m;
bool vis[11];
int ans=0;
int a[11];

void dfs(int cur){
    if(cur>num_n+num_m){
        int first=0,second=0;
        for(int i=1;i<=num_n;i++) first=first*7+a[i];
        for(int i=num_n+1;i<=num_n+num_m;i++) second=second*7+a[i];
        if(first<=n&&second<=m) {ans++;//printf("first:%d second:%d\n",first,second);
        }
        return;
    }


    for(int i=0;i<7;i++){
        if(vis[i]) continue;
        a[cur]=i;vis[i]=1;
        dfs(cur+1);
        vis[i]=0;
    }
}

int main(){
    seven[0]=1;
    for(int i=1;i<10;i++) seven[i]=seven[i-1]*7;
    scanf("%d%d",&n,&m);n--;m--;

    int nn=n,mm=m;
    num_n=num_m=0;
    while(nn>0) num_n++,nn/=7;
    while(mm>0) num_m++,mm/=7;

    if(n==0) num_n=1;if(m==0) num_m=1;

    if(num_n+num_m>7){
        puts("0");return 0;
    }

    memset(vis,0,sizeof(vis));ans=0;
    dfs(1);

    printf("%d\n",ans);
    return 0;
}
