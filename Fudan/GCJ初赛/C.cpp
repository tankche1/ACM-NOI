# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
typedef long long LL;
LL pow[11][20];
int prime[1310],cnt=0;
int n=16,m=50;
bool vis[10010];


void prepare(){
    for(int i=2;i<=10000;i++){
        if(!vis[i]){
            prime[cnt++]=i;
            for(int j=i;j<=10000;j+=i) vis[j]=1;
        }
    }
    //printf("cnt:%d\n",cnt);
}
int ans=0;
vector<int> print[10000];

bool _find(LL x){

    for(int i=0;i<cnt&&prime[i]<x;i++){
        if(x%(prime[i])==0){
            print[ans].push_back(prime[i]);
           // if(x==32771) printf("fuck:%d\n",prime[i]);
           return true;
        }
    }
    return false;
}

int main(){
    //freopen("output.txt","w",stdout);
    printf("Case #1:\n");
    prepare();
    for(int i=2;i<=10;i++){
        pow[i][0]=1;
        for(int j=1;j<=16;j++)
            pow[i][j]=pow[i][j-1]*i;
    }

    LL tmp;

    for(int i=0;i<(1<<14);i++){
        int x=((i<<1)^1)+pow[2][15];
        tmp=0;
        ans++;print[ans].clear();print[ans].push_back(x);
        for(int k=2;k<=10;k++){
            tmp=0;
            for(int j=0;j<16;j++){
                if((x>>j)&1){
                    tmp+=pow[k][j];
                }
            }
           // if(x==32771) printf("tmp:%I64d\n",tmp);
            if(_find(tmp)) continue;
            else {ans--;break;}
        }
        if(ans==50) break;
    }

    for(int i=1;i<=ans;i++){
        for(int k=1;k<=10;k++){
            tmp=0;
            int x=print[i][k-1],j=k==1?2:k,l;
            if(k==1){
            for(l=16;pow[j][l]>x;l--);
            for(;l>=0;l--){
                printf("%d",x/pow[j][l]);x-=x/pow[j][l]*pow[j][l];
            }
            //printf(" %d\n",print[i][k-1]);
            }
            else printf("%d",x);
            if(k<10) printf(" ");
        }
        puts("");
        //int tt;scanf("%d",&tt);
    }//printf("ans:%d\n",ans);
    return 0;
}
