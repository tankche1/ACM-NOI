# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
int tcase,n;
const int maxn=60;
int A[maxn<<1][maxn];
int bh[maxn][2];
int go[maxn][2];

bool check(int x){
    //printf("check:%d\n",x);
    if(bh[x][0]==2*n||bh[x][1]==2*n){
        //puts("fuck");
        int d=(bh[x][1]!=2*n);
        for(int i=1;i<=n;i++){
            if(i==x) {A[2*n][i]=A[bh[x][d]][i];continue;}
            if(A[bh[i][0]][x]==A[bh[x][d]][i]) A[2*n][i]=A[bh[i][1]][x];
            else A[2*n][i]=A[bh[i][0]][x];
        }
        return true;
    }
    else{
        for(int i=1;i<=n;i++){
            if(i==x) continue;
            if(A[go[x][0]][i]!=A[go[x][1]][i]){
                if(go[i][0]!=-1) continue;
                if(A[bh[i][1]][x]==A[go[x][0]][i]) go[i][1]=bh[i][1],go[i][0]=bh[i][0];
                else go[i][1]=bh[i][0],go[i][0]=bh[i][1];
                if(check(i)) return true;
            }
        }
    }
    return false;
}

void print(){
    for(int i=1;i<=n;i++){
        printf("%d",A[2*n][i]);if(i) printf(" ");
    }puts("");
}

bool vis[maxn<<1];

int main(){
       // freopen("B-large.in","r",stdin);
    //freopen("output.txt","w",stdout);
    scanf("%d",&tcase);
    for(int Tcase=1;Tcase<=tcase;Tcase++){
        scanf("%d",&n);
        for(int i=1;i<n+n;i++){
            for(int j=1;j<=n;j++)
                scanf("%d",&A[i][j]);
        }

        printf("Case #%d: ",Tcase);

        memset(vis,0,sizeof(vis));
        for(int i=1;i<=n;i++){
            int _min=3000;
            for(int j=1;j<n+n;j++){
                if(vis[j]) continue;
                _min=min(_min,A[j][i]);
            }
            int now=0;
            for(int j=1;j<n+n;j++){
                if(A[j][i]==_min&&(!vis[j])) bh[i][now++]=j,vis[j]=1;
            }
            if(now==1) bh[i][now++]=2*n;
            //printf("i:%d 0:%d 1:%d\n",i,bh[i][0],bh[i][1]);
        }

        memset(go,-1,sizeof(go));
        go[1][0]=bh[1][0];go[1][1]=bh[1][1];
        if(check(1)) {print();continue;}
        for(int i=1;i<=n;i++){
            if(go[i][0]==-1){
                go[i][0]=bh[i][0];go[i][1]=bh[i][1];if(check(i)) {print();break;}
            }
        }
    }

    return 0;
}
