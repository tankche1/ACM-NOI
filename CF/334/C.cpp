# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=100010;
int n,k;
int a[maxn];
int sg[maxn];
bool vis[200];

int solve(int x){
    if(x<=100) return sg[x];
    if(x%2==1) return 0;
    if(k&1){
        int num=2;
        while(x%2==0){
            x/=2;num=3-num;
        }
        return num;
    }
    else{
        return 1;
    }
}

void prepare(){
    sg[0]=0;
    for(int i=1;i<=100;i++){
        for(int j=0;j<=100;j++) vis[j]=0;
        if(i&1) vis[sg[i-1]]=1;
        else{
            if(k%2==0) vis[0]=1;
            else vis[sg[i/2]]=1;
            vis[sg[i-1]]=1;
        }
        for(int j=0;j<=100;j++){
            if(!vis[j]) {sg[i]=j;break;}
        }
        //if(i%2==0) printf("sg[%d]:%d\n",i,sg[i]);
    }
}

int main(){
    scanf("%d%d",&n,&k);
    prepare();
    int ans=0,x;
    for(int i=1;i<=n;i++){
        scanf("%d",&x);
        ans^=solve(x);
    }
    if(ans>0) printf("Kevin\n");
    else puts("Nicky");
    return 0;
}
