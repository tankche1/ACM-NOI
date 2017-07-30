# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
typedef long long LL;
bool a[210][210];
int n;
LL p[210][210],sum[210][210];
LL px[210][210],py[210][210];
int R[210][210],U[210][210];

int t[210][210];//a=i b<=j
LL tank[210][210];//a>=i b<=j

int gcd(int a,int b){
    return b==0?a:gcd(b,a%b);
}

void prepare(){
    for(int i=1;i<=200;i++){
        t[i][0]=0;
        for(int j=1;j<=200;j++){
            t[i][j]=t[i][j-1];
            if(gcd(i,j)==1) t[i][j]++;
        }
    }

    for(int i=200;i>=0;i--){
        for(int j=200;j>=1;j--){
            tank[i][j]=tank[i+1][j]+t[i][j];
        }
    }
}

int main(){
//freopen("input.txt","r",stdin);
    int T;
    int x,y;;
    scanf("%d",&T);
    prepare();
    for(int Tcase=1;Tcase<=T;Tcase++){
        memset(a,0,sizeof(a));
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d%d",&x,&y);
            a[x][y]=1;
        }

        for(int i=200;i>=1;i--){
            for(int j=200;j>=1;j--){
                U[i][j]=a[i][j]==0?0:U[i][j+1]+1;
                R[i][j]=a[i][j]==0?0:R[i+1][j]+1;
            }
        }
        LL ans1=0,ans2=0;
        for(int i=200;i>=1;i--){
            for(int j=200;j>=1;j--){
                p[i][j]=0;
                if(!a[i][j]) p[i][j]=0;
                else{
                    for(int aa=1;aa<=R[i][j]-1;aa++){
                        p[i][j]+=t[aa][U[i][j]-1];
                    }
                }
                px[i][j]=px[i][j+1]+p[i][j];
                py[i][j]=py[i+1][j]+p[i][j];
                sum[i][j]=sum[i+1][j+1]+px[i][j]+py[i][j]-p[i][j];
                ans2+=p[i][j]*p[i][j];
                //if(p[i][j]>0) printf("p[%d][%d]:%d\n",i,j,p[i][j]);
            }
        }
        ans1=sum[1][1]*sum[1][1];

        //printf("ans2:%I64d\n",ans2);

        LL tmp=0;

        for(int i=200;i>=1;i--){
            for(int j=200;j>=1;j--){
                tmp=0;
                for(int aa=1;aa<=R[i][j]-1;aa++){
                    //ans2+=(py[i+1][j]-py[i+aa+1][j])*t[aa][U[i][j]-1];
                    tmp+=(py[i+1][j]-py[i+aa+1][j])*t[aa][U[i][j]-1];
                }
                for(int bb=1;bb<=U[i][j]-1;bb++){
                    //ans2+=(px[i][j+1]-px[i][j+bb+1])*t[bb][R[i][j]-1];
                    tmp+=(px[i][j+1]-px[i][j+bb+1])*t[bb][R[i][j]-1];
                }
                ans2+=tmp*2;
                //if(tmp>0) printf("i:%d j:%d tmp:%I64d\n",i,j,tmp);
            }
        }

        //printf("ans2:%I64d\n",ans2);


        LL res1,res2;
        for(int i=200;i>=1;i--){
            for(int j=200;j>=1;j--){
                if(a[i][j]==0) continue;
                res1=0;res2=0;
                for(int aa=1;a[i-aa][j]==1;aa++){
                    res1+=-tank[R[i-aa][j]][U[i-aa][j]-1]+tank[aa][U[i-aa][j]-1];
                }

                for(int bb=1;a[i][j-bb]==1;bb++){
                    res2+=tank[bb][R[i][j-bb]-1]-tank[U[i][j-bb]][R[i][j-bb]-1];
                }
                ans2+=res1*res2*2;
            }
        }

        LL ans=ans1-ans2;
        printf("Case #%d: ",Tcase);
        printf("%I64d\n",ans);

        //printf("ans1:%I64d ans2:%I64d\n",ans1,ans2);

    }
    return 0;
}
