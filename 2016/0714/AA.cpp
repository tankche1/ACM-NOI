# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=1010;
typedef long long LL;
//int mod[3]={999997,1000007,100003};
int n,m,t,p,q;
struct tank{
    unsigned long long hash;
    tank() {hash=0;}
    void init() {hash=0;}
};

bool operator == (tank A,tank B){
    if(A.hash==B.hash) return 1;
    return 0;
}
long long line[maxn][maxn];
int a[maxn][maxn];
int b[maxn][maxn];
tank val[maxn][maxn];
tank pp[110];

bool check(int x,int y){
    //printf("x:%d y:%d\n",x,y);
    for(int i=1;i<=p;i++){
        for(int j=1;j<=q;j++){
            if(b[x+i-1][y+j-1]!=a[i][j]) return false;
        }
    }
    return true;
}

int main(){
    int Tcase=0;
    char tt;
    while(scanf("%d%d%d%d%d",&n,&m,&t,&p,&q)!=EOF){
        if(n==0&&m==0) break;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                while((tt=getchar())&&tt!='0'&&tt!='*');
                a[i][j]=tt=='*';b[i][j]=a[i][j];
            }
        }

        for(int j=1;j<=m;j++){
            long long tmp=0;
            for(int i=n-p+1;i<=n;i++){
                tmp=(tmp<<1)+(a[i][j]);
            }
            line[n-p+1][j]=tmp;
            for(int i=n-p;i>=1;i--){
                line[i][j]=(line[i+1][j]>>1);if(a[i][j]) line[i][j]+=((LL)1<<(p-1));
            }
        }

        for(int i=1;i<=n-p+1;i++){
            for(int j=1;j<=m-q+1;j++){
                val[i][j].init();
                for(int k=1;k<=q;k++){
                        val[i][j].hash<<=p;
                        val[i][j].hash+=line[i][j+k-1];
                    }
                }
            }

        int ans=0;
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
                        pp[l].hash<<=1;//if(pp[l].hash[k]>=mod[k]) pp[l].hash[k]-=mod[k];
                        pp[l].hash+=a[i][j];
                }
            }
           // printf("pp[%d]:%d %d %d\n",l,pp[l].hash[0],pp[l].hash[1],pp[l].hash[2]);
          /* bool ok=0;
            for(int k=1;k<l;k++) if(pp[k]==pp[l]) ok=1;
            if(ok) continue;*/

            for(int i=1;i<=n-p+1;i++){
                for(int j=1;j<=m-q+1;j++){
                      //  printf("i:%d j:%d val:%d\n",i,j,val[i][j].hash[0]);
                    if(val[i][j]==pp[l]){
                      //      printf("i:%d j:%d l:%d\n",i,j,l);
                        if(check(i,j)) ans++;
                    }
                }
            }
        }

        printf("Case %d: %d\n",++Tcase,ans);
    }
    return 0;
}
