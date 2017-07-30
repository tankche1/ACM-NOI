# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=100010;
typedef long long LL;
const LL INF=(LL)1<<60;
LL ans=INF;
int n,k;
struct point{
    double x,y;
    int bh;
    point(){}
};
point up[maxn],down[maxn],left[maxn],right[maxn];

bool cmpup(point a,point b){ return a.y>b.y;}
bool cmpdown(point a,point b){ return a.y<b.y;}
bool cmpleft(point a,point b){ return a.x<b.x;}
bool cmpright(point a,point b){ return a.x>b.x;}
bool vis[maxn];
int Sdown[maxn],Sleft[maxn],Sright[maxn];
int down_top=-1,left_top=-1,right_top=-1;
int main(){
    //printf("ans:%I64d\n",ans);
    int x1,y1,x2,y2;
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++){
        scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
        up[i].x=(x1+x2)/2.0;up[i].y=(y1+y2)/2.0;up[i].bh=i;
    }
    for(int i=1;i<=n;i++) down[i]=up[i],left[i]=up[i],right[i]=up[i];
    sort(up+1,up+n+1,cmpup);
    sort(down+1,down+n+1,cmpdown);
    sort(left+1,left+n+1,cmpleft);
    sort(right+1,right+n+1,cmpright);
    int tot=0;
    memset(vis,false,sizeof(vis));
    bool okup,okdown,okleft,okright;
    LL area,height,width;
    for(int kup=0;tot<=k;kup++){
        if(kup>0&&!vis[up[kup].bh]){
            tot++;vis[up[kup].bh]=1;
        }
        for(int kdown=0;tot<=k;kdown++){
            if(kdown>0&&!vis[down[kdown].bh]){
                tot++;vis[down[kdown].bh]=1;
                Sdown[++down_top]=down[kdown].bh;
            }
            for(int kleft=0;tot<=k;kleft++){
                if(kleft>0&&!vis[left[kleft].bh]){
                    tot++;vis[left[kleft].bh]=1;
                    Sleft[++left_top]=left[kleft].bh;
                }
                for(int kright=0;tot<=k;kright++){
                    if(kright>0&&!vis[right[kright].bh]){
                        tot++;vis[right[kright].bh]=1;
                        Sright[++right_top]=right[kright].bh;
                    }
                    if(tot<=k){
                        height=(LL)(up[kup+1].y-down[kdown+1].y);if(!height) height++;
                        width=(right[kright+1].x-left[kleft+1].x);if(!width) width++;
                        area=(LL)height*width;
                        /*if(area==0){
                            printf("kup:%d kdown:%d kleft:%d kright:%d\n",kup,kdown,kleft,kright);
                        }*/
                        ans=min(ans,area);
                    }
                }
                while(right_top>=0){
                    tot--;vis[Sright[right_top--]]=0;
                }
            }
            while(left_top>=0){
                    tot--;vis[Sleft[left_top--]]=0;
                }
        }
        while(down_top>=0){
                    tot--;vis[Sdown[down_top--]]=0;
                }
    }
    printf("%lld\n",ans);
    return 0;
}
