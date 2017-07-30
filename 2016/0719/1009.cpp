# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=17;
const int mod=1000000007;
typedef long long LL;
int n,m;
int any[maxn][maxn];
int size[maxn],block,last;
LL dp[maxn];
LL g[maxn];

void prepare(){
    any[1][1]=0,any[1][2]=1,any[1][3]=0,any[1][4]=1,any[1][5]=0,any[1][6]=1,any[1][7]=0,any[1][8]=1,any[1][9]=0,any[1][10]=1,any[1][11]=0,any[1][12]=1,any[1][13]=0,any[1][14]=1,any[1][15]=0,any[1][16]=1,any[2][1]=1,any[2][2]=2,any[2][3]=3,any[2][4]=5,any[2][5]=8,any[2][6]=13,any[2][7]=21,any[2][8]=34,any[2][9]=55,any[2][10]=89,any[2][11]=144,any[2][12]=233,any[2][13]=377,any[2][14]=610,any[2][15]=987,any[2][16]=1597,any[3][1]=0,any[3][2]=3,any[3][3]=0,any[3][4]=11,any[3][5]=0,any[3][6]=41,any[3][7]=0,any[3][8]=153,any[3][9]=0,any[3][10]=571,any[3][11]=0,any[3][12]=2131,any[3][13]=0,any[3][14]=7953,any[3][15]=0,any[3][16]=29681,any[4][1]=1,any[4][2]=5,any[4][3]=11,any[4][4]=36,any[4][5]=95,any[4][6]=281,any[4][7]=781,any[4][8]=2245,any[4][9]=6336,any[4][10]=18061,any[4][11]=51205,any[4][12]=145601,any[4][13]=413351,any[4][14]=1174500,any[4][15]=3335651,any[4][16]=9475901,any[5][1]=0,any[5][2]=8,any[5][3]=0,any[5][4]=95,any[5][5]=0,any[5][6]=1183,any[5][7]=0,any[5][8]=14824,any[5][9]=0,any[5][10]=185921,any[5][11]=0,any[5][12]=2332097,any[5][13]=0,any[5][14]=29253160,any[5][15]=0,any[5][16]=366944287,any[6][1]=1,any[6][2]=13,any[6][3]=41,any[6][4]=281,any[6][5]=1183,any[6][6]=6728,any[6][7]=31529,any[6][8]=167089,any[6][9]=817991,any[6][10]=4213133,any[6][11]=21001799,any[6][12]=106912793,any[6][13]=536948224,any[6][14]=720246619,any[6][15]=704300462,any[6][16]=289288426,any[7][1]=0,any[7][2]=21,any[7][3]=0,any[7][4]=781,any[7][5]=0,any[7][6]=31529,any[7][7]=0,any[7][8]=1292697,any[7][9]=0,any[7][10]=53175517,any[7][11]=0,any[7][12]=188978103,any[7][13]=0,any[7][14]=124166811,any[7][15]=0,any[7][16]=708175999,any[8][1]=1,any[8][2]=34,any[8][3]=153,any[8][4]=2245,any[8][5]=14824,any[8][6]=167089,any[8][7]=1292697,any[8][8]=12988816,any[8][9]=108435745,any[8][10]=31151234,any[8][11]=940739768,any[8][12]=741005255,any[8][13]=164248716,any[8][14]=498190405,any[8][15]=200052235,any[8][16]=282756494,any[9][1]=0,any[9][2]=55,any[9][3]=0,any[9][4]=6336,any[9][5]=0,any[9][6]=817991,any[9][7]=0,any[9][8]=108435745,any[9][9]=0,any[9][10]=479521663,any[9][11]=0,any[9][12]=528655152,any[9][13]=0,any[9][14]=764896039,any[9][15]=0,any[9][16]=416579196,any[10][1]=1,any[10][2]=89,any[10][3]=571,any[10][4]=18061,any[10][5]=185921,any[10][6]=4213133,any[10][7]=53175517,any[10][8]=31151234,any[10][9]=479521663,any[10][10]=584044562,any[10][11]=472546535,any[10][12]=732130620,any[10][13]=186229290,any[10][14]=274787842,any[10][15]=732073997,any[10][16]=320338127,any[11][1]=0,any[11][2]=144,any[11][3]=0,any[11][4]=51205,any[11][5]=0,any[11][6]=21001799,any[11][7]=0,any[11][8]=940739768,any[11][9]=0,any[11][10]=472546535,any[11][11]=0,any[11][12]=177126748,any[11][13]=0,any[11][14]=513673802,any[11][15]=0,any[11][16]=881924366,any[12][1]=1,any[12][2]=233,any[12][3]=2131,any[12][4]=145601,any[12][5]=2332097,any[12][6]=106912793,any[12][7]=188978103,any[12][8]=741005255,any[12][9]=528655152,any[12][10]=732130620,any[12][11]=177126748,any[12][12]=150536661,any[12][13]=389322891,any[12][14]=371114062,any[12][15]=65334618,any[12][16]=119004311,any[13][1]=0,any[13][2]=377,any[13][3]=0,any[13][4]=413351,any[13][5]=0,any[13][6]=536948224,any[13][7]=0,any[13][8]=164248716,any[13][9]=0,any[13][10]=186229290,any[13][11]=0,any[13][12]=389322891,any[13][13]=0,any[13][14]=351258337,any[13][15]=0,any[13][16]=144590622,any[14][1]=1,any[14][2]=610,any[14][3]=7953,any[14][4]=1174500,any[14][5]=29253160,any[14][6]=720246619,any[14][7]=124166811,any[14][8]=498190405,any[14][9]=764896039,any[14][10]=274787842,any[14][11]=513673802,any[14][12]=371114062,any[14][13]=351258337,any[14][14]=722065660,any[14][15]=236847118,any[14][16]=451896972,any[15][1]=0,any[15][2]=987,any[15][3]=0,any[15][4]=3335651,any[15][5]=0,any[15][6]=704300462,any[15][7]=0,any[15][8]=200052235,any[15][9]=0,any[15][10]=732073997,any[15][11]=0,any[15][12]=65334618,any[15][13]=0,any[15][14]=236847118,any[15][15]=0,any[15][16]=974417347,any[16][1]=1,any[16][2]=1597,any[16][3]=29681,any[16][4]=9475901,any[16][5]=366944287,any[16][6]=289288426,any[16][7]=708175999,any[16][8]=282756494,any[16][9]=416579196,any[16][10]=320338127,any[16][11]=881924366,any[16][12]=119004311,any[16][13]=144590622,any[16][14]=451896972,any[16][15]=974417347,any[16][16]=378503901;
}

int main(){
    //freopen("output2.txt","w",stdout);
    prepare();
    //for(n=1;n<=16;n++){
     //   for(m=1;m<=16;m++){
    while(scanf("%d%d",&n,&m)!=EOF){
    LL ans=0;
    for(int st=1<<(m-1);st<(1<<m);st++){
        block=0;last=0;
        for(int i=1;i<=m;i++){
            if((st>>(i-1))&1){
                size[++block]=i-last;last=i;
            }
        }
        for(int i=1;i<=n;i++){
            g[i]=1;
            for(int j=1;j<=block;j++) g[i]=g[i]*any[i][size[j]]%mod;
        }

        for(int i=1;i<=n;i++){
            dp[i]=g[i];
            for(int k=1;k<i;k++) dp[i]-=dp[k]*g[i-k]%mod;
            dp[i]=dp[i]%mod;if(dp[i]<0) dp[i]+=mod;
        }

        if(block&1) ans+=dp[n];
        else ans-=dp[n];
    }
    ans=((ans%mod)+mod)%mod;
    //printf("ans[%d][%d]:%I64d\n",n,m,ans);
    printf("%I64d\n",ans);
    }
    return 0;
}
