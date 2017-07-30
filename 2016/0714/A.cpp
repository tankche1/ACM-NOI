# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=1010;
typedef long long LL;
int mod[3]={999997,1000007,100003};
int n,m,t,p,q;
struct tank{
    int hash[3];
    tank() {hash[0]=hash[1]=hash[2]=0;}
    void init() {hash[0]=hash[1]=hash[2]=0;}
};

bool operator == (tank A,tank B){
    if(A.hash[0]==B.hash[0]&&A.hash[1]==B.hash[1]&&A.hash[2]==B.hash[2]) return 1;
    return 0;
}
long long line[maxn][maxn];
int a[maxn][maxn];
tank val[maxn][maxn];
tank pp[110];

int main(){
    int Tcase=0;
    char tt;
    while(scanf("%d%d%d%d%d",&n,&m,&t,&p,&q)!=EOF){
        if(n==0&&m==0) break;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                while((tt=getchar())&&tt!='0'&&tt!='*');
                a[i][j]=tt=='*';
            }
        }

        //memset(line,0,sizeof(line));
        for(int j=1;j<=m;j++){
            long long tmp=0;
            for(int i=n-p+1;i<=n;i++){
                tmp=(tmp<<1)+(a[i][j]);
            }
            line[n-p+1][j]=tmp;
            for(int i=n-p;i>=1;i--){
                line[i][j]=(line[i+1][j]>>1);if(a[i][j]) line[i][j]+=((LL)1<<(p-1));
               // printf("line[%d][%d]:%I64d\n",i,j,line[i][j]);
            }
        }
        long long test[3];test[0]=((LL)1<<p)%mod[0];test[1]=((LL)1<<p)%mod[1];test[2]=((LL)1<<p)%mod[2];

        for(int i=1;i<=n-p+1;i++){
            for(int j=1;j<=m-q+1;j++){
                val[i][j].init();
                for(int k=1;k<=q;k++){
                    for(int l=0;l<3;l++){
                        val[i][j].hash[l]=val[i][j].hash[l]*test[l];
                        if(val[i][j].hash[l]>=mod[l]) val[i][j].hash[l]%=mod[l];
                        val[i][j].hash[l]+=line[i][j+k-1];
                    }
                }
            }
        }

        for(int l=1;l<=t;l++){
            for(int i=1;i<=p;i++){
                for(int j=1;j<=q;j++){
                    while((tt=getchar())&&tt!='0'&&tt!='*');
                    a[i][j]=tt=='*';
                }
            }

            pp[l].init();
            for(int j=1;j<=q;j++){
                for(int i=1;i<=p;i++){
                    for(int k=0;k<3;k++){
                        pp[l].hash[k]=pp[l].hash[k]*2;if(pp[l].hash[k]>=mod[k]) pp[l].hash[k]-=mod[k];
                        pp[l].hash[k]+=a[i][j];
                    }
                }
            }
           // printf("pp[%d]:%d %d %d\n",l,pp[l].hash[0],pp[l].hash[1],pp[l].hash[2]);
        }

        int ans=0;
        for(int l=1;l<=t;l++){
            bool ok=0;
            for(int k=1;k<l;k++) if(pp[k]==pp[l]) ok=1;
            if(ok) continue;

            for(int i=1;i<=n-p+1;i++){
                for(int j=1;j<=m-q+1;j++){
                      //  printf("i:%d j:%d val:%d\n",i,j,val[i][j].hash[0]);
                    if(val[i][j]==pp[l]){
                      //      printf("i:%d j:%d l:%d\n",i,j,l);
                        ans++;
                    }
                }
            }
        }
        printf("Case %d: %d\n",++Tcase,ans);
    }
    return 0;
}
