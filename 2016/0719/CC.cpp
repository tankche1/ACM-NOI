# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=1010;
int n,m;


int blockx[maxn],blocky[maxn];
int sum[maxn];
char s[maxn];

int main(){
    //freopen("1003.in","r",stdin);
    //freopen("output.txt","w",stdout);
    int T,num;
    char tt;
    scanf("%d",&T);
    //memset(f,0,sizeof(f));memset(g,0,sizeof(g));
    sum[0]=0;
    for(int i=1;i<=1000;i++) sum[i]=sum[i-1]+i;

    for(int Tcase=1;Tcase<=T;Tcase++){
        scanf("%d%d",&n,&m);num=n*m;
        memset(blockx,0,sizeof(blockx));memset(blocky,0,sizeof(blocky));

        for(int i=1;i<=n;i++){
            scanf("%s",s+1);
            for(int j=1;j<=m;j++){
                if(s[j]=='G') blockx[i]=j,blocky[j]=i,num--;
            }
        }

        /*for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                while((tt=getchar())&&tt!='#'&&tt!='G');
                if(tt=='G'){
                    blockx[i]=j;blocky[j]=i;num--;
                }
            }
        }*/

        LL tot=0,now=0;

        for(int i=1;i<n;i++){
            now+=m;if(blockx[i]!=0) now--;
            tot+=now*(num-now);
        }

        now=0;
        for(int j=1;j<m;j++){
            now+=n;if(blocky[j]!=0) now--;
            tot+=now*(num-now);
        }

        tot<<=1;

        LL res;
        for(int i=n;i>=1;i--){
            if(blockx[i]==0) {res=0;continue;}
            if(i==n||blockx[i]>blockx[i+1]) res=0;
            res+=m-blockx[i];

            tot+=(blockx[i]-1)*res*2*2;
        }

        for(int i=1;i<=n;i++){
            if(blockx[i]==0) {res=0;continue;}
            if(i==1||blockx[i]>blockx[i-1]) res=0;

            tot+=(blockx[i]-1)*res*2*2;
            res+=m-blockx[i];


        }

        for(int j=m;j>=1;j--){
            if(blocky[j]==0) {res=0;continue;}
            if(j==m||blocky[j]>blocky[j+1]) res=0;
            res+=n-blocky[j];

            tot+=(blocky[j]-1)*res*2*2;
        }

        for(int j=1;j<=m;j++){
            if(blocky[j]==0) {res=0;continue;}
            if(j==1||blocky[j]>blocky[j-1]) res=0;

            tot+=(blocky[j]-1)*res*4;
            res+=n-blocky[j];

        }

       // printf("tot:%I64d\n",tot);
        double ans=tot/((double)num*num*1.0);
        printf("%.4lf\n",ans);
        /*if(fabs(ans-13.6754)<0.1){
            printf("%d %d\n",n,m);

        }*/
    }
    return 0;
}
