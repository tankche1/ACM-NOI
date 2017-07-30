# include<stdio.h>
# include<string.h>
# include<vector>
# include<set>
# include<algorithm>
using namespace std;
const int maxn=32;
typedef long long LL;
set<pair<LL,LL> > id;
int a[maxn][maxn];
int s[maxn][maxn];
int three[16];

int n,m,pos;

int needs[maxn],needa[maxn];

void print(){
    int t;
    for(int j=pos-1;j>=1;j--){
        for(int i=1;i<=n;i++){
            t=(s[i][j+1]*2+a[i][j+1]+s[i-1][j+1]+s[i+1][j+1]+s[i][j+2])%3;
            s[i][j]=(3-t)%3;
        }
    }

    for(int j=pos+2;j<=m;j++){
        for(int i=1;i<=n;i++){
            t=(s[i][j-1]*2+a[i][j-1]+s[i-1][j-1]+s[i+1][j-1]+s[i][j-2])%3;
            s[i][j]=(3-t)%3;
        }
    }

    int tot=0;
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) tot+=s[i][j];

    printf("%d\n",tot);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            for(int k=1;k<=s[i][j];k++)
                printf("%d %d\n",i,j);
        }
    }
}

void solve(){
    memset(s,0,sizeof(s));
    pos=m/2;int t;
    id.clear();
    for(int st=0;st<three[pos];st++){
        int tmp=st;
        for(int j=1;j<=pos;j++){
            s[1][j]=tmp%3;tmp/=3;
        }

        for(int i=2;i<=n;i++){
            for(int j=1;j<=pos;j++){
                t=(s[i-2][j]+s[i-1][j]*2+s[i-1][j-1]+s[i-1][j+1]+a[i-1][j])%3;
                s[i][j]=(3-t)%3;
            }
        }

        bool ok=true;
        for(int j=1;j<pos;j++){
            t=(s[n-1][j]+s[n][j]*2+s[n][j-1]+s[n][j+1]+a[n][j])%3;
            if(t!=0) {ok=false;break;}
        }
        if(!ok) continue;

        LL code=0;
        for(int i=1;i<=n;i++){
            code*=3;
            code=code+s[i][pos];
        }

        LL code2=0;
        for(int i=1;i<=n;i++){
            code2*=3;
            t=(a[i][pos]+s[i-1][pos]+s[i][pos]*2+s[i][pos-1]+s[i+1][pos])%3;
            code2=code2+t;
        }

        id.insert(make_pair(code,code2));

        puts("***********");
        for(int i=1;i<=n;i++){
            for(int j=1;j<=pos;j++){
                printf("%d ",s[i][j]);
            }puts("");
        }
        puts("***********");
    }

    memset(s,0,sizeof(s));

    for(int st=0;st<three[m-pos];st++){
        int tmp=st;
        for(int j=pos+1;j<=m;j++){
            s[1][j]=tmp%3;
            tmp/=3;
        }

        for(int i=2;i<=n;i++){
            for(int j=pos+1;j<=m;j++){
                t=(s[i-2][j]+s[i-1][j]*2+s[i-1][j-1]+s[i-1][j+1]+a[i-1][j])%3;
                s[i][j]=(3-t)%3;
            }
        }

        bool ok=true;
        for(int j=pos+2;j<=m;j++){
            t=(s[n-1][j]+s[n][j]*2+s[n][j-1]+s[n][j+1]+a[n][j])%3;
            if(t!=0) {ok=false;break;}
        }
        if(!ok) continue;

        for(int i=1;i<=n;i++){
            for(int k=0;k<3;k++){
                if((k+s[i][pos+1])%3==0) needa[i]=k;
            }
        }

        for(int i=1;i<=n;i++){
            for(int k=0;k<3;k++){
                if(((k+s[i][pos+1]*2+s[i-1][pos+1]+s[i+1][pos+1]+s[i][pos+2]+a[i][pos+1])%3)==0){
                    needs[i]=k;
                }
            }
        }

        LL code1=0;
        for(int i=1;i<=n;i++){
            code1*=3;
            code1+=needs[i];
        }

        LL code2=0;
        for(int i=1;i<=n;i++){
            code2*=3;
            code2+=needa[i];
        }

        if(id.count(make_pair(code1,code2))){
            for(int i=1;i<=n;i++) printf("nees[%d]:%d\n",i,needs[i]);
            for(int i=1;i<=n;i++) printf("needa[%d]:%d\n",i,needa[i]);

            for(int i=1;i<=n;i++) needa[i]=s[i][pos+1],s[i][pos]=needs[i];
            for(int i=1;i<=n;i++){
                for(int j=pos;j<=m;j++){
                    printf("%d ",s[i][j]);
                }puts("");
            }
            memset(s,0,sizeof(s));

            for(int i=1;i<=n;i++){
                s[i][pos]=needs[i];
                s[i][pos+1]=needa[i];
            }

            print();
            return;
        }
    }
}

int main(){
    three[0]=1;
    for(int i=1;i<=15;i++) three[i]=three[i-1]*3;
    int T;
    scanf("%d",&T);
    for(int Tcase=1;Tcase<=T;Tcase++){
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                scanf("%d",&a[i][j]);
            }
        }

        if(m==1){
            s[1][0]=0;
            for(int k=0;k<=2;k++){
                s[1][1]=k;
                for(int i=2;i<=n;i++){
                    s[i][1]=(3-((s[i-2][1]+s[i-1][1]*2+a[i-1][1])%3))%3;
                }
                if((s[n-1][1]+s[n][1]*2+a[n][1])%3==0){
                    int tot=0;
                    for(int i=1;i<=n;i++) tot+=s[i][1];
                    printf("%d\n",tot);
                    for(int i=1;i<=n;i++){
                        for(int j=1;j<=s[i][1];j++)
                            printf("%d %d\n",i,1);
                    }
                    break;
                }
            }
        }
        else solve();
    }
    return 0;
}
