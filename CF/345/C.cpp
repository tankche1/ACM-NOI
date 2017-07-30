# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=1000010;
int n,m,tot;
int a[maxn];

int pos(int x,int y){
    return (x-1)*m+y;
}

int bh[maxn];
int dp[maxn];
int b[maxn];

bool cmp(int c,int d){
    return a[c]>a[d];
}

bool cmp2(int c,int d){
    return dp[c]>dp[d];
}

int row[maxn],line[maxn];

int main(){
    int x,y,p,ans=0;
    scanf("%d%d",&n,&m);tot=n*m;
    for(int i=1;i<=tot;i++)
        scanf("%d",&a[i]),bh[i]=i;
    for(int i=1;i<=n;i++) row[i]=0;
    for(int j=1;j<=m;j++) line[j]=0;

    sort(bh+1,bh+tot+1,cmp);
    int j;
    for(int i=1;i<=tot;i++){
        j=i;
        while(j<tot&&a[bh[j+1]]==a[bh[j]]) j++;
        for(int k=i;k<=j;k++){
            p=bh[k];dp[p]=1;
            x=(bh[k]-1)/m+1;y=bh[k]-(x-1)*m;
            dp[p]=max(dp[p],row[x]+1);
            dp[p]=max(dp[p],line[y]+1);
        }

        sort(bh+i,bh+j+1,cmp2);

        for(int k=i;k<=j;k++){
            p=bh[k];
            x=(bh[k]-1)/m+1;y=bh[k]-(x-1)*m;
            dp[p]=max(dp[p],row[x]);
            dp[p]=max(dp[p],line[y]);
            row[x]=max(row[x],dp[p]);
            line[y]=max(line[y],dp[p]);
        }

        for(int k=i;k<=j;k++){
            p=bh[k];
            x=(bh[k]-1)/m+1;y=bh[k]-(x-1)*m;
            ans=max(ans,dp[p]);//,printf("x:%d y:%d dp:%d\n",x,y,dp[bh[k]]);
        }
        i=j;
       // printf("dp:%d\n",dp[p]);
    }

    //printf("ans:%d\n",ans);
    for(int i=1;i<=tot;i++){
        b[i]=ans-dp[i]+1;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(j>1) printf(" ");
            printf("%d",b[pos(i,j)]);
        }puts("");
    }
    return 0;
}
