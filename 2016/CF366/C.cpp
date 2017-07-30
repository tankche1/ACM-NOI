# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=100010;
const int mod=1000000007;
int x[maxn][3];

vector< pair<int,int> > G[maxn];
vector<int> appear[maxn];
int du[maxn];
bool vis[maxn];
int n,m;

int dp[maxn][2][2];
int a[maxn];

void solve1(int pos){
    int now=1,op,want=abs(x[pos][1]);
    memset(dp[0],0,sizeof(dp[0]));
    for(int j=0;j<2;j++){
        op=0;a[want]=j;
        for(int k=0;k<x[pos][0];k++){
            op=op^a[abs(x[pos][k])];
            if(x[pos][k]<0) op^=1;
        }
        dp[now][op][j]++;
    }


}

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&x[i][0]);
        for(int j=1;j<=x[i][0];j++) {scanf("%d",&x[i][j]);appear[x[i][j]].push_back(i);}
    }

    for(int i=1;i<=m;i++){
        if(appear[i].size()>1) {
            if(appear[i][0]==appear[i][1]) continue;
            G[appear[i][0]].push_back(make_pair(i,appear[i][1])),G[appear[i][1]].push_back(make_pair(i,appear[i][0]));
            du[appear[i][1]]++;du[appear[i][0]]++;
        }
    }

    for(int i=1;i<=n;i++){
        if(du[i]<2&&(!vis[i])) solve1(i);
    }
    return 0;
}
