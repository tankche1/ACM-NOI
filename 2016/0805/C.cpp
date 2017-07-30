# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=50010;
typedef long long LL;
int mod=10007;
void update(int &x,int y){
    x+=y;while(x>=mod) x-=mod;
}
int n=50000;

int f[maxn][2];
int dp[maxn][2][2][2][2][2][2];
int p[7];
int ans;

int find(int x){
    if(x==p[x]) return x;
    return p[x]=find(p[x]);
}

void Union(int a,int b){
    int pa=find(a),pb=find(b);
    if(pa!=pb) p[pa]=pb;
}

void Go(int i,int ab,int ac,int ad,int bc,int bd,int cd,int st){
    int tmp=dp[i][ab][ac][ad][bc][bd][cd];
    if(tmp==0) return;
    if(st==7&&cd) return;

    for(int i=1;i<=6;i++) p[i]=i;
    if(ab) Union(1,2);if(ac) Union(1,3);if(ad) Union(1,4);
    if(bc) Union(2,3);if(bd) Union(2,4);if(cd) Union(3,4);

    if(st&1) Union(3,5);
    if(st&2) Union(5,6);
    if(st&4) Union(4,6);

    if(find(3)!=find(1)&&find(3)!=find(5)&&find(3)!=find(2)&&find(3)!=find(6)) return;
    if(find(4)!=find(1)&&find(4)!=find(2)&&find(4)!=find(5)&&find(4)!=find(6)) return;

    update(dp[i+1][find(1)==find(2)][find(1)==find(5)][find(1)==find(6)][find(2)==find(5)][find(2)==find(6)][find(5)==find(6)],dp[i][ab][ac][ad][bc][bd][cd]);
}

int pp[7];

void Calc(int i,int ab,int ac,int ad,int bc,int bd,int cd){
    for(int i=1;i<=6;i++) p[i]=i;
    if(ab) Union(1,2);if(ac) Union(1,3);if(ad) Union(1,4);
    if(bc) Union(2,3);if(bd) Union(2,4);if(cd) Union(3,4);

    for(int i=1;i<=6;i++) pp[i]=p[i];

    for(int st=0;st<4;st++){
        for(int i=1;i<=6;i++) p[i]=pp[i];
        if(st&1){
            if(find(1)==find(3)) continue;
            Union(1,3);
        }

        if(st&2){
            if(find(2)==find(4)) continue;
            Union(2,4);
        }

        if((find(2)!=find(1))||(find(3)!=find(1))||(find(4)!=find(1))) continue;
        update(ans,dp[i][ab][ac][ad][bc][bd][cd]);
    }
}

int main(){
    int T;
    scanf("%d",&T);
    f[1][0]=1;f[1][1]=1;
    for(int i=2;i<=n;i++){
        f[i][0]=f[i-1][0];f[i][1]=f[i-1][0];
        update(f[i][0],f[i-1][1]*2);
        update(f[i][1],f[i-1][1]*3);
       // if(i<=20) printf("i:%d %d\n",i,f[i][1]);
    }

    dp[1][0][1][0][0][1][0]=1;
    dp[1][1][1][1][1][1][1]=1;

    for(int i=1;i<n;i++){
        for(int ab=0;ab<2;ab++){
            for(int ac=0;ac<2;ac++){
                for(int ad=0;ad<2;ad++){
                    for(int bc=0;bc<2;bc++){
                        for(int bd=0;bd<2;bd++){
                            for(int cd=0;cd<2;cd++){
                                for(int st=0;st<8;st++){
                                    Go(i,ab,ac,ad,bc,bd,cd,st);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    for(int Tcase=1;Tcase<=T;Tcase++){
        scanf("%d",&n);
        printf("%d ",f[n][1]);
        ans=0;

        for(int ab=0;ab<2;ab++){
            for(int ac=0;ac<2;ac++){
                for(int ad=0;ad<2;ad++){
                    for(int bc=0;bc<2;bc++){
                        for(int bd=0;bd<2;bd++){
                            for(int cd=0;cd<2;cd++){
                                Calc(n,ab,ac,ad,bc,bd,cd);
                            }
                        }
                    }
                }
            }
        }

        printf("%d\n",ans);

    }
    return 0;
}
