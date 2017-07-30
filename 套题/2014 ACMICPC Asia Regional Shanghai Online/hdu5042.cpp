# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
const int maxn=100010;
typedef long long LL;
int n,q;
int a[maxn],b[maxn];

struct Node{
    int l,r1,r2,_gcd;
    Node() {}
    bool operator < (const Node &rhs) const{
        if(_gcd==rhs._gcd){
            if(l==rhs.l) return r1<rhs.r1;
            return l<rhs.l;
        }
        return _gcd<rhs._gcd;
    }
};
Node p[maxn*18];
int cnt=0;

inline int gcd(int a,int b){
    if(a==0) return b;
    return gcd(b%a,a);
}

int fa[maxn];
int find(int x){
    if(x==fa[x]) return x;
    return fa[x]=find(fa[x]);
}

void Union(int x,int y){
    int px=find(x),py=find(y);
    if(px==py) return;
    fa[px]=py;
}

bool cmp(int a,int b){
    if(p[a].l==p[b].l) return p[a].r1<p[b].r1;
    return p[a].l<p[b].l;
}

int sumF[maxn*18];LL sum_num[maxn*18];
int bh[maxn*18];
void prepare(){
    cnt=0;
    for(int i=1;i<=n+1;i++) fa[i]=i;

    int st,ed;
    for(int L=n;L>=1;L--){
        st=L,ed;b[L]=a[L];
        for(ed=find(st)+1;ed<=n;ed=find(ed)+1){
            b[ed]=gcd(b[ed],a[L]);
            if(b[ed]!=b[st]){
                cnt++;p[cnt].l=L;p[cnt].r1=st;p[cnt].r2=ed-1;p[cnt]._gcd=b[st];st=ed;
            }
            else Union(st,ed);
        }
        cnt++;p[cnt].l=L;p[cnt].r1=st;p[cnt].r2=n;p[cnt]._gcd=b[st];
        //printf("L:%d cnt:%d\n",L,cnt);
    }


    sort(p+1,p+cnt+1);
    /*for(int i=1;i<=cnt;i++){
        printf("L:%d r1:%d r2:%d gcd:%d\n",p[i].l,p[i].r1,p[i].r2,p[i]._gcd);
    }*/
    for(int i=1;i<=cnt;i++) bh[i]=i;
    sumF[1]=1;sum_num[1]=p[1].r2-p[1].r1+1;
    for(int i=2;i<=cnt;i++){
        sumF[i]=sumF[i-1];sum_num[i]=sum_num[i-1]+p[i].r2-p[i].r1+1;
        //printf("sum_num[%d]:%I64d\n",i,sum_num[i]);
        if(p[i]._gcd!=p[i-1]._gcd) sumF[i]++;
    }
    sort(bh+1,bh+cnt+1,cmp);

}

int main(){
    int Case,l,r,L,R,pos,M,pos2;
    Node need;
    LL k1,k2;
    LL t;
    char op[200];
    scanf("%d",&Case);
    for(int Tcase=1;Tcase<=Case;Tcase++){
        scanf("%d%d",&n,&q);
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        prepare();
        printf("Case #%d:\n",Tcase);
        for(int i=1;i<=q;i++){
            scanf("%s",op);
            if(op[0]=='S'){
                scanf("%I64d%I64d",&k1,&k2);
                if(k1>sumF[cnt]) {puts("-1");continue;}
                L=lower_bound(sumF+1,sumF+cnt+1,k1)-sumF;
                if(k1==sumF[cnt]) R=cnt;
                else R=upper_bound(sumF+1,sumF+cnt+1,k1)-sumF-1;
                //printf("L:%d R:%d\n",L,R);
                t=sum_num[L-1]+k2;
                if(sum_num[R]<t) {puts("-1");continue;}
                pos=lower_bound(sum_num+L,sum_num+R+1,t)-sum_num;
                //printf("pos:%d t:%I64d \n",pos,t);
                printf("%d %I64d\n",p[pos].l,t-sum_num[pos-1]+p[pos].r1-1);
            }
            else{
                scanf("%d%d",&l,&r);
                L=1,R=cnt;
                while(L<=R){
                    M=(L+R)>>1;
                    if(p[bh[M]].l<l||(p[bh[M]].l==l&&p[bh[M]].r1<=r)) L=M+1;
                    else R=M-1;
                }
                pos=bh[L-1];
                k1=sumF[pos];
                k2=r-p[pos].r1+1;
                need._gcd=p[pos]._gcd;need.l=0;need.r1=0;
                pos2=lower_bound(p+1,p+cnt+1,need)-p;
                k2+=sum_num[pos-1]-sum_num[pos2-1];
                printf("%I64d %I64d\n",k1,k2);
            }
        }
    }
    return 0;
}
