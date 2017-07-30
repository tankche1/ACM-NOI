# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=1000100;
int n;
bool vis[10];
int main(){
    //freopen("A-large.in","r",stdin);
   // freopen("output2.txt","w",stdout);
    int tcase;
    scanf("%d",&tcase);
    int T=0,tmp,cnt;
    while(tcase--){
        printf("Case #%d: ",++T);
        scanf("%d",&n);
        if(n==0){
            puts("INSOMNIA");continue;
        }
        memset(vis,0,sizeof(vis));cnt=0;
        for(int x=n;;x+=n){
            tmp=x;
            while(tmp>0){
                if(!vis[tmp%10]) vis[tmp%10]=1,cnt++;
                tmp/=10;
            }
            if(cnt==10) {printf("%d\n",x);break;}
        }
    }
    return 0;
}
