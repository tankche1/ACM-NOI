# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=200010;
typedef long long LL;
int n,k,a,b,q,op;
int need,day,tmp;
int opt1[maxn],opt2[maxn];
inline int lowbit(int x) {return x&(-x);}

struct FenwickTree{
    int C[maxn],n;
    void init(int nn) {n=nn;for(int i=0;i<=n;i++) C[i]=0;}

    void add(int x,int val){
        while(x<=n){
            C[x]+=val;x+=lowbit(x);
        }
    }

    int sum(int x){
        int res=0;
        while(x>0){
            res+=C[x];x-=lowbit(x);
        }
        return res;
    }

}fwt1,fwt2;

int main(){
    int ans;
    scanf("%d%d%d%d%d",&n,&k,&a,&b,&q);
    fwt1.init(n);fwt2.init(n);
    for(int i=1;i<=q;i++){
        scanf("%d",&op);
        if(op==1){
            scanf("%d%d",&day,&need);
            tmp=min(b,opt1[day]+need);
            if(tmp>opt1[day]){
                fwt1.add(day,tmp-opt1[day]);
                opt1[day]=tmp;
            }

            tmp=min(a,opt2[day]+need);
            if(tmp>opt2[day]){
                fwt2.add(day,tmp-opt2[day]);
                opt2[day]=tmp;
            }
        }
        else{
            scanf("%d",&day);
            ans=fwt2.sum(n)-fwt2.sum(day+k-1)+fwt1.sum(day-1);
            printf("%d\n",ans);
        }
    }
    return 0;
}
