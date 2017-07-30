# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=100010;
int n,k;
int a[maxn];
int sg[maxn];
bool vis[2];
int main(){
    scanf("%d%d",&n,&k);
    sg[0]=0;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=n;j++) vis[j]=0;
        if(i&1) vis[sg[i-1]]=1;
        else{
            if(k%2==0) vis[0]=1;
            else vis[sg[i/2]]=1;
            vis[sg[i-1]]=1;
        }
        for(int j=0;j<=n;j++){
            if(!vis[j]) {sg[i]=j;break;}
        }
         printf("sg[%d]:%d\n",i,sg[i]);
    }
    int ans=0;
    for(int i=1;i<=ans;i++){

    }
    return 0;
}
