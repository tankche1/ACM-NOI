# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
//set<pair<LL,LL> > id;
const int maxn=32;
int a[maxn][maxn];
int s[maxn][maxn];
int three[16];

int main(){
    three[0]=1;
    for(int i=1;i<=15;i++) three[i]=three[i-1]*3;
    int n,m;
    int T;
    scanf("%d",&T);
    int t;
    for(int Tcase=1;Tcase<=T;Tcase++){
        scanf("%d%d",&n,&m);
        memset(s,0,sizeof(s));
        for(int st=0;st<three[m];st++){
            int tmp=st;
            for(int j=1;j<=m;j++){
                s[1][j]=tmp%3;tmp/=3;
            }

            for(int i=2;i<=n;i++){
                for(int j=1;j<=m;j++){
                    t=(s[i-2][j]+s[i-1][j]*2+s[i-1][j-1]+s[i-1][j+1]+a[i][j])%3;
                    s[i][j]=(3-t)%3;
                }
            }

            bool ok=true;
            for(int j=1;j<=m;j++){
                t=(s[n-1][j]+s[n][j]*2+s[n][j-1]+s[n][j+1]+a[n][j])%3;
                if(t!=0) {ok=false;break;}
            }
            if(!ok) continue;

            puts("*************");
            for(int i=1;i<=n;i++){
                for(int j=1;j<=m;j++){
                    printf("%d ",s[i][j]);
                }puts("");
            }
            puts("//////////////");
        }
    }

    return 0;
}
