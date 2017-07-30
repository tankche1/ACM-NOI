# include<stdio.h>
# include<string.h>
# include<vector>
# include<bitset>
# include<algorithm>
using namespace std;
const int maxn=52;
int n,A[maxn];
int Q;
bitset<90> dp[12];
int ans[maxn][maxn][maxn];

bool solve(int a,int b,int c){
    if(ans[a][b][c]!=-1) return ans[a][b][c];
    //dp[0].reset();dp[0][0]=1;
    //for(int i=0;i<=10;i++) dp[i].reset();dp[0][0]=1;
    memset(dp,0,sizeof(dp));dp[0][0]=1;
    for(int i=1;i<=n;i++){
        if(i==a||i==b||i==c) continue;
        for(int num=9;num>=0;num--){
            if(A[i]<=87)
                dp[num+1]|=(dp[num]<<A[i]);
        }
    }
    return ans[a][b][c]=dp[10][87];
}

bool f[51][11][90];
int B[11];

void print(int i,int num,int k){
    if(num==0) return;
    while(f[i-1][num][k]) i--;
    B[num]=i;
    print(i-1,num-1,k-A[i]);
}
bool prepare(){
    memset(f,0,sizeof(f));f[0][0][0]=1;
    for(int i=0;i<n;i++){
        for(int num=10;num>=0;num--){
            for(int k=87;k>=0;k--){
                if(f[i][num][k]==0) continue;
                //if(i>=10&&num>=9) printf("%d %d %d\n",i,num,k);
                if(k+A[i]<=87) f[i+1][num+1][k+A[i]]=1;
                f[i+1][num][k]=1;
            }
        }
    }

    if(!f[n][10][87]) return false;

    print(n,10,87);

    for(int a=1;a<=50;a++){
        for(int b=a;b<=50;b++){
            for(int c=b;c<=50;c++){
                ans[a][b][c]=1;
                for(int k=1;k<=10;k++) if(B[k]==a||B[k]==b||B[k]==c) {ans[a][b][c]=-1;break;}
            }
        }
    }
    return true;
}

void read(int &x){
    int ch;
    while (!isdigit(ch = getchar()));
    x = ch - '0';
    while (isdigit(ch = getchar()))
        x = x * 10 + ch - '0';
}

int main(){
    int Case;
    int a,b,c;
    int tank[4];
    bool ok;
    bool flag;
    read(Case);
    for(int Tcase=1;Tcase<=Case;Tcase++){
        //scanf("%d",&n);
        read(n);
        for(int i=1;i<=n;i++) read(A[i]);
        memset(ans,-1,sizeof(ans));
        flag=prepare();//printf("flag:%d\n",flag);
        if(!flag){
            read(Q);for(int i=1;i<=Q;i++){read(a);read(b);read(c);puts("No");}continue;
        }
        read(Q);
        for(int i=1;i<=Q;i++){
            //scanf("%d%d%d",&a,&b,&c);
            read(tank[0]);read(tank[1]);read(tank[2]);
            sort(tank,tank+3);
            ok=solve(tank[0],tank[1],tank[2]);
            if(ok) puts("Yes");
            else puts("No");
        }

    }
    return 0;
}
