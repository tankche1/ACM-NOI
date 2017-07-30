# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=33;
int s[maxn][maxn][maxn];
int a[maxn][maxn];
int n,m;
int p[maxn][maxn];

void read(){
    scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                scanf("%d",&a[i][j]);
            }
        }
}

void prepare(){
    memset(s,0,sizeof(s));
    for(int i=1;i<=m;i++)
        s[1][i][i]=1;

    for(int i=2;i<=n+1;i++){
        for(int j=1;j<=m;j++){
            for(int k=0;k<=m;k++){
                s[i][j][k]=-(s[i-1][j][k]*2+s[i-1][j-1][k]+s[i-1][j+1][k]+s[i-2][j][k]);
            }
            s[i][j][0]-=a[i-1][j];
            //printf("i:%d j:%d ",i,j);
            for(int k=0;k<=m;k++){
                while(s[i][j][k]<0) s[i][j][k]+=3;
                while(s[i][j][k]>=3) s[i][j][k]-=3;

               // printf("%d ",s[i][j][k]);
            }//puts("");
        }
    }

   // puts("****************");

    for(int i=1;i<=m;i++){
        for(int k=1;k<=m;k++){
            p[i][k]=s[n+1][i][k];
        }
        p[i][m+1]=-s[n+1][i][0];
        while(p[i][m+1]<0) p[i][m+1]+=3;

        /*for(int j=1;j<=m+1;j++){
            printf("%d ",p[i][j]);
        }puts("");*/

    }

//puts("****************");
}

int ans[maxn];

void gaoss(){
    int t;
    for(int i=1;i<=m;i++){
        int r=i;
        for(int j=i+1;j<=m;j++){
            if(p[j][i]>p[r][i]) r=j;
        }
        if(r!=i)
            for(int j=i;j<=m+1;j++) swap(p[i][j],p[r][j]);

        if(p[i][i]==0) continue;

        for(int j=i+1;j<=m;j++){
            if(p[j][i]!=0){
                if(p[j][i]-p[i][i]==0) t=1;
                else t=2;
                for(int k=i;k<=m+1;k++){
                    p[j][k]-=t*p[i][k];
                    while(p[j][k]<0) p[j][k]+=3;
                }
            }
        }
    }

    for(int i=m;i>=1;i--){
        if(p[i][i]==0) ans[i]=0;
        else if(p[i][i]==1) ans[i]=p[i][m+1];
        else{
            ans[i]=(3-p[i][m+1])%3;
        }

        for(int j=i-1;j>=1;j--){
            p[j][m+1]-=ans[i]*p[j][i];
            while(p[j][m+1]<0) p[j][m+1]+=3;
        }
    }

}

int print[maxn][maxn];

void solve(){
    memset(print,0,sizeof(print));
    int tot=0,t;
    for(int i=1;i<=m;i++) print[1][i]=ans[i],tot+=ans[i];//,printf("%d ",ans[i]);puts(" ...");
    for(int i=2;i<=n;i++){
                for(int j=1;j<=m;j++){
                    t=(print[i-2][j]+print[i-1][j]*2+print[i-1][j-1]+print[i-1][j+1]+a[i-1][j])%3;
                   //printf("i:%d j:%d t:%d a:%d\n",)
                    print[i][j]=(3-t)%3;
                    tot+=print[i][j];
                }
            }

    printf("%d\n",tot);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            for(int k=1;k<=print[i][j];k++){
                printf("%d %d\n",i,j);
            }
        }
    }
}

int main(){
    int T;
    scanf("%d",&T);
    for(int Tcase=1;Tcase<=T;Tcase++){
        read();
        prepare();
        gaoss();
        solve();
    }
    return 0;
}
