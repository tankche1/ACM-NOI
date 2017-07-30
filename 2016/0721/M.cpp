# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=2010;
int n,m,k,p[5];

struct point{
    int x,y;
}s[maxn];

bool cmp1(point A,point B){
    return A.y>B.y;
}

bool cmp2(point A,point B){
    return A.x<B.x;
}

bool cmp3(int A,int B){
    return s[A].x<s[B].x;
}

int pre1[maxn],next1[maxn];
int pre2[maxn],next2[maxn];

int pp[5];

int ans;
int miny,maxy;
int sum[maxn][maxn];

int area(int x1,int y1,int x2,int y2){
    return sum[x2][y2]-sum[x1-1][y2]-sum[x2][y1-1]+sum[x1-1][y1-1];
}

void check(int a,int b,int c,int d){
    if(b==0||b>k||c==0||c>k) return;
    if(a==0||a>k||d==0||d>k) return;
    //printf("a:%d b:%d c:%d d:%d\n"a,b,c,d);

    pp[1]=a;pp[2]=b;pp[3]=c;pp[4]=d;
    sort(pp+1,pp+5,cmp3);

    /*puts("////////////");
    for(int i=1;i<5;i++){
        printf("%d %d\n",s[pp[i]].x,s[pp[i]].y);
    }
    puts("///////////////");*/

    if(!(s[pp[1]].x<s[pp[2]].x&&s[pp[2]].x<s[pp[3]].x&&s[pp[3]].x<s[pp[4]].x)) return;
    for(int i=1;i<=4;i++){
            //printf("pp[%d]:%d ",i,pp[i]);
        for(int j=i+1;j<=4;j++){
            if((p[i]-p[j])*(s[pp[i]].y-s[pp[j]].y)<=0) return;
        }
    }//puts("");
    miny=maxy=s[pp[1]].y;for(int i=2;i<=4;i++) miny=min(miny,s[pp[i]].y),maxy=max(maxy,s[pp[i]].y);
    if(area(s[pp[1]].x,miny,s[pp[4]].x,maxy)!=4) return;
   /*  puts("**********");
    for(int i=1;i<5;i++){
        printf("%d %d\n",s[pp[i]].x,s[pp[i]].y);
    }
    puts("**************");*/
   ans++;
}

void del1(int x){
    next1[pre1[x]]=next1[x];pre1[next1[x]]=pre1[x];
}

void del2(int x){
    next2[pre2[x]]=next2[x];pre2[next2[x]]=pre2[x];
}

int bh[maxn];

int main(){
    //freopen("1013.in","r",stdin);
    //freopen("output.b","w",stdout);
    int T;
    scanf("%d",&T);
    for(int Tcase=1;Tcase<=T;Tcase++){
        scanf("%d%d%d%d%d%d%d",&n,&m,&k,&p[1],&p[2],&p[3],&p[4]);
        memset(sum,0,sizeof(sum));

        for(int i=1;i<=k;i++){
            scanf("%d%d",&s[i].x,&s[i].y);sum[s[i].x][s[i].y]=1;
        }

        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+sum[i][j];
            }
        }

        pre1[0]=0;next1[k+1]=k+1;next1[0]=1;pre1[k+1]=k;
        sort(s+1,s+k+1,cmp1);
        for(int i=1;i<=k;i++) pre1[i]=i-1,next1[i]=i+1;

       /* for(int i=1;i<=k;i++){
            printf("i:%d %d %d\n",i,s[i].x,s[i].y);
        }*/

        for(int i=1;i<=k;i++) bh[i]=i;
        //sort(s+1,s+k+1,cmp2);
        sort(bh+1,bh+k+1,cmp3);
        ans=0;

        int i,j;

        for(int ii=1;ii<=k;ii++){
            i=bh[ii];
            //printf("i:%d j:%d\n",i,j);
            for(j=0;j<=k+1;j++) pre2[j]=pre1[j],next2[j]=next1[j];

            for(int jj=k;jj>ii;jj--){
                j=bh[jj];
                if(s[j].x==s[i].x) break;
                int up=s[i].y>s[j].y?i:j,down=s[i].y>s[j].y?j:i;
               // printf("i:%d j:%d up:%d down:%d\n",i,j,up,down);
                if(next2[next2[next2[up]]]==down){
                   // puts("a1");
                    check(up,next2[up],next2[next2[up]],down);
                }
                else if(next2[next2[up]]==down){
                    //puts("a2");
                    check(up,pre2[up],next2[up],down);
                    check(up,next2[up],next2[down],down);
                }
                else{
                    //puts("a3");
                    check(up,pre2[up],next2[down],down);
                    check(up,pre2[pre2[up]],pre2[up],down);
                    check(up,next2[down],next2[next2[down]],down);
                }

                del2(j);
            }

            del1(i);
        }

        printf("%d\n",ans);
    }
    return 0;
}
