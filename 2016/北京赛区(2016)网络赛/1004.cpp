# include<stdio.h>
# include<string.h>
# include<iostream>
# include<vector>
# include<bitset>
# include<algorithm>
using namespace std;
const int maxn=510;
const int INF=1000000000;
typedef long long LL;
int n,Limit;
char op[20];
int dp[12][2][6][6][4][1010],dp_num[12][2][6][6][4][1010];

struct player{
    int type,val,cost;
    player() {}
}p[maxn];

bool cmp(player a,player b){
    return a.val<b.val;
}
int cnt[4]={1,5,5,3};

void normal(int &x){
    if(x>INF) x=INF;
}

int ans,_cost,tot;

void solve(){
    int t[4],tmp,res;
    //
    //memset(dp,-1,sizeof(dp));
    for(int num=11;num>=0;num--){
            for(t[0]=0;t[0]<2;t[0]++){
                for(t[1]=0;t[1]<6;t[1]++){
                    for(t[3]=0;t[3]<4;t[3]++){
                          //  printf("num:%d %d %d %d\n",num,t[0],t[1],t[3]);
                        t[2]=num-t[0]-t[1]-t[3];if(t[2]>cnt[2]||t[2]<0) continue;
                        for(int j=0;j<=Limit;j++) dp[num][t[0]][t[1]][t[2]][t[3]][j]=-1,dp_num[num][t[0]][t[1]][t[2]][t[3]][j]=0;
                    }
                }
            }
    }
    dp[0][0][0][0][0][0]=0;dp_num[0][0][0][0][0][0]=1;


    for(int i=1;i<=n;i++){
        for(int num=10;num>=0;num--){
            for(t[0]=0;t[0]<2;t[0]++){
                for(t[1]=0;t[1]<6;t[1]++){
                for(t[3]=0;t[3]<4;t[3]++){
                            t[2]=num-t[0]-t[1]-t[3];if(t[2]>cnt[2]||t[2]<0) continue;
                            for(int j=0;j+p[i].cost<=Limit;j++){
                                if(dp[num][t[0]][t[1]][t[2]][t[3]][j]==-1) continue;
                                if(t[p[i].type]+1>cnt[p[i].type]) continue;
                                tmp=dp[num][t[0]][t[1]][t[2]][t[3]][j];res=dp_num[num][t[0]][t[1]][t[2]][t[3]][j];
                                t[p[i].type]++;
                                if(num!=10){
                                    if(dp[num+1][t[0]][t[1]][t[2]][t[3]][j+p[i].cost]<tmp+p[i].val){
                                        dp[num+1][t[0]][t[1]][t[2]][t[3]][j+p[i].cost]=tmp+p[i].val;
                                        dp_num[num+1][t[0]][t[1]][t[2]][t[3]][j+p[i].cost]=res;
                                    }
                                    else if(dp[num+1][t[0]][t[1]][t[2]][t[3]][j+p[i].cost]==tmp+p[i].val){
                                        dp_num[num+1][t[0]][t[1]][t[2]][t[3]][j+p[i].cost]+=res;
                                        normal(dp_num[num+1][t[0]][t[1]][t[2]][t[3]][j+p[i].cost]);
                                    }
                                }
                                else{
                                    if(dp[num+1][t[0]][t[1]][t[2]][t[3]][j+p[i].cost]<tmp+p[i].val*2){
                                        dp[num+1][t[0]][t[1]][t[2]][t[3]][j+p[i].cost]=tmp+p[i].val*2;
                                        dp_num[num+1][t[0]][t[1]][t[2]][t[3]][j+p[i].cost]=res;
                                    }
                                    else if(dp[num+1][t[0]][t[1]][t[2]][t[3]][j+p[i].cost]==tmp+p[i].val*2){
                                        dp_num[num+1][t[0]][t[1]][t[2]][t[3]][j+p[i].cost]+=res;
                                        normal(dp_num[num+1][t[0]][t[1]][t[2]][t[3]][j+p[i].cost]);
                                    }
                                }
                                t[p[i].type]--;
                                //if(i<=3&&num<=3) printf("dp[%d][%d][%d][%d][%d][%d]:%d\n",num,t[0],t[1],t[2],t[3],j,dp[num][t[0]][t[1]][t[2]][t[3]][j]);
                            }

                    }
                }
            }
        }
    }

    ans=0;_cost=0;tot=0;
    for(t[0]=1;t[0]<2;t[0]++){
        for(t[1]=3;t[1]<6;t[1]++){
            for(t[2]=2;t[2]<6;t[2]++){
                for(t[3]=1;t[3]<4;t[3]++){
                    if(t[0]+t[1]+t[2]+t[3]==11){
                        for(int j=0;j<=Limit;j++){
                            if(dp[11][t[0]][t[1]][t[2]][t[3]][j]>ans||(dp[11][t[0]][t[1]][t[2]][t[3]][j]==ans&&_cost>j)){
                                ans=dp[11][t[0]][t[1]][t[2]][t[3]][j];_cost=j;tot=dp_num[11][t[0]][t[1]][t[2]][t[3]][j];
                            }
                            else if(dp[11][t[0]][t[1]][t[2]][t[3]][j]==ans&&_cost==j){
                                tot+=dp_num[11][t[0]][t[1]][t[2]][t[3]][j];
                                normal(tot);
                            }
                        }
                    }
                }
            }
        }
    }
    printf("%d %d %d\n",ans,_cost,tot);
}

int main(){

   // freopen("in.txt","r",stdin);
    int Case;
    scanf("%d",&Case);
    for(int Tcase=1;Tcase<=Case;Tcase++){
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%s",op);
            if(op[0]=='G') p[i].type=0;
            else if(op[0]=='D') p[i].type=1;
            else if(op[0]=='M') p[i].type=2;
            else p[i].type=3;
            scanf("%d%d",&p[i].val,&p[i].cost);
        }
        scanf("%d",&Limit);
        sort(p+1,p+n+1,cmp);

        solve();
    }
    return 0;
}
