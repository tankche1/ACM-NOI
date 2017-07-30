# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=65;
int st[maxn],ed[maxn];
LL F[maxn][4],H[maxn][4];
LL S[maxn];
int n;

int main(){
    int tcase=0;
while(scanf("%d",&n)!=EOF){
    if(!n) break;
    for(int i=1;i<=n;i++) scanf("%d",&st[i]);
    for(int i=1;i<=n;i++) scanf("%d",&ed[i]);

    for(int C=1;C<=3;C++) {if(st[1]==C) F[1][C]=0;else F[1][C]=1;}
    for(int i=2;i<=n;i++){
        for(int C=1;C<=3;C++){
            if(st[i]==C) F[i][C]=F[i-1][C];
            else{
                F[i][C]=F[i-1][6-st[i]-C]+1+((LL)1<<(i-1))-1;
            }
        }
    }

    for(int C=1;C<=3;C++) if(ed[1]==C) H[1][C]=0;else H[1][C]=1;
    for(int i=2;i<=n;i++){
        for(int C=1;C<=3;C++){
            if(ed[i]==C) H[i][C]=H[i-1][C];
            else{
                H[i][C]=H[i-1][6-ed[i]-C]+((LL)1<<(i-1));
            }
        }
    }

    S[0]=0;
    for(int i=1;i<=n;i++){
        if(st[i]==ed[i]) S[i]=S[i-1];
        else{
            S[i]=F[i-1][6-st[i]-ed[i]]+1+H[i-1][6-st[i]-ed[i]];
        }
    }
    printf("Case %d: %lld\n",++tcase,S[n]);
}
    return 0;
}
