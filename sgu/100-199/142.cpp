# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
const int maxn=500010;
const int maxl=1<<20;
int n;
char s[maxn];
bool vis[maxl];
int two[30];
int main(){
    int now,ans,ansl;
    scanf("%d",&n);
    scanf("%s",s+1);
    two[0]=1;
    for(int i=1;i<=23;i++) two[i]=two[i-1]<<1;
    for(int len=1;;len++){
          //  printf("len:%d\n",len);
        now=0;
        for(int i=1;i<=len;i++){
            now=now*2+s[i]-'a';
        }
        vis[now]=1;
        for(int i=len+1;i<=n;i++){
            now=now&(two[len-1]-1);
            now=(now<<1)+s[i]-'a';
            vis[now]=1;
        }
        for(int i=0;i<two[len];i++){
            if(!vis[i]){
                ans=i;ansl=len;goto loop;
            }
            vis[i]=0;
        }
    }
    loop:
    printf("%d\n",ansl);
    for(int i=1;i<=ansl;i++){
        printf("%c",'a'+((ans>>(ansl-i))&1));
    }
    return 0;
}
