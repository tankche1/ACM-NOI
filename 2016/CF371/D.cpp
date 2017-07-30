# include<stdio.h>
# include<string.h>
# include<iostream>
# include<vector>
# include<bitset>
# include<algorithm>
using namespace std;
const int maxn=1010;
const int Step=10;
int n,m;
int a[maxn][maxn],to[maxn][maxn];
int dp[maxn][maxn][Step+1][Step+1];
int two[1050];

void prepare(){
    memset(to,0,sizeof(to));
    for(int i=n;i>=1;i--){
        for(int j=m;j>=1;j--){
            if(a[i][j]==0) to[i][j]=0;
            else to[i][j]=min(to[i+1][j+1],min(to[i][j+1],to[i+1][j]))+1;
            //printf("to[%d][%d]:%d\n",i,j,to[i][j]);
        }
    }
    for(int x=1;x<=n;x++){
        for(int y=1;y<=m;y++){
            dp[x][y][0][0]=to[x][y];
        }
    }

    for(int i=1;i<Step;i++){
        for(int x=1;x<=n;x++){
            for(int y=1;y<=m;y++){
                dp[x][y][i][0]=dp[x][y][i-1][0];
                if(x+(1<<(i-1))<=n) dp[x][y][i][0]=max(dp[x][y][i][0],dp[x+(1<<(i-1))][y][i-1][0]);
            }
        }
    }

    for(int j=1;j<Step;j++){
        for(int i=0;i<Step;i++){
            for(int x=1;x<=n;x++){
                for(int y=1;y<=m;y++){
                    dp[x][y][i][j]=dp[x][y][i][j-1];
                    if(y+(1<<(j-1))<=m) dp[x][y][i][j]=max(dp[x][y][i][j],dp[x][y+(1<<(j-1))][i][j-1]);

                    //if(i<=2&&j<=2) printf("dp[%d][%d][%d][%d]:%d\n",x,y,i,j,dp[x][y][i][j]);
                }
            }
        }
    }
    two[1]=0;

    /*two[1]=0;
    for(int i=1;i<=10;i++){
        for(int j=(1<<(i-1))+1;j<=(1<<i);j++) {two[j]=i;}
    }*/

    int now=2;
    for(int i=2;i<=1000;i++){
        two[i]=two[i-1];
        if(i>=now) {two[i]=two[i-1]+1;now<<=1;}
        //if(i<=50) printf("two[%d]:%d\n",i,two[i]);
    }
    return;
}

int query(int x1,int y1,int x2,int y2){
    int i=two[x2-x1+1],j=two[y2-y1+1];
    int res=dp[x1][y1][i][j];
    res=max(res,dp[x2-(1<<i)+1][y1][i][j]);
    res=max(res,dp[x1][y2-(1<<j)+1][i][j]);
    res=max(res,dp[x2-(1<<i)+1][y2-(1<<j)+1][i][j]);
    //printf("x1:%d y1:%d x2:%d y2:%d res:%d\n",x1,y1,x2,y2,res);
    return res;
}
int x1,y1,x2,y2;


bool check(int k){
    //printf("k:%d\n",k);
    if(query(x1,y1,x2-k+1,y2-k+1)>=k) return true;
    return false;
}

int main(){
    int Q;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++)
            scanf("%d",&a[i][j]);
    }

    int L,R,M;
    prepare();
    scanf("%d",&Q);
    while(Q--){
        scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
        L=1,R=min(x2-x1+1,y2-y1+1);
        while(L<=R){
            M=(L+R)>>1;
            if(check(M)) L=M+1;
            else R=M-1;
        }
        printf("%d\n",L-1);
    }
    return 0;
}
