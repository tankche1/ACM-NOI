# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
int n,m,k;
int c[30];
int a[6][6];

bool dfs(int x,int y,int cur){
    int _max=0;
    for(int i=1;i<=k;i++) _max=max(_max,c[i]);
    if((n*m-cur+1+1)/2<_max) return false;

    if(y>m) x++,y=1;
    if(x>n) return true;

    for(int i=1;i<=k;i++){
        if(c[i]==0) continue;
        if(a[x-1][y]==i||a[x][y-1]==i) continue;
        a[x][y]=i;
        c[i]--;
        if(dfs(x,y+1,cur+1)) return true;
        c[i]++;
    }
    return false;
}
int main(){
    int T;
    scanf("%d",&T);
    memset(a,0,sizeof(a));
    for(int Tcase=1;Tcase<=T;Tcase++){
        scanf("%d%d%d",&n,&m,&k);
        for(int i=1;i<=k;i++)
            scanf("%d",&c[i]);
        bool ok=dfs(1,1,1);

        printf("Case #%d:\n",Tcase);
        if(ok){
            puts("YES");
            for(int i=1;i<=n;i++){
                for(int j=1;j<=m;j++){
                    printf("%d",a[i][j]);
                    if(j<m) printf(" ");
                }puts("");
            }
        }
        else puts("NO");
    }
    return 0;
}
