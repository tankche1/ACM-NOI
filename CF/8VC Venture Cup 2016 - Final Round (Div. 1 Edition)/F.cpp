# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=3010;
int n,k,r,c;
vector<int> G[maxn];

struct point{
    int x,y;
    point() {}
}p[maxn];

vector<int> q;

bool cmp(int A,int B){
    if(p[A].x==p[B].x) return p[A].y<p[B].y;
    return p[A].x<p[B].x;
}

int pre[maxn],nex[maxn],nexk[maxn];

int calc(int bh){
    if(bh==0||nexk[bh]==n+1) return 0;
    return (p[bh].x-p[pre[bh]].x)*(r+1-p[nexk[bh]].x);
}

int main(){
    int a,b;
    scanf("%d%d%d%d",&r,&c,&n,&k);
    for(int i=1;i<=n;i++){
        scanf("%d%d",&p[i].x,&p[i].y);
        G[p[i].y].push_back(i);
    }

    LL res=0,ans=0;int t;
    for(int L=1;L<=c;L++){
        q.clear();
        for(int i=1;i<=n;i++){
            if(p[i].y>=L) q.push_back(i);
        }
        sort(q.begin(),q.end(),cmp);
        pre[0]=0;nex[n+1]=n+1;nex[0]=n+1;pre[n+1]=0;
        for(int i=0;i<(int)q.size();i++){
            nex[q[i]]=n+1;pre[q[i]]=pre[n+1];nex[pre[q[i]]]=q[i];pre[n+1]=q[i];
        }

        for(int i=0;i<=n+1;i++) nexk[i]=n+1;
        a=nex[0];for(int i=1;i<k;i++) a=nex[a];
        b=nex[0];
        while(b!=n+1){
            nexk[b]=a;a=nex[a];b=nex[b];
        }

        res=0;
        for(int i=nex[0];i!=n+1;i=nex[i]) res+=calc(i);

        for(int R=c;R>=L;R--){
            ans+=res;
            for(int e=0;e<(int)G[R].size();e++){
                a=b=G[R][e];
                res-=calc(a);nexk[a]=n+1;
                for(int i=1;i<k&&b!=0;i++){
                    b=pre[b];
                    res-=calc(b);
                    nexk[b]=nex[nexk[b]];
                    res+=calc(b);
                }
                res-=calc(nex[a]);
                t=nex[a];
                pre[nex[a]]=pre[a];nex[pre[a]]=nex[a];
                pre[a]=nex[a]=0;
                res+=calc(t);
            }
        }
    }
    printf("%I64d\n",ans);
    return 0;
}
