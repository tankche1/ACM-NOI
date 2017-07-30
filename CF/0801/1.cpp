# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
int a,n,aa;
int b[25];
int c[25];

bool cmp(int a,int b){return a>b;}

bool dfs(int cur,int tot,int last){
    if(cur>tot){
        aa=a;
        for(int i=1;i<=tot;i++)
            aa=aa%c[i];//,printf("c[%d]:%d\n",i,c[i]);puts("fuck");
        return aa==0;
    }
    for(int i=last;i<=n;i++){
        c[cur]=b[i];if(dfs(cur+1,tot,i+1)) return true;
    }
    return false;
}
int main(){
    int tcase,ans;
    scanf("%d",&tcase);
    while(tcase--){
        ans=-1;
        scanf("%d%d",&n,&a);
        for(int i=1;i<=n;i++)
            scanf("%d",&b[i]);
        sort(b+1,b+n+1,cmp);
        for(int i=1;i<=n;i++){
            if(dfs(1,i,1)) {ans=i;break;}
        }
        printf("%d\n",ans);
    }
    return 0;
}
