# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
const int maxn=1000100;
const int INF=1000000010;
int ssum,mmin,mmax;

struct SegmenTree{
    int sumv[maxn<<2],minv[maxn<<2],maxv[maxn<<2],setv[maxn<<2],addv[maxn<<2];
    void build() {
        memset(sumv,0,sizeof(sumv));memset(minv,0,sizeof(minv));
        memset(maxv,0,sizeof(maxv));memset(setv,0,sizeof(setv));
        memset(addv,0,sizeof(addv));
    }

    void maintain(int o){
        sumv[o]=sumv[o<<1]+sumv[o<<1|1];
        minv[o]=min(minv[o<<1],minv[o<<1|1]);
        maxv[o]=max(maxv[o<<1],maxv[o<<1|1]);
    }

    void pushdown(int o,int L,int R){
        int M=(L+R)>>1;
        if(setv[o]){
            addv[o<<1]=0;setv[o<<1]=setv[o];
            sumv[o<<1]=(M-L+1)*setv[o];minv[o<<1]=maxv[o<<1]=setv[o];
            addv[o<<1|1]=0;setv[o<<1|1]=setv[o];
            sumv[o<<1|1]=(R-M)*setv[o];minv[o<<1|1]=maxv[o<<1|1]=setv[o];
            setv[o]=0;
        }
        if(addv[o]){
            addv[o<<1]+=addv[o];
            sumv[o<<1]+=(M-L+1)*addv[o];minv[o<<1]+=addv[o];maxv[o<<1]+=addv[o];
            addv[o<<1|1]+=addv[o];
            sumv[o<<1|1]+=(R-M)*addv[o];minv[o<<1|1]+=addv[o];maxv[o<<1|1]+=addv[o];
            addv[o]=0;
        }
    }

    void add(int o,int L,int R,int qL,int qR,int v){
        if(qL<=L&&qR>=R){
            addv[o]+=v;sumv[o]+=(R-L+1)*v;
            minv[o]+=v;maxv[o]+=v;
            return;
        }
        int M=(L+R)>>1;
        pushdown(o,L,R);
        if(qL<=M) add(o<<1,L,M,qL,qR,v);
        if(qR>M) add(o<<1|1,M+1,R,qL,qR,v);
        maintain(o);
        return;
    }

    void reset(int o,int L,int R,int qL,int qR,int v){
        if(qL<=L&&qR>=R){
            addv[o]=0;setv[o]=v;sumv[o]=(R-L+1)*v;maxv[o]=minv[o]=v;
            return;
        }
        int M=(L+R)>>1;
        pushdown(o,L,R);
        if(qL<=M) reset(o<<1,L,M,qL,qR,v);
        if(qR>M) reset(o<<1|1,M+1,R,qL,qR,v);
        maintain(o);
    }

    void query(int o,int L,int R,int qL,int qR){
        if(qL<=L&&qR>=R){
            ssum+=sumv[o];mmin=min(mmin,minv[o]);mmax=max(mmax,maxv[o]);
            return;
        }
        int M=(L+R)>>1;
        pushdown(o,L,R);
        if(qL<=M) query(o<<1,L,M,qL,qR);
        if(qR>M) query(o<<1|1,M+1,R,qL,qR);
    }
}seg[21];



int r,c,m;
int main(){
    while(scanf("%d%d%d",&r,&c,&m)!=EOF){
        int op,x1,y1,x2,y2,v;
        for(int i=1;i<=r;i++) seg[i].build();
        for(int tt=1;tt<=m;tt++){
            scanf("%d%d%d%d%d",&op,&x1,&y1,&x2,&y2);
            if(op==1){
                    scanf("%d",&v);
                for(int i=x1;i<=x2;i++)
                    seg[i].add(1,1,c,y1,y2,v);
            }
            else if(op==2){
                scanf("%d",&v);
                for(int i=x1;i<=x2;i++)
                    seg[i].reset(1,1,c,y1,y2,v);
            }
            else{
                ssum=0,mmin=INF;mmax=-INF;
                for(int i=x1;i<=x2;i++)
                    seg[i].query(1,1,c,y1,y2);
                printf("%d %d %d\n",ssum,mmin,mmax);
            }
        }
    }
	return 0;
}
