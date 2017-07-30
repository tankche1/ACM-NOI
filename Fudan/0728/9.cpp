# include<stdio.h>
# include<string.h>
# include<math.h>
# include<vector>
# include<string>
# include<algorithm>
# define mp(a,b) make_pair(a,b)
using namespace std;
typedef long long LL;
const int maxn=50010;
struct point{
    int x,y,z;
    point(int x=0,int y=0,int z=0):x(x),y(y),z(z){}
};
point a[maxn];
int n,m;
bool cmp1(point a,point b){return a.z<b.z;}
bool cmp2(point a,point b){return a.y>b.y;}

pair<int,int> dp[maxn];

pair<int,int> Max(pair<int,int> a,pair<int,int> b){
    if(a.first!=b.first) return a.first>b.first?a:b;
    return a.second<b.second?a:b;
}

inline int lowbit(int x) {return x&(-x);}

struct FenwickTree{
    pair<int,int> C[maxn];
    void init() {for(int i=0;i<=n;i++) C[i].first=C[i].second=0;}

    pair<int,int> ask(int x){
        pair<int,int> res=mp(0,0);
        while(x>0) res=Max(res,C[x]),x-=lowbit(x);
        return res;
    }

    void update(int x,pair<int,int> v){
        while(x<=n){
            C[x]=Max(C[x],v);x+=lowbit(x);
        }
    }

    void clear(int x){
        while(x<=n){
            C[x]=mp(0,0);x+=lowbit(x);
        }
    }

}fwt;
pair<int,int> t;

void cdq(int L,int R){
    if(L==R) return;
    int M=(L+R)>>1;
    sort(a+L,a+R+1,cmp1);
    cdq(M+1,R);
    sort(a+L,a+M+1,cmp2);sort(a+M+1,a+R+1,cmp2);
    int pos1=L,pos2=M+1;
    for(int tt=1;tt<=R-L+1;tt++){
        if((pos1>M)||(pos2<=R&&a[pos2].y>=a[pos1].y)){
            fwt.update(a[pos2].x,mp(dp[a[pos2].z].first,a[pos2].z));
            pos2++;
        }
        else{
            t=fwt.ask(a[pos1].x);
            t.first++;if(t.first==1) {pos1++;continue;}
            dp[a[pos1].z]=Max(dp[a[pos1].z],t);//printf("dp[%d]:%d\n",a[pos1].z,dp[a[pos1].z].first);
            pos1++;
        }
    }

    for(int tt=M+1;tt<=R;tt++)
        fwt.clear(a[tt].x);
    cdq(L,M);
    return;
}
int x[maxn],x_cnt;
vector<int> print;

int main(){
    int ans,pos;
    while(scanf("%d",&n)!=EOF){
        x_cnt=0;
        for(int i=1;i<=n;i++) scanf("%d",&a[i].x),a[i].z=i,x[x_cnt++]=a[i].x;
        for(int i=1;i<=n;i++) scanf("%d",&a[i].y);
        sort(x,x+x_cnt);
        x_cnt=unique(x,x+x_cnt)-x;
        for(int i=1;i<=n;i++) a[i].x=lower_bound(x,x+x_cnt,a[i].x)-x+1;
        sort(a+1,a+n+1,cmp1);
        for(int i=1;i<=n;i++) dp[i].first=1,dp[i].second=i;
        //seg.build(1,1,n);
        fwt.init();
        cdq(1,n);
        ans=0;
        for(int i=1;i<=n;i++)
            if(dp[i].first>ans) ans=dp[i].first,pos=i;
        printf("%d\n",ans);
        print.clear();
        while(1){
            print.push_back(pos);
            if(dp[pos].first==1) break;
            pos=dp[pos].second;
        }
        printf("%d",print[0]);
        for(int i=1;i<(int)print.size();i++)
            printf(" %d",print[i]);
        puts("");
    }
    return 0;
}
