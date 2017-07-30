# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=100010;
typedef pair<int,int> pi;
struct Card{
    int cost,val;
    int bh;
};
Card c[maxn];
int n;
vector<int> ans;

bool cmp(Card A,Card B){
    if(A.cost!=B.cost) return A.cost<B.cost;
    return A.val<B.val;
}

inline int lowbit(int x) {return x&(-x);}

struct FenwickTree{
    int n;pi C[maxn];

    void init(int nn) {n=nn;for(int i=1;i<=n;i++) C[i]=make_pair(0,0);}
    void add(int x,pi v){
        //C[x]=max(C[x],v);
        while(x<=n){
            C[x]=max(C[x],v);x+=lowbit(x);
        }
    }

    pi query(int x){
        pi res=make_pair(0,0);;
        while(x>0){
            res=max(res,C[x]);x-=lowbit(x);
        }
        return res;
    }


}fwt;

int main(){
    scanf("%d",&n);
    c[0].cost=0;c[0].val=1;c[0].bh=0;
    for(int i=1;i<=n;i++){
        scanf("%d%d",&c[i].cost,&c[i].val);c[i].bh=i;
    }
    fwt.init(n);

    int want=c[n].cost;
    sort(c+1,c+n+1,cmp);
    for(int i=1;i<=n;i++){
        fwt.add(i,pi(c[i].val,i));;
    }
    int now=0;
    int L,R,M;
    pi tmp;
    while(1){
        if(c[now].val>=want) {ans.push_back(n);break;}
        L=1;R=n;
        while(L<=R){
            M=(L+R)>>1;
            if(c[M].cost<=c[now].val) L=M+1;
            else R=M-1;
        }
        tmp=fwt.query(L-1);
        if(tmp.first<=c[now].val) {puts("No such luck");return 0;}
        ans.push_back(c[tmp.second].bh);
        now=tmp.second;
    }

    printf("%d\n",(int)ans.size());
    for(int i=0;i<(int)ans.size();i++){
        if(i) printf(" ");
        printf("%d",ans[i]);
    }puts("");
    return 0;
}
