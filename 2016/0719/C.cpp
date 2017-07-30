# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=1010;
int n,m;

int f[maxn][maxn],g[maxn][maxn];

int blockx[maxn],blocky[maxn];
int sum[maxn];

char s[maxn];

int main(){
    //freopen("1003.in","r",stdin);
    //freoen("output.txt","w",stdout);
    int T,num;
    char tt;
    scanf("%d",&T);
    //memset(f,0,sizeof(f));memset(g,0,sizeof(g));
    sum[0]=0;
    for(int i=1;i<=1000;i++) sum[i]=sum[i-1]+i;

    for(int Tcase=1;Tcase<=T;Tcase++){
        scanf("%d%d",&n,&m);num=n*m;
        memset(blockx,0,sizeof(blockx));memset(blocky,0,sizeof(blocky));
        for(int i=0;i<=n+1;i++) for(int j=0;j<=m+1;j++) f[i][j]=g[i][j]=0;
        for(int i=1;i<=n;i++){
            scanf("%s",s+1);
            for(int j=1;j<=m;j++){
                if(s[j]=='G') blockx[i]=j,blocky[j]=i,num--;
            }
        }

        LL tot=0;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                f[i][j]=f[i][j-1]+f[i-1][j]-f[i-1][j-1]+(blockx[i]!=j);
                g[i][j]=g[i][j-1]+g[i-1][j]-g[i-1][j-1];if(blockx[i]!=j) g[i][j]+=i+j;
                if(blockx[i]!=j) tot+=(i+j)*f[i-1][j-1]-g[i-1][j-1];
                //printf("i:%d j:%d f:%d g:%d\n",i,j,f[i][j],g[i][j]);
            }
        }
        //printf("tot:%I64d\n",tot);

        for(int i=n;i>=1;i--){
            for(int j=1;j<=m;j++){
                f[i][j]=f[i+1][j]+f[i][j-1]-f[i+1][j-1]+(blockx[i]!=j);
                g[i][j]=g[i+1][j]+g[i][j-1]-g[i+1][j-1];if(blockx[i]!=j) g[i][j]+=j-i;
                if(blockx[i]!=j) tot+=f[i+1][j-1]*(j-i)-g[i+1][j-1];
                //printf("i:%d j:%d f:%d g:%d\n",i,j,f[i][j],g[i][j]);
            }
        }

        tot*=2; //printf("tot:%I64d\n",tot);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(blockx[i]==j) continue;
                else if(blockx[i]>j){
                    tot+=2*(sum[m-j]-(blockx[i]-j));
                }
                else tot+=2*sum[m-j];

                if(blocky[j]>i){
                    tot+=2*(sum[n-i]-(blocky[j]-i));
                }
                else tot+=2*sum[n-i];
            }
        }

        //printf("tot:%I64d\n",tot);
        LL res1,res2;int pos;

        for(int i=1;i<=n;i++){
            if(blockx[i]==0) continue;
            res1=blockx[i]-1;res2=m-blockx[i];pos=i;
            while(pos<n&&blockx[pos+1]>blockx[pos]) res2+=m-blockx[pos+1],pos++;
            pos=i;
            while(pos>1&&blockx[pos-1]>blockx[pos]) res2+=m-blockx[pos-1],pos--;
            tot+=res1*res2*2*2;
        }

        for(int j=1;j<=m;j++){
            if(blocky[j]==0) continue;
            res1=blocky[j]-1;res2=n-blocky[j];pos=j;
            while(pos<m&&blocky[pos+1]>blocky[pos]) res2+=n-blocky[pos+1],pos++;

            pos=j;
            while(pos>1&&blocky[pos-1]>blocky[pos]) res2+=n-blocky[pos-1],pos--;
            tot+=res1*res2*2*2;
        }

        //printf("tot:%I64d\n",tot);
        double ans=tot/((double)num*num*1.0);
        printf("%.4lf\n",ans);
    }
    return 0;
}
