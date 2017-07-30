# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=100010;
const LL INF=(LL)1<<60;
int n;
struct Point{
    LL x,y;
    Point() {}
}px[maxn],py[maxn];

LL pre_minx[maxn],pre_maxx[maxn],suf_minx[maxn],suf_maxx[maxn];
LL pre_miny[maxn],pre_maxy[maxn],suf_miny[maxn],suf_maxy[maxn];

void prepare(){
    pre_minx[0]=INF;pre_miny[0]=INF;
    pre_maxx[0]=-INF;pre_maxy[0]=-INF;
    for(int i=1;i<=n;i++){
        pre_minx[i]=min(pre_minx[i-1],py[i].x);pre_maxx[i]=max(pre_maxx[i-1],py[i].x);
        pre_miny[i]=min(pre_miny[i-1],px[i].y);pre_maxy[i]=max(pre_maxy[i-1],px[i].y);
    }
    pre_minx[0]=0;pre_miny[0]=0;
    pre_maxx[0]=0;pre_maxy[0]=0;

    suf_minx[n+1]=INF;suf_miny[n+1]=INF;
    suf_maxx[n+1]=-INF;suf_maxy[n+1]=-INF;
    for(int i=n;i>=1;i--){
        suf_minx[i]=min(suf_minx[i+1],py[i].x);suf_maxx[i]=max(suf_maxx[i+1],py[i].x);
        suf_miny[i]=min(suf_miny[i+1],px[i].y);suf_maxy[i]=max(suf_maxy[i+1],px[i].y);
    }
    suf_minx[n+1]=0;suf_miny[n+1]=-0;
    suf_maxx[n+1]=0;suf_maxy[n+1]=0;
}

inline LL sqr(LL a) {return a*a;}
inline LL Max_4(LL a,LL b,LL c,LL d) {return max(max(a,b),max(c,d));}
void print(LL D,int L,int R,char c){
    //if(D==30241) printf("L:%d R:%d %c\n",L,R,c);
}

bool check(LL D){
    LL T;
    int L,R1,R2,R,L1,L2;
    R1=1;R2=n;
    for(L=1;L<=n&&px[L].x<=0;L++){
        T=sqr(px[L].x);
        while(R1<n&&sqr(px[R1+1].x-px[L].x)<=D) R1++;
        while(sqr(px[R2].x)>sqr(px[L].x)) R2--;
        R=min(R1,R2);
        if(L==1&&R==n) return true;
        if(sqr(pre_miny[L-1])<=T&&sqr(pre_maxy[L-1])<=T&&sqr(suf_miny[R+1])<=T&&sqr(suf_maxy[R+1])<=T){
            if(Max_4(sqr(pre_miny[L-1]),sqr(pre_maxy[L-1]),sqr(suf_miny[R+1]),sqr(suf_maxy[R+1]))+T<=D){
                if(sqr(max(L==1?-INF:pre_maxy[L-1],R==n?-INF:suf_maxy[R+1])-min(L==1?INF:pre_miny[L-1],R==n?INF:suf_miny[R+1]))<=D){
                    print(D,L,R,'x');
                    return true;
                }
            }
        }
    }
    L1=n;L2=1;
    for(R=n;R>=1&&px[R].x>=0;R--){
        T=sqr(px[R].x);
        while(L1>1&&sqr(px[L1-1].x-px[R].x)<=D) L1--;
        while(sqr(px[L2].x)>sqr(px[R].x)) L2++;
        L=max(L1,L2);
        if(L==1&&R==n) return true;
        if(sqr(pre_miny[L-1])<=T&&sqr(pre_maxy[L-1])<=T&&sqr(suf_miny[R+1])<=T&&sqr(suf_maxy[R+1])<=T){
            if(Max_4(sqr(pre_miny[L-1]),sqr(pre_maxy[L-1]),sqr(suf_miny[R+1]),sqr(suf_maxy[R+1]))+T<=D){
                if(sqr(max(L==1?-INF:pre_maxy[L-1],R==n?-INF:suf_maxy[R+1])-min(L==1?INF:pre_miny[L-1],R==n?INF:suf_miny[R+1]))<=D){
                    print(D,L,R,'x');
                    return true;
                }
            }
        }
    }

    R1=1;R2=n;
    for(L=1;L<=n&&py[L].y<=0;L++){
        T=sqr(py[L].y);
        while(R1<n&&sqr(py[R1+1].y-py[L].y)<=D) R1++;
        while(sqr(py[R2].y)>sqr(py[L].y)) R2--;
        R=min(R1,R2);
        if(L==1&&R==n) return true;
        if(sqr(pre_minx[L-1])<=T&&sqr(pre_maxx[L-1])<=T&&sqr(suf_minx[R+1])<=T&&sqr(suf_maxx[R+1])<=T){
            if(Max_4(sqr(pre_minx[L-1]),sqr(pre_maxx[L-1]),sqr(suf_minx[R+1]),sqr(suf_maxx[R+1]))+T<=D){
                if(sqr(max(L==1?-INF:pre_maxx[L-1],R==n?-INF:suf_maxx[R+1])-min(L==1?INF:pre_minx[L-1],R==n?INF:suf_minx[R+1]))<=D){
                    print(D,L,R,'y');
                    return true;
                }
            }
        }
    }
    L1=n;L2=1;
    for(R=n;R>=1&&py[R].y>=0;R--){
        T=sqr(py[R].y);
        while(L1>1&&sqr(py[L1-1].y-py[R].y)<=D) L1--;
        while(sqr(py[L2].y)>sqr(py[R].y)) L2++;
        L=max(L1,L2);
        if(L==1&&R==n) return true;
        if(sqr(pre_minx[L-1])<=T&&sqr(pre_maxx[L-1])<=T&&sqr(suf_minx[R+1])<=T&&sqr(suf_maxx[R+1])<=T){
            if(Max_4(sqr(pre_minx[L-1]),sqr(pre_maxx[L-1]),sqr(suf_minx[R+1]),sqr(suf_maxx[R+1]))+T<=D){
                if(sqr(max(L==1?-INF:pre_maxx[L-1],R==n?-INF:suf_maxx[R+1])-min(L==1?INF:pre_minx[L-1],R==n?INF:suf_minx[R+1]))<=D){
                    print(D,L,R,'y');
                    return true;
                }
            }
        }
    }
    return false;
}

bool cmpx(Point A,Point B){
    return A.x<B.x;
}

bool cmpy(Point A,Point B){
    return A.y<B.y;
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%I64d%I64d",&px[i].x,&px[i].y);
        py[i]=px[i];
    }
    sort(px+1,px+n+1,cmpx);/*puts("");puts("");
    for(int i=1;i<=n;i++){
        printf("%I64d %I64d\n",px[i].x,px[i].y);
    }puts("");puts("");*/
    sort(py+1,py+n+1,cmpy);
    prepare();

    LL L=0,R=INF,M;
    while(L<=R){
        M=(L+R)>>1;
        if(check(M)) R=M-1;
        else L=M+1;
    }
    printf("%I64d\n",R+1);
    return 0;
}
