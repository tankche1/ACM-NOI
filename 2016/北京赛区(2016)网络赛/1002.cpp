# include<stdio.h>
# include<string.h>
# include<vector>
# include<set>
# include<bitset>
# include<algorithm>
using namespace std;
const int maxn=500010;
typedef long long LL;
int n,m;
LL K;
int a[maxn];
int b[maxn];
int len;

bool check(int L,int R){
    LL tmp;
    for(int i=L;i<=R;i++) b[i-L]=a[i];
    len=R-L+1;
    sort(b,b+len);
    LL ans=0;
    int w=min(len>>1,m);
    for(int i=0;i<w;i++){
        tmp=b[len-1-i]-b[i];
        ans+=tmp*tmp;
    }
    return ans<=K;
}

void RD(int &x) {
    static char c;
    for (c = getchar() ; !isdigit(c) ; c = getchar());
    x = c - '0';
    for (c = getchar() ; isdigit(c) ; c = getchar())
        x = x * 10 + c - '0';
}


int main(){
    int Case;
    int L,R,M,d;
    RD(Case);
    for(int Tcase=1;Tcase<=Case;Tcase++){
        scanf("%d%d%lld",&n,&m,&K);
        for(int i=1;i<=n;i++) RD(a[i]);
        int ans=0;
        for(int i=1;i<=n;){
            d=0;
            for(int k=1;;k++){
                if(!check(i,min(i+(1<<k)-1,n))){
                    break;
                }
                else d=k;

                if(i+(1<<k)-1>=n) break;
            }
            L=i+(1<<d)-1;R=min(n,i+(1<<d+1)-1);
            while(L<=R){
                M=(L+R)>>1;
                if(check(i,M)) L=M+1;
                else R=M-1;
            }
            i=L-1+1;ans++;
        }

        printf("%d\n",ans);
    }
    return 0;
}
